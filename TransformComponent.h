#pragma once
#include "Component.h"
#include "raylib.h"

class TransformComponent : public Component
{
public:
	Vector2 position;
	float rotation;
	float radius;

	TransformComponent()
		: position{ 0, 0 }, rotation(0.0f), radius(0.0f) 
	{ }



};