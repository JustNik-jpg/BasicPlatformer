#pragma once

#include <bitset>
#include <array>
#include <algorithm>
#include <memory>
#include <vector>

class Component;

class Entity;

constexpr std::size_t maxCom = 32;

using ComponentID = std::size_t;
using ComponentBitset = std::bitset<maxCom>;
using ComponentArray = std::array<Component*, maxCom>;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template<typename T>
inline ComponentID getComponentTypeID() {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

class Component {
public:
    Entity *entity;

    virtual ~Component(){};

    virtual void update(){};
};

class Entity {
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentBitset componentBitset;
    ComponentArray componentArray;
public:
    void update() {
        for (auto component: componentArray) {
            component->update();
        }
    }

    bool isActive() {
        return active;
    }

    void destroy() {
        active = false;
    }

    template<typename T>
    bool hasComponent() const {
        return componentBitset[getComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs>
    T &addComponent(TArgs &&... args) {
        T* component(new T(std::forward<TArgs>(args)...));
        component->entity = this;
        std::unique_ptr<Component> uPtr{ component };
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()] = component;
        componentBitset[getComponentTypeID<T>()] = true;

        return *component;
    }

    template<typename T>
    T &getComponent() const {
        auto ptr = componentArray[getComponentTypeID<T>()];
        return *static_cast<T *>(ptr);
    }
};

class Manager {

private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update() {
        for (auto &entity: entities) {
            entity->update();
        }
    }

    void refresh() {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
                                      [](const std::unique_ptr<Entity> &entity) {
                                          return !entity->isActive();
                                      }), std::end(entities));
    }

    Entity *addEntity() {
        auto *e = new Entity();
        std::unique_ptr<Entity> ePointer{e};
        entities.emplace_back(std::move(ePointer));
        return e;
    }
};
