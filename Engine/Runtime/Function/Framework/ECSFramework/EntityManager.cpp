#include "EntityManager.h"

namespace RXECS
{
    Entity EntityManager::CreateEntity()
    {
        m_LastEntity++;
        return {m_LastEntity};
    }

    void EntityManager::Destroy(RXECS::Entity entity)
    {
    }
}
