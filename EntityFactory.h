#pragma once

#include "entity.h"
#include "EventManager.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "MovementComponent.h"
#include "PlayerInputComponent.h"
#include "ShooterComponent.h"
#include "EnemyBehaveComponent.h"


namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(Vector2 spawnPosition, EventManager* eventManager, ProjectileManager& projectileManager)
	{
       
        auto player = std::make_unique<Entity>();
        auto* transform = player->AddComponent<TransformComponent>();
        transform->position = spawnPosition;
        transform->radius = 10.0f;

        auto* stats = player->AddComponent<StatsComponent>();
        stats->currentHealth = 100;
        stats->maxHealth = 100;
        stats->speed = 20.0f;
        stats->damage = 10;
        stats->fireRate = 1.0f;

        player->AddComponent<MovementComponent>();
        player->AddComponent<PlayerInputComponent>();
        player->AddComponent<ShooterComponent>(projectileManager);





        return player;

	}


    std::unique_ptr<Entity> CreateStdEnemy(Vector2 spawnPosition, Entity* attackTarget, ProjectileManager& projectileManager)
    {
        auto stdEnemy = std::make_unique<Entity>();

        auto* transform = stdEnemy->AddComponent<TransformComponent>();
        transform->position = spawnPosition;
        transform->radius = 10.0f;

        auto* stats = stdEnemy->AddComponent<StatsComponent>();

        stats->currentHealth = 40;
        stats->maxHealth = 40;
        stats->speed = 15.0f;
        stats->damage = 5;
        stats->fireRate = 1.0f;

        stdEnemy->AddComponent<MovementComponent>();

        auto* behaviour = stdEnemy->AddComponent<EnemyBehaveComponent>();
        behaviour->attackThis = attackTarget;

        auto* shooter = stdEnemy->AddComponent<ShooterComponent>();
        shooter->shootingAtEnemyOrPlayer = 1 ;

        return stdEnemy;

    }

    std::unique_ptr<Entity> CreateHeavyEnemy(Vector2 spawnPosition, Entity* attackTarget, ProjectileManager& projectileManager)
    {
        auto heavyEnemy = std::make_unique<Entity>();

        auto* transform = heavyEnemy->AddComponent<TransformComponent>();
        transform->position = spawnPosition;
        transform->radius = 10.0f;

        auto* stats = heavyEnemy->AddComponent<StatsComponent>();

        stats->currentHealth = 200;
        stats->maxHealth = 200;
        stats->speed = 10.0f;
        stats->damage = 20;
        stats->fireRate = 1.0f;

        heavyEnemy->AddComponent<MovementComponent>();

        auto* behaviour = heavyEnemy->AddComponent<EnemyBehaveComponent>();
        behaviour->attackThis = attackTarget;

        auto* shooter = heavyEnemy->AddComponent<ShooterComponent>();
        shooter->shootingAtEnemyOrPlayer = 1;
        shooter->TypeOfProjectile = 1;

        return heavyEnemy;

    }

}