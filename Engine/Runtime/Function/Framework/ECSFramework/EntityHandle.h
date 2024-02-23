#pragma once
#include "ComponentHandle.h"
#include "entity.h"
#include "world.h"

namespace RXECS
{
    struct EntityHandle
    {
        Entity entity;
        World* world;

        void Destroy() { world->DestroyEntity(entity); }

        template <typename ComponentType>
        void AddComponent(ComponentType&& component)
        {
            world->AddComponent<ComponentType>(entity, std::forward<ComponentType>(component));
        }

        template <typename ComponentType>
        void RemoveComponent() const
        {
            world->RemoveComponent<ComponentType>(entity);
        }

        template <typename ComponentType>
        ComponentHandle<ComponentType> GetComponent()
        {
            ComponentHandle<ComponentType> handle;
            world->Unpack(entity, handle);
            return handle;
        }
    };
}
