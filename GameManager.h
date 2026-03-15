#pragma once

#include "raylib.h"
#include "Entity.h"
#include "EventManager.h"

enum class Gamestate
{
	Paused, 
	Playing,
	GameOver

};

class GameManager
{
private:
	Gamestate currentGameState;
	EventManager eventManager;
	std::unique_ptr<Entity> player;
	float gameTimer;

public:
	GameManager();

	void Initialize(int screenWidth, int screenHeight, Vector2 screenCenter);
	void Update(float deltaTime);
	void Draw();
	void Reset();

	Gamestate GetState() const { return currentGameState; }
	void SetState(Gamestate newState) { currentGameState = newState; }

	
	

};

