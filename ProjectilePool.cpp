
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

void ActivateBulletPool(ProjectilePool& projectilePool, int bulletNr, Vector2 firePostion, int bulletType, Vector2 direction,int shootingAtEnemyOrPlayer, Vector2 homingTarget)
{
	projectilePool[bulletNr].isActive = true;
	projectilePool[bulletNr].position = firePostion;
	projectilePool[bulletNr].typeOfProjectile = bulletType;
	projectilePool[bulletNr].shootingAtEnemyOrPlayer = shootingAtEnemyOrPlayer;

	switch (bulletType)
	{
		case 0:
			projectilePool[bulletNr].radius = 3.0f;
			projectilePool[bulletNr].damage = 10;
			break;

		case 1:
			projectilePool[bulletNr].radius = 5.0f;
			projectilePool[bulletNr].homingRocket.homingTargetLocation = homingTarget;
			//add line for activeduration
			projectilePool[bulletNr].homingRocket.agility = 3.0f;
			projectilePool[bulletNr].speedMultiplier = 1.2;
			projectilePool[bulletNr].damage = 20; 
			break;

		case 2:
			projectilePool[bulletNr].radius = 10.0f;
			projectilePool[bulletNr].explodingBullet.explotionRadius = 18.0f;
			projectilePool[bulletNr].explodingBullet.fuse = 7.0f;
			projectilePool[bulletNr].explodingBullet.readyToBlow = false;
			projectilePool[bulletNr].speedMultiplier = 0.8;
			projectilePool[bulletNr].damage = 25;
			projectilePool[bulletNr].explodingBullet.landAt = homingTarget;
			

			break;

	} 

	float bulletSpeed = projectilePool[bulletNr].speedStd * projectilePool[bulletNr].speedMultiplier;
	projectilePool[bulletNr].velocity =
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

		if (projectile.typeOfProjectile == 2)
		{
			projectile.explodingBullet.fuse -= deltaTime;
			
			if (projectile.explodingBullet.fuse <= 0)
			{
				projectile.explodingBullet.readyToBlow = true;

			}

			float distanceToTarget = Vector2Distance(projectile.position, projectile.explodingBullet.landAt);
			if (distanceToTarget < 1.0f)
			{

				projectile.velocity = {0,0};
				
			}

			
		}

		if (projectile.position.x > GetScreenWidth() || projectile.position.y > GetScreenHeight() || projectile.position.x < 0 || projectile.position.y < 0)
		{
			projectile.isActive = false;
		}
	}
	




}
