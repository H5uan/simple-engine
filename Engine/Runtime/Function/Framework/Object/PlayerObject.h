#pragma once
#include "Function/Framework/ECSFramework/RXECS.h"
#include "nlohmann/json.hpp"

class Player
{
public:
    Player(RXECS::World& world): m_World(world)
    {
    }

    void Initialize(const std::string& filePath);

private:
    RXECS::World& m_World;
    RXECS::EntityHandle m_Entity{};
};
