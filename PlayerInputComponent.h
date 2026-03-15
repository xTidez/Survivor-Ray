#pragma once

#include "Component.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "ShooterComponent.h"
#include "raylib.h"
#include "raymath.h"

class PlayerInputComponent : public Component
{
public:

	void Update(float deltaTime) override
	{
		auto* movement = whatHasTheComponent->GetComponent<MovementComponent>();
		auto* position = whatHasTheComponent->GetComponent<TransformComponent>();

		if (!movement || !position) return;

		// reset to 0 when no keydown
		movement->velocity = { 0,0 };

		if (IsKeyDown(KEY_W)) movement->velocity.y = -1.0f;
		if (IsKeyDown(KEY_A)) movement->velocity.x = -1.0f;
		if (IsKeyDown(KEY_S)) movement->velocity.y = 1.0f;
		if (IsKeyDown(KEY_D)) movement->velocity.x = 1.0f;

		Vector2 mousePosition = GetMousePosition();
		Vector2 lookAt =
		{
			mousePosition.x - position->position.x,
			mousePosition.y - position->position.y
		};

		position->rotation = atan2f(lookAt.y, lookAt.x);

		auto* shooter = whatHasTheComponent->GetComponent<ShooterComponent>();
		if (shooter) shooter->targetToShoot = mousePosition;
	}


};