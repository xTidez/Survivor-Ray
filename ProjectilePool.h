#pragma once
#include "raylib.h"


#define MAX_PROJECTILES 300

struct Projectile 
{
	bool isActive;
	int shootingAtEnemyOrPlayer = 0;
	Vector2 position;
	Vector2 velocity;
	float speedStd = 150.0f;
	float speedMultiplier = 1.0f;
	int typeOfProjectile;

	union 
	{

		struct
		{
			float radius;
			float activeDuration;
			int damage;
		} stdBullet;

		struct
		{
			Vector2 homingTargetLocation;
			float agility;
			int damage;

		} homingRocket;

		struct
		{
			float radius;
			float explotionRadius;
			int damage;
			float activeDuration;

		} explodingBullet;


	};
	

};

using ProjectilePool = Projectile[MAX_PROJECTILES];

int FindBulletInPool(ProjectilePool& projPool);
void ActivateBulletPool(ProjectilePool& projPool, int bulletNr, Vector2 position, int bulletType, Vector2 direction, int team, Vector2 homingTarget = { 0, 0 });

void DeactivateBulletPool(ProjectilePool projPool, int bulletNr);

void UpdateProjectilePool(ProjectilePool& projPool, float deltaTime);



