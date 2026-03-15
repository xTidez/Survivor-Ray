#pragma once

#include "raylib.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "ProjectilePool.h"
#include <vector>
#include <memory>

class collisionManager
{
public:
	static void CheckForProjectileCollisions(ProjectilePool& projectilePool, Entity* player, std::vector<std::unique_ptr<Entity>>& enemies)
	{
		for (int p = 0; p < MAX_PROJECTILES; p++)
		{
			if (!projectilePool[p].isActive) continue;

			if (projectilePool[p].shootingAtEnemyOrPlayer == 1)
			{
				CheckHit(projectilePool[p], player);
			}
			if (projectilePool[p].typeOfProjectile == 2 && projectilePool[p].explodingBullet.readyToBlow)
			{
				for (auto& enemy : enemies)
				{
					CheckExplosion(projectilePool[p], enemy.get());
				}

				projectilePool[p].isActive = false;
				continue;
			}
			else if (projectilePool[p].shootingAtEnemyOrPlayer == 0)
			{
				for (auto& enemy : enemies)
				{
					if (CheckHit(projectilePool[p], enemy.get())) break;

				}

			}
			

		}

	}

private:
	static bool CheckHit(Projectile& projectile, Entity* attackTarget)
	{
		auto* targetTransform = attackTarget->GetComponent<TransformComponent>();
		if (!targetTransform) return false;
		
		if (CheckCollisionCircles(projectile.position, projectile.radius, targetTransform->position, targetTransform->radius))
		{
			auto* targetStats = attackTarget->GetComponent<StatsComponent>();
			if (targetStats) targetStats->currentHealth -= projectile.damage;

			if (projectile.typeOfProjectile == 0 || projectile.typeOfProjectile == 1)
			{
				projectile.isActive = false;
			}
			return true;
		}
		

		return false;

	}

	static bool CheckExplosion(Projectile& projectile, Entity* attackTarget)
	{
		auto* targetTransform = attackTarget->GetComponent<TransformComponent>();
		if (!targetTransform) return false;

		if (CheckCollisionCircles(projectile.position, projectile.explodingBullet.explotionRadius, targetTransform->position, targetTransform->radius))
		{
			auto* targetStats = attackTarget->GetComponent<StatsComponent>();
			if (targetStats) targetStats->currentHealth -= projectile.damage;

			
			return true;
		}


		return false;

	}

};