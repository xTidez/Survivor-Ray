#pragma once

#include "raylib.h"
#include "Entity.h"
#include "EntityFactory.h"
#include <vector>
#include <memory>


class WaveManager
{
public:

	int currentWave;
	int enemiesTospawn;
	float currentWaveTimer;
	float spawnTimer;
	float spawnIntervall;
	float waveIncrementTimer;
	float minSpawnDistanceFromPlayer;
	bool isWavePlaying;

	//difficultyscaling
	float scaleNrEnemiesPerWave;
	float scaleEnemyStats;

	WaveManager()
		:currentWave(0), enemiesTospawn(5), currentWaveTimer(0.0f), waveIncrementTimer(30.0f), minSpawnDistanceFromPlayer(200.0f), isWavePlaying(false), scaleNrEnemiesPerWave(0.2f), scaleEnemyStats(0.1f), spawnIntervall(0.3), spawnTimer(0.0f)
	{
	}


	void StartNextWave()
	{
		currentWave++;
		currentWaveTimer = 0.0f;
		enemiesTospawn = (int)(5 * (1.0f + currentWave * scaleNrEnemiesPerWave));
		isWavePlaying = true;

	}

	bool IsWaveComplete(int aliveCount) const
	{
		return aliveCount <= 0 && enemiesTospawn <= 0;
	}

	Vector2 GetSpawnPosition(Vector2 playerPosition, int screenWidth, int screenHeight)
	{
		Vector2 spawnPosition;
		float  screenMargin = 20.0f;

		do
		{
			spawnPosition.x = (float)GetRandomValue((int)screenMargin, screenWidth - (int)screenMargin);
			spawnPosition.y = (float)GetRandomValue((int)screenMargin, screenHeight - (int)screenMargin);

		} while (Vector2Distance(spawnPosition, playerPosition) < minSpawnDistanceFromPlayer);

		return spawnPosition;
	}


	float GetStatScaleValue() const
	{
		return 1.0f + currentWave * scaleEnemyStats;

	}

	int RandomizeSwitchTrigger()
	{
		int result = GetRandomValue(1, 100);

		if (result <= 70) return 0;
		else if (result <= 71) return 1;
		else return 0; //just failsafe 
		

	}

	void Update(float deltaTime, Vector2 playerPosition, int screenWidth, int screenHeight,
		Entity* player, ProjectileManager& projectileManager,
		std::vector<std::unique_ptr<Entity>>& enemies)
	{
		if (isWavePlaying)
		{
			currentWaveTimer += deltaTime;
			spawnTimer += deltaTime;

			if (spawnTimer >= spawnIntervall)
			{
				spawnTimer = 0.0f;
				if (enemiesTospawn > 0)
				{
					Vector2 spawnPosition = GetSpawnPosition(playerPosition, screenWidth, screenHeight);
					float statScale = GetStatScaleValue();

					switch (RandomizeSwitchTrigger())
					{
					case 0:
						enemies.push_back(EntityFactory::CreateStdEnemy(spawnPosition, player, projectileManager, statScale));
						break;
					case 1:
						enemies.push_back(EntityFactory::CreateHeavyEnemy(spawnPosition, player, projectileManager, statScale));
						break;

					}

					enemiesTospawn--;
				}
			}

			if (IsWaveComplete((int)enemies.size()))
			{
				StartNextWave();

			}

		}

		else
		{
			currentWaveTimer += deltaTime;

			if (currentWaveTimer >= waveIncrementTimer)

				StartNextWave();


		}
	}













};