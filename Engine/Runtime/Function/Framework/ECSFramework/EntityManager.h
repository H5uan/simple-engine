#pragma once
#include "Entity.h"


namespace RXECS
{
    class EntityManager
    {
    public:
        Entity CreateEntity();
        void Destroy(Entity entity);

    private:
        int m_LastEntity = 0;
    };
}
