#pragma once

#include "Component.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "StatsComponent.h"
#include "raylib.h"
#include "raymath.h"
#include "ProjectileManager.h"

class ShooterComponent : public Component
{
	public:
		float cooldown;
		ProjectileManager& projectileManager;

		ShooterComponent(ProjectileManager& myManagerOfProjectiles) : cooldown(0.0f), projectileManager(myManagerOfProjectiles)
		{
		
		}

		Vector2 GetFirepoint() const
		{
			auto* transform = whatHasTheComponent->GetComponent<TransformComponent>();
			if (!transform) return { 0,0 };

			return
			{
				transform->position.x + cosf(transform->rotation) * transform->radius,
				transform->position.y + sinf(transform->rotation) * transform->radius

			};

		}
			
		bool CanShoot() const
		{
			return cooldown <= 0.0f;
		}

		void ResetCooldown() 
		{
			auto* stats = whatHasTheComponent->GetComponent<StatsComponent>();
			float fireRate = stats ? stats->fireRate : 10.0f;
			cooldown = 1.0f / fireRate;
		}


		void Update(float deltaTime) override
		{
			cooldown -= deltaTime;

			if (cooldown <= 0.0f)
			{
				auto* transform = whatHasTheComponent->GetComponent<TransformComponent>();
				if (!transform) return;

				auto* entityStats = whatHasTheComponent->GetComponent<StatsComponent>();
				float fireRate = entityStats ? entityStats->fireRate : 15.0f;

				Vector2 firePoint = GetFirepoint();
				Vector2 direction =
				{
					cosf(transform->rotation),
					sinf(transform->rotation)

				};

				projectileManager.Shoot(firePoint, direction, 0);

				cooldown = 1.0f / fireRate;
			}
				
		}


};