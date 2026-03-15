#pragma once

#include "Component.h"
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

class Entity
{
private:
    std::vector<std::unique_ptr<Component>> components;
    std::unordered_map<std::type_index, Component*> componentMap;
    bool active;

public:
    Entity() : active(true) {}

    Entity(const Entity&) = delete;
    Entity& operator=(const Entity&) = delete;

    // Allow move
    Entity(Entity&& other) noexcept
        : components(std::move(other.components)),
        componentMap(std::move(other.componentMap)),
        active(other.active)
    {
        for (auto& component : components) 
        {
            component->Init(this);
        }
            
    }

    Entity& operator=(Entity&& other) noexcept
    {
        components = std::move(other.components);
        componentMap = std::move(other.componentMap);
        active = other.active;
        for (auto& component : components)
        {
            component->Init(this);
        }
        return *this;
    }
   
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        T* component = new T(std::forward<Args>(args)...);
        component->Init(this);

        components.push_back(std::unique_ptr<Component>(component));
        componentMap[typeid(T)] = component;

        return component;
    }

  
    template<typename T>
    T* GetComponent()
    {
        auto it = componentMap.find(typeid(T));
        if (it != componentMap.end())
        {
            return static_cast<T*>(it->second);
        }
        return nullptr;
    }

  
    template<typename T>
    bool HasComponent()
    {
        return componentMap.find(typeid(T)) != componentMap.end();
    }

   
    template<typename T>
    void RemoveComponent()
    {
        auto it = componentMap.find(typeid(T));
        if (it != componentMap.end())
        {   
            Component* toRemove = it->second;
            componentMap.erase(it);

           
            components.erase(
                std::remove_if(components.begin(), components.end(),
                    [toRemove](const std::unique_ptr<Component>& c) {
                        return c.get() == toRemove;
                    }),
                components.end()
            );
        }
    }

   
    void Update(float deltaTime)
    {
        if (!active) return;

        for (auto& component : components)
        {
            if (component->IsEnabled())
            {
                component->Update(deltaTime);
            }
        }
    }

    
    void Draw() const
    {
        if (!active) return;

        for (auto& component : components)
        {
            if (component->IsEnabled())
            {
                component->Draw();
            }
        }
    }

   
    void SetActive(bool value) { active = value; }
    bool IsActive() const { return active; }
};

