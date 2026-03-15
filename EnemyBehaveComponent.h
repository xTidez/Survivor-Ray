#pragma once

#include "Component.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "ShooterComponent.h"
#include "raylib.h"
#include "raymath.h"

class EnemyBehaveComponent : public Component
{
public:
	Entity* attackThis;

	EnemyBehaveComponent() : attackThis(nullptr) {}

	void Update(float deltaTime) override
	{
		if (!attackThis) return;

		auto* myTransform = whatHasTheComponent->GetComponent<TransformComponent>();
		auto* attackThisSTransform = attackThis->GetComponent<TransformComponent>();

		if (!myTransform || !attackThisSTransform) return;

		auto* myMovement = whatHasTheComponent->GetComponent<MovementComponent>();
		if (myMovement)
		{
			Vector2 toAttackTarget =
			{
				attackThisSTransform->position.x - myTransform->position.x,
				attackThisSTransform->position.y - myTransform->position.y

			};

			toAttackTarget = Vector2Normalize(toAttackTarget);
			myMovement->velocity = toAttackTarget;
		}

		Vector2 lookTowards =
		{
			attackThisSTransform->position.x - myTransform->position.x,
			attackThisSTransform->position.y - myTransform->position.y

		};

		myTransform->rotation = atan2f(lookTowards.y, lookTowards.x);

		auto* myShooter = whatHasTheComponent->GetComponent<ShooterComponent>();
		if (myShooter)
		{
			myShooter->targetToShoot = attackThisSTransform->position;
		}



	}




};