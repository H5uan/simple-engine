#pragma once
#include <array>
#include <map>
#include "Entity.h"
#include "EntityMap.h"

namespace RXECS
{
    template <typename ComponentType>
    struct ComponentData
    {
        unsigned int size = 1;
        std::array<ComponentType, MAX_NUMBER_OF_COMPONENTS>* data;
    };

    class BaseComponentManager
    {
    public:
        BaseComponentManager() = default;
        virtual ~BaseComponentManager() = default;
        BaseComponentManager(const BaseComponentManager&) = default;
        BaseComponentManager& operator=(const BaseComponentManager&) = default;
        BaseComponentManager(BaseComponentManager&&) = default;
        BaseComponentManager& operator=(BaseComponentManager&&) = default;
    };

    template <typename ComponentType>
    class ComponentManager : public BaseComponentManager
    {
    public:
        using LookupType = ComponentType;

        ComponentManager(): m_EntityMap()
        {
            m_ComponentData.data = static_cast<std::array<ComponentType, 1024>*>(malloc(sizeof(ComponentType) * 1024));
        }

        ComponentInstance AddComponent(Entity entity, ComponentType& component)
        {
            ComponentInstance newInstance = m_ComponentData.size;
            m_ComponentData.data->at(newInstance) = component;
            m_EntityMap.Add(entity, newInstance);
            ++m_ComponentData.size;
            return newInstance;
        }

        void DestroyComponent(Entity entity)
        {
            ComponentInstance instance = m_EntityMap.GetInstance(entity);

            // Move last component to the deleted position to maintain data coherence
            ComponentInstance lastComponent = m_ComponentData.size - 1;
            m_ComponentData.data[instance] = m_ComponentData.data[lastComponent];
            const Entity lastEntity = m_EntityMap.GetEntity(lastComponent);

            // Update our map
            m_EntityMap.Remove(entity);
            m_EntityMap.Update(lastEntity, instance);

            --m_ComponentData.size;
        }

        LookupType* LookUp(Entity entity)
        {
            ComponentInstance instance = m_EntityMap.GetInstance(entity);
            return &m_ComponentData.data->at(instance);
        }

    private:
        ComponentData<ComponentType> m_ComponentData;
        EntityMap m_EntityMap;
    };
}
