#pragma once

#include "Component.h"
#include "entity.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "raylib.h"


class MovementComponent : public Component
{
public:
	Vector2 velocity;
	float speed;

	MovementComponent()
		: velocity{ 0.0f, 0.0f }, speed(1.0f)
	{}

	void Update(float deltaTime) override
	{
		auto* transform = whatHasTheComponent->GetComponent<TransformComponent>();
		if (!transform) return; 

		auto* stats = whatHasTheComponent->GetComponent<StatsComponent>();
		float movespeed = stats ? stats->speed : speed;

		transform->position.x += velocity.x * movespeed * deltaTime;
		transform->position.y += velocity.y * movespeed * deltaTime;

		if (transform->position.x < transform->radius)
			transform->position.x = transform->radius;
		if (transform->position.y < transform->radius)
			transform->position.y = transform->radius;
		if (transform->position.x > GetScreenWidth() - transform->radius)
			transform->position.x = GetScreenWidth() - transform->radius;
		if (transform->position.y > GetScreenHeight() - transform->radius)
			transform->position.y = GetScreenHeight() - transform->radius;


	}



};