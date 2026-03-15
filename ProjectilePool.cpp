
#include "ProjectilePool.h"
#include "raylib.h"
#include "raymath.h"




int FindBulletInPool(ProjectilePool projPool)
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

void ActivateBulletPool(ProjectilePool projPool, int bulletNr, Vector2 firePostion, int type, Vector2 velocity, Player& player)
{
	projPool[bulletNr].isActive = true;
	projPool[bulletNr].position = firePostion;
	projPool[bulletNr].typeOfProjectile = type;

	switch (type)
	{
		case 0:
			projPool[bulletNr].stdBullet.radius = 2.0f;
			projPool[bulletNr].stdBullet.activeDuration = 5.0f;
			projPool[bulletNr].stdBullet.damage = 10;
			break;

		case 1:
			projPool[bulletNr].homingRocket.homingTargetLocation = player.playerPosition;
			projPool[bulletNr].homingRocket.damage = 20;
			break;

		case 2:
			projPool[bulletNr].explodingBullet.explotionRadius = 10.0f;
			projPool[bulletNr].explodingBullet.activeDuration = 5.0f;
			projPool[bulletNr].explodingBullet.damage = 25;
			break;

	} 

}

void UpdateProjectilePool(ProjectilePool& projPool, const Player& player, float deltaTime)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		auto& projectile = projPool[i];
		if (!projectile.isActive) continue;

		if (projectile.typeOfProjectile == 1) {

			projectile.homingRocket.homingTargetLocation = player.playerPosition;

			Vector2 toTarget = {
				projectile.homingRocket.homingTargetLocation.x - projectile.position.x,
				projectile.homingRocket.homingTargetLocation.y - projectile.position.y
			};

		}

		projectile.position.x += projectile.velocity.x * deltaTime;
		projectile.position.y += projectile.velocity.y * deltaTime;

		
		if (projectile.position.x > GetScreenWidth() || projectile.position.y < GetScreenHeight())
		{
			projectile.isActive = false;
		}
	}
	




}
