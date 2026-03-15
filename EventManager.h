#pragma once

#include <functional>
#include <vector>

struct HealthChangedEvent
{
    int newHealth;
    int maxHealth;
    int delta;
};

class EventManager
{
private:
    std::vector<std::function<void(const HealthChangedEvent&)>> healthChangedListeners;

public:
    void SubscribeToHealthChanged(std::function<void(const HealthChangedEvent&)> callback)
    {
        healthChangedListeners.push_back(callback);
    }

    void TriggerHealthChanged(const HealthChangedEvent& event)
    {
        for (auto& listener : healthChangedListeners)
        {
            listener(event);
        }
    }
};
