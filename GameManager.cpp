#include "GameManager.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "MovementComponent.h"
#include "PlayerInputComponent.h"
#include "EntityFactory.h"
#include "CollisionManager.h"

GameManager::GameManager()
    : currentGameState(Gamestate::Playing), eventManager(), player(), gameTimer(0.0f)
{
}

void GameManager::Initialize(int screenWidth, int screenHeight, Vector2 screenCenter)
{
  

    player = EntityFactory::CreatePlayer(screenCenter, &eventManager, projectileManager);
    currentGameState = Gamestate::Paused;
    gameTimer = 0.0f;

    waveManager.StartNextWave();
}

void GameManager::Update(float deltaTime)
{
    if (currentGameState == Gamestate::Playing)
    {
        
        gameTimer += deltaTime;
        player->Update(deltaTime);
        projectileManager.Update(deltaTime);
        collisionManager::CheckForProjectileCollisions(projectileManager.GetProjectilePool(), player.get(), enemies);
        auto* playerStats = player->GetComponent<StatsComponent>();

        auto* playerTransform = player->GetComponent<TransformComponent>();
        Vector2 playerPosition = playerTransform ? playerTransform->position : Vector2{ 0,0 };

        waveManager.Update(deltaTime, playerPosition, GetScreenWidth(), GetScreenHeight(), player.get(), projectileManager, enemies);

        for (auto& enemy : enemies)
        {
            enemy->Update(deltaTime);
            auto* enemyStats = enemy->GetComponent<StatsComponent>();
            if (enemyStats && enemyStats->currentHealth <= 0)
            {   
                auto* playerStats = player->GetComponent<StatsComponent>();
                if (playerStats) playerStats->experience += 10;
                enemy->SetActive(false);
            }

        }

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const std::unique_ptr<Entity>& e)
            {return !e->IsActive(); }), enemies.end()); // cleanup code for enemies, sorts and deletes inactives

        if (IsKeyPressed(KEY_J) && playerStats)
        {
            playerStats->currentHealth -= 10;
            if (playerStats->currentHealth < 0) playerStats->currentHealth = 0;
        }

        if (IsKeyPressed(KEY_K) && playerStats)
        {
            playerStats->currentHealth += 15;
            if (playerStats->currentHealth > playerStats->maxHealth)
                playerStats->currentHealth = playerStats->maxHealth;
        }

        if (IsKeyPressed(KEY_P))
        {
            currentGameState = Gamestate::Paused;
        }

        if (playerStats && playerStats->currentHealth <= 0)
        {
            currentGameState = Gamestate::GameOver;
        }
    }
    else if (currentGameState == Gamestate::Paused)
    {
        if (IsKeyPressed(KEY_P))
        {
            currentGameState = Gamestate::Playing;
        }
    }
    else if (currentGameState == Gamestate::GameOver)
    {
        if (IsKeyPressed(KEY_R))
        {
            Reset();
        }
    }
}

void GameManager::Draw()
{
    if (currentGameState == Gamestate::Playing)
    {
        auto* playerTransform = player->GetComponent<TransformComponent>();
        auto* playerStats = player->GetComponent<StatsComponent>();

        if (playerTransform)
        {
            DrawCircleV(playerTransform->position, playerTransform->radius, DARKBLUE);
            Vector2 firePoint =
            {
                playerTransform->position.x + cosf(playerTransform->rotation) * playerTransform->radius,
                playerTransform->position.y + sinf(playerTransform->rotation) * playerTransform->radius
            };
            DrawCircleV(firePoint, playerTransform->radius / 4, BLACK);
        }

        if (playerStats)
        {
            DrawText(TextFormat("Health: %d/%d", playerStats->currentHealth, playerStats->maxHealth), 10, 10, 20, BLACK);
            DrawText(TextFormat("Level: %d", playerStats->level), 10, 35, 20, BLACK);
        }

        for (auto& enemy : enemies)
        {
            auto* enemyTransform = enemy->GetComponent<TransformComponent>();
            if (enemyTransform)
            {
                DrawCircleV(enemyTransform->position, enemyTransform->radius, BLACK);
                enemy->Draw();
            }

        }

        DrawText(TextFormat("Time: %.1f", gameTimer), GetScreenWidth() - 120, 10, 20, BLACK);
        projectileManager.Draw();
    }

    if (currentGameState == Gamestate::Paused)
    {
        DrawText("PAUSED", GetScreenWidth() / 2 - 60, GetScreenHeight() / 2, 40, RED);
        DrawText("Press P to play", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 50, 20, BLACK);
    }
    else if (currentGameState == Gamestate::GameOver)
    {
        DrawText("GAME OVER", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 40, 40, RED);
        DrawText(TextFormat("Survival Time: %.1f", gameTimer),
            GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 + 10, 20, BLACK);
        DrawText("Press R to restart",
            GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 + 40, 20, BLACK);
    }
}

void GameManager::Reset()
{
    enemies.clear();
    player.reset();
    projectileManager.ClearBullets();
    waveManager = WaveManager();
    Vector2 screenCenter = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    Initialize(GetScreenWidth(), GetScreenHeight(), screenCenter);
}
