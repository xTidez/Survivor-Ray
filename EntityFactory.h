#pragma once

#include "entity.h"
#include "EventManager.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "MovementComponent.h"
#include "PlayerInputComponent.h"


namespace EntityFactory
{
	std::unique_ptr<Entity> CreatePlayer(Vector2 spawnPosition, EventManager* eventManager)
	{
       
        auto player = std::make_unique<Entity>();
        auto* transform = player->AddComponent<TransformComponent>();
        transform->position = spawnPosition;
        transform->radius = 10.0f;

        auto* stats = player->AddComponent<StatsComponent>();
        stats->currentHealth = 100;
        stats->maxHealth = 100;
        stats->speed = 10.0f;
        stats->damage = 10;
        stats->fireRate = 7.0f;

        player->AddComponent<MovementComponent>();
        player->AddComponent<PlayerInputComponent>();






        return player;

	}






}