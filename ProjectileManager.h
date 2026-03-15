#pragma once

#include "raylib.h"
#include "ProjectilePool.h"
#include "raymath.h"


class ProjectileManager
{
private:
	ProjectilePool projectilePool;

public:
	ProjectileManager()
	{
		for (int p = 0; p < MAX_PROJECTILES; p++)
			projectilePool[p].isActive = false;
	}

	void Shoot(Vector2 firePoint, Vector2 direction, int bulletType, int shootingAtEnemyOrPlayer, Vector2 targetToShoot = {0,0})
	{
		int projectileIndex = FindBulletInPool(projectilePool);
		if (projectileIndex < 0) return;
		
		ActivateBulletPool(projectilePool, projectileIndex, firePoint, bulletType, direction, shootingAtEnemyOrPlayer, targetToShoot);


	};


	void Update(float deltaTime)
	{

		UpdateProjectilePool(projectilePool, deltaTime);

	}

	void UpdateHomingTargeting(int shootingAtEnemyOrPlayer, Vector2 target)
	{
		for (int p = 0; p < MAX_PROJECTILES; p++)
		{
			if (projectilePool[p].isActive && projectilePool[p].shootingAtEnemyOrPlayer == shootingAtEnemyOrPlayer && projectilePool[p].typeOfProjectile == 1)
			{
				projectilePool[p].homingRocket.homingTargetLocation = target;
			}

		}


	}

	void Draw() const
	{
		for (int p = 0; p < MAX_PROJECTILES; p++)
		{
			if (!projectilePool[p].isActive) continue;

			switch (projectilePool[p].typeOfProjectile)
			{
			
				case 0:
					DrawCircleV(projectilePool[p].position, projectilePool[p].stdBullet.radius, RED);
					break;

				case 1:
				{
					Vector2 tipLocal = { 0, -10 };
					Vector2 leftLocal = { -4, 6 };
					Vector2 rightLocal = { 4, 6 };
					Vector2 homingTarget = projectilePool[p].homingRocket.homingTargetLocation;
					float rotation = atan2(homingTarget.x, homingTarget.y);

					Vector2 tip = Vector2Add(projectilePool[p].position, Vector2Rotate(tipLocal, rotation));
					Vector2 left = Vector2Add(projectilePool[p].position, Vector2Rotate(leftLocal, rotation));
					Vector2 right = Vector2Add(projectilePool[p].position, Vector2Rotate(rightLocal, rotation));

					DrawTriangle(tip, left, right, ORANGE);
					break;
				}

				case 2:
				{
					DrawCircleV(projectilePool[p].position, projectilePool[p].explodingBullet.radius, BLACK);
					DrawCircleLines(projectilePool[p].position.x, projectilePool[p].position.y, projectilePool[p].explodingBullet.radius * 2, YELLOW);
					break;
				}
			}
		}

	}










};