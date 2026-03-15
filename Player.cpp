#include "player.h"
#include "EventManager.h"
#include "math.h"


void PlayerUpdate(Player& player, float deltaTime)
{
    if (IsKeyDown(KEY_W)) player.playerPosition.y -= player.playerMoveSpeed * deltaTime;
    if (IsKeyDown(KEY_S)) player.playerPosition.y += player.playerMoveSpeed * deltaTime;
    if (IsKeyDown(KEY_A)) player.playerPosition.x -= player.playerMoveSpeed * deltaTime;
    if (IsKeyDown(KEY_D)) player.playerPosition.x += player.playerMoveSpeed * deltaTime;

    if (player.playerPosition.x < player.playerRadius)
        player.playerPosition.x = player.playerRadius;
    if (player.playerPosition.y < player.playerRadius)
        player.playerPosition.y = player.playerRadius;
    if (player.playerPosition.x > GetScreenWidth() - player.playerRadius)
        player.playerPosition.x = GetScreenWidth() - player.playerRadius;
    if (player.playerPosition.y > GetScreenHeight() - player.playerRadius)
        player.playerPosition.y = GetScreenHeight() - player.playerRadius;

    Vector2 mousePosition = GetMousePosition();
    Vector2 lookAtMouse =
    {
        mousePosition.x - player.playerPosition.x,
        mousePosition.y - player.playerPosition.y
    };
    player.playerRotation = atan2f(lookAtMouse.y, lookAtMouse.x);

}

void DrawPlayer(const Player& player) 
{
    DrawCircleV(player.playerPosition, player.playerRadius, BLUE);
    Vector2 firePoint = player.FirePoint();

    DrawCircleV(firePoint, player.playerRadius / 4, BLACK);
}

void PlayerTakeDamage(Player& player, int damage)
{
    player.playerCurrentHealth -= damage;
    if (player.playerCurrentHealth < 0) player.playerCurrentHealth = 0;

    if (player.eventManager)
    {
        HealthChangedEvent event;
        event.newHealth = player.playerCurrentHealth;
        event.maxHealth = player.playerMaxHealth;
        event.delta = -damage;
        player.eventManager->TriggerHealthChanged(event);
    }
}

void PlayerHeal(Player& player, int healAmount)
{
    player.playerCurrentHealth += healAmount;
    if (player.playerCurrentHealth > player.playerMaxHealth) 
        player.playerCurrentHealth = player.playerMaxHealth;

    if (player.eventManager)
    {
        HealthChangedEvent event;
        event.newHealth = player.playerCurrentHealth;
        event.maxHealth = player.playerMaxHealth;
        event.delta = healAmount;
        player.eventManager->TriggerHealthChanged(event);
    }
}

namespace PlayerFactory
{
    Player CreatePlayer(Vector2 startPosition, EventManager* eventMgr)
    {
        Player player;
        player.playerPosition = startPosition;
        player.playerRadius = 10.0f;
        player.playerRotation = 0.0f;
        player.playerMoveSpeed = 150.0f;
        player.playerCurrentHealth = 100;
        player.playerMaxHealth = 100;
        player.playerDamage = 10;
        float fireRate = 1.0f;
        player.playerExperience = 0;
        player.playerLevel = 1;
        player.eventManager = eventMgr;
        return player;
    }
}


