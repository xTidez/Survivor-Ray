#pragma once
#include "raylib.h"
#include "Player.h"

#define MAX_PROJECTILES 300

typedef struct  
{
	bool isActive;
	Vector2 position;
	Vector2 velocity;
	int typeOfProjectile;

	union {

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
			float explotionRadius;
			int damage;
			float activeDuration;

		} explodingBullet;

	
	};

} Projectile;

typedef Projectile ProjectilePool[MAX_PROJECTILES];

int FindBulletInPool(ProjectilePool& projPool);

void ActivateBulletPool(ProjectilePool& projPool, int bulletNr, Vector2 position, int bulletType, Vector2 velocity, const Player& player);

void DeactivateBulletPool(ProjectilePool projPool, int bulletNr);



