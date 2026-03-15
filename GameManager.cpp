#include "GameManager.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "MovementComponent.h"
#include "PlayerInputComponent.h"
#include "EntityFactory.h"

GameManager::GameManager()
    : currentGameState(Gamestate::Playing), eventManager(), player(), gameTimer(0.0f)
{
}

void GameManager::Initialize(int screenWidth, int screenHeight, Vector2 screenCenter)
{
    eventManager.SubscribeToHealthChanged([](const HealthChangedEvent& event) {
        if (event.delta < 0)
        {
            TraceLog(LOG_INFO, "Player took %d damage! Health: %d/%d",
                -event.delta, event.newHealth, event.maxHealth);
        }
        else
        {
            TraceLog(LOG_INFO, "Player healed %d! Health: %d/%d",
                event.delta, event.newHealth, event.maxHealth);
        }
        });

    player = EntityFactory::CreatePlayer(screenCenter, &eventManager, projectileManager);
    currentGameState = Gamestate::Paused;
    gameTimer = 0.0f;
}

void GameManager::Update(float deltaTime)
{
    if (currentGameState == Gamestate::Playing)
    {
        gameTimer += deltaTime;
        player->Update(deltaTime);
        projectileManager.Update(deltaTime);
        auto* stats = player->GetComponent<StatsComponent>();

        for (auto& enemy : enemies)
        {
            enemy->Update(deltaTime);
        }

        if (IsKeyPressed(KEY_J) && stats)
        {
            stats->currentHealth -= 10;
            if (stats->currentHealth < 0) stats->currentHealth = 0;
        }

        if (IsKeyPressed(KEY_K) && stats)
        {
            stats->currentHealth += 15;
            if (stats->currentHealth > stats->maxHealth)
                stats->currentHealth = stats->maxHealth;
        }

        if (IsKeyPressed(KEY_P))
        {
            currentGameState = Gamestate::Paused;
        }

        if (stats && stats->currentHealth <= 0)
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
    Vector2 screenCenter = { GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f };
    Initialize(GetScreenWidth(), GetScreenHeight(), screenCenter);
}
