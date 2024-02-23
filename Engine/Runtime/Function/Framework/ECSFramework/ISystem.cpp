#include "ISystem.h"

namespace RXECS
{
    void ISystem::RegisterWorld(World* world) { m_ParentWorld = world; }

    void ISystem::RegisterEntity(RXECS::Entity const& entity) { m_RegisteredEntities.push_back(entity); }

    void ISystem::UnRegisterEntity(RXECS::Entity const& entity)
    {
        for (auto it = m_RegisteredEntities.begin(); it != m_RegisteredEntities.end(); ++it)
        {
            const Entity e = *it;
            if (e.id == entity.id)
            {
                m_RegisteredEntities.erase(it);
                return;
            }
        }
    }

    ComponentHash ISystem::GetSignature() const { return m_Signature; }
}
