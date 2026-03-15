#pragma once
#include "raylib.h"
#include "math.h"


class EventManager;

struct Player 
{
	Vector2 playerPosition;
	float playerRadius;
	float playerMoveSpeed;
	int playerCurrentHealth;
	int playerMaxHealth;
	int playerDamage;
	float fireRate;
	int playerExperience;
	int playerLevel;
	EventManager* eventManager;
	Vector2 aimTarget;
	float playerRotation;

	Vector2 FirePoint() const
	{
		return
		{
			playerPosition.x + cosf(playerRotation) * playerRadius,
			playerPosition.y + sinf(playerRotation) * playerRadius
		};
	}
};

namespace PlayerFactory
{
	Player CreatePlayer(Vector2 startPosition, EventManager* eventMgr = nullptr);
}

void DrawPlayer(const Player& player);
void PlayerUpdate(Player& player, float deltatime);
void PlayerTakeDamage(Player& player, int damage);
void PlayerHeal(Player& player, int healAmount);

