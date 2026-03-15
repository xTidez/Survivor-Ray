#pragma once

#include "raylib.h"
#include "ProjectilePool.h"


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

	void Shoot(Vector2 fireFrom, Vector2 direction, int bulletType)
	{
		int projectileIndex = FindBulletInPool(projectilePool);
		if (projectileIndex < 0) return;




	};



};