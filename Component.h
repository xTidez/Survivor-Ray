#pragma once



class Entity;

class Component
{
protected:
	Entity* whatHasTheComponent;
	bool enabled;

public:
	Component() : whatHasTheComponent(nullptr), enabled(true) {}
	virtual  ~Component() = default;

	virtual void Init(Entity* ownerEntity)
	{
		whatHasTheComponent = ownerEntity;
	}

	virtual void Update(float deltaTime) {}

	virtual void Draw() const {}

	void setEnabled(bool value) { enabled = value; }
	bool IsEnabled() const { return enabled; }

	Entity* GetWhatHasTheComponent() const { return whatHasTheComponent; }


};