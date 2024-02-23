#include "world.h"
#include <iostream>
#include "EntityHandle.h"

namespace RXECS
{
    World::World(std::unique_ptr<EntityManager> entityManager) : m_EntityManager(std::move(entityManager))
    {
    }

    void World::Init() const
    {
        for (auto& system : m_Systems)
        {
            system->Init();
        }
    }

    void World::Tick(float dt) const
    {
        for (auto& system : m_Systems)
        {
            system->Tick(dt);
        }
    }

    void World::Render() const
    {
        for (auto& system : m_Systems)
        {
            system->Render();
        }
    }

    EntityHandle World::CreateEntity() { return {m_EntityManager->CreateEntity(), this}; }

    void World::DestroyEntity(RXECS::Entity entity) const
    {
        for (auto& system : m_Systems)
        {
            system->UnRegisterEntity(entity);
        }

        m_EntityManager->Destroy(entity);
    }

    void World::AddSystem(std::unique_ptr<RXECS::ISystem> system)
    {
        system->RegisterWorld(this);
        m_Systems.push_back(std::move(system));
    }

    void World::UpdateEntityHash(RXECS::Entity const& entity, RXECS::ComponentHash oldHash)
    {
        ComponentHash newHash = m_EntityGroup[entity];

        for (const auto& system : m_Systems)
        {
            const ComponentHash systemSignature = system->GetSignature();
            if (newHash.IsNewMatch(oldHash, systemSignature))
            {
                // We match but didn't match before
                system->RegisterEntity(entity);
            }
            else if (newHash.IsNoLongerMatched(oldHash, systemSignature))
            {
                system->UnRegisterEntity(entity);
            }
        }
    }
}
