#pragma once
#include <memory>
#include "Component.h"
#include "ComponentHandle.h"
#include "ComponentManager.h"
#include "ComponentHash.h"
#include "entity.h"
#include "EntityManager.h"
#include "ISystem.h"

namespace RXECS
{
    struct EntityHandle;

    class World
    {
    public:
        World() = default;

        explicit World(std::unique_ptr<EntityManager> entityManager);

        /*
         * Should be called before the first update, but after instantiation
         */
        void Init() const;

        /*
         * Update game logic. This is unrelated to a frame
         */
        void Tick(float dt) const;
        /*
         * Render a frame.
         */
        void Render() const;
        EntityHandle CreateEntity();
        void AddSystem(std::unique_ptr<ISystem> system);
        void DestroyEntity(Entity entity) const;


        template <typename ComponentType>
        void AddCustomComponentManager(std::unique_ptr<ComponentManager<ComponentType>> manager)
        {
            const int family = GetComponentFamily<ComponentType>();
            if (family >= m_ComponentManagers.size())
            {
                m_ComponentManagers.resize(family + 1);
            }
            m_ComponentManagers[family] = manager;
        }

        template <typename ComponentType>
        void AddComponent(Entity const& entity, ComponentType&& component)
        {
            ComponentManager<ComponentType>* manager = GetComponentManager<ComponentType>();
            manager->AddComponent(entity, component);

            ComponentHash oldHash = m_EntityGroup[entity];
            m_EntityGroup[entity].AddComponent<ComponentType>();

            UpdateEntityHash(entity, oldHash);
        }

        template <typename ComponentType>
        void RemoveComponent(Entity const& entity)
        {
            ComponentManager<ComponentType>* manager = GetComponentManager<ComponentType>();
            ComponentHandle<ComponentType> component = manager->LookUp(entity);
            component.Destroy();

            ComponentHash oldHash = m_EntityGroup[entity];
            m_EntityGroup[entity].RemoveComponent<ComponentType>();

            UpdateEntityHash(entity, oldHash);
        }

        template <typename ComponentType, typename... Args>
        void Unpack(Entity e, ComponentHandle<ComponentType>& handle, ComponentHandle<Args>&... args)
        {
            typedef ComponentManager<ComponentType> ComponentManagerType;
            auto mgr = GetComponentManager<ComponentType>();
            handle = ComponentHandle<ComponentType>(e, mgr->LookUp(e), mgr);

            // Recurse
            Unpack<Args...>(e, args...);
        }

        // Base case
        template <typename ComponentType>
        void Unpack(Entity e, ComponentHandle<ComponentType>& handle)
        {
            typedef ComponentManager<ComponentType> ComponentManagerType;
            auto mgr = GetComponentManager<ComponentType>();
            handle = ComponentHandle<ComponentType>(e, mgr->LookUp(e), mgr);
        }

    private:
        std::unique_ptr<EntityManager> m_EntityManager;
        std::vector<std::unique_ptr<ISystem>> m_Systems;
        std::vector<std::unique_ptr<BaseComponentManager>> m_ComponentManagers;
        std::map<Entity, ComponentHash> m_EntityGroup;

        void UpdateEntityHash(Entity const& entity, ComponentHash oldHash);

        template <typename ComponentType>
        ComponentManager<ComponentType>* GetComponentManager()
        {
            const int family = GetComponentFamily<ComponentType>();

            if (family >= m_ComponentManagers.size())
            {
                m_ComponentManagers.resize(family + 1);
            }

            if (!m_ComponentManagers[family])
            {
                m_ComponentManagers[family] = std::make_unique<ComponentManager<ComponentType>>();
            }

            return static_cast<ComponentManager<ComponentType>*>(m_ComponentManagers[family].get());
        }
    };
}
