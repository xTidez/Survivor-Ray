
#include "ProjectilePool.h"
#include "raylib.h"
#include "raymath.h"




int FindBulletInPool(ProjectilePool& projPool)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (!projPool[i].isActive)
		{
			return i;
		}

	}
	return -1;
}

void ActivateBulletPool(ProjectilePool& projPool, int bulletNr, Vector2 firePostion, int bulletType, Vector2 direction,int shootingAtEnemyOrPlayer, Vector2 homingTarget)
{
	projPool[bulletNr].isActive = true;
	projPool[bulletNr].position = firePostion;
	projPool[bulletNr].typeOfProjectile = bulletType;
	projPool[bulletNr].shootingAtEnemyOrPlayer = shootingAtEnemyOrPlayer;

	switch (bulletType)
	{
		case 0:
			projPool[bulletNr].stdBullet.radius = 2.0f;
			projPool[bulletNr].stdBullet.activeDuration = 5.0f;
			projPool[bulletNr].stdBullet.damage = 10;
			break;

		case 1:
			projPool[bulletNr].homingRocket.homingTargetLocation = homingTarget;
			projPool[bulletNr].homingRocket.agility = 3.0f;
			projPool[bulletNr].speedMultiplier = 1.2;
			projPool[bulletNr].homingRocket.damage = 20; 
			break;

		case 2:
			projPool[bulletNr].explodingBullet.radius = 5.0f;
			projPool[bulletNr].explodingBullet.explotionRadius = 10.0f;
			projPool[bulletNr].explodingBullet.activeDuration = 5.0f;
			projPool[bulletNr].speedMultiplier = 0.8;
			projPool[bulletNr].explodingBullet.damage = 25;
			break;

	} 

	float bulletSpeed = projPool[bulletNr].speedStd * projPool[bulletNr].speedMultiplier;
	projPool[bulletNr].velocity =
	{
		direction.x * bulletSpeed,
		direction.y * bulletSpeed
	};

}

void UpdateProjectilePool(ProjectilePool& projPool, float deltaTime)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		auto& projectile = projPool[i];
		if (!projectile.isActive) continue;

		if (projectile.typeOfProjectile == 1) 
		{
		Vector2 toTarget = 
			{
				projectile.homingRocket.homingTargetLocation.x - projectile.position.x,
				projectile.homingRocket.homingTargetLocation.y - projectile.position.y
			};
			
		toTarget = Vector2Normalize(toTarget);
		float projectileSpeed = projectile.speedStd * projectile.speedMultiplier;
		float agility = projectile.homingRocket.agility;

		projectile.velocity.x += (toTarget.x * projectileSpeed - projectile.velocity.x * agility * deltaTime);
		projectile.velocity.y += (toTarget.y * projectileSpeed - projectile.velocity.y * agility * deltaTime);

		}

		projectile.position.x += projectile.velocity.x * deltaTime;
		projectile.position.y += projectile.velocity.y * deltaTime;

		
		if (projectile.position.x > GetScreenWidth() || projectile.position.y > GetScreenHeight() || projectile.position.x < 0 || projectile.position.y < 0)
		{
			projectile.isActive = false;
		}
	}
	




}
