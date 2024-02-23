#pragma once
#include "Function/Framework/ECSFramework/ComponentHandle.h"
#include "Function/Framework/ECSFramework/EntityHandle.h"
#include "Function/Framework/ECSFramework/ISystem.h"
#include "Function/Framework/Systems/Movement/Movement.h"

static bool KEY_A_PRESSED;
static bool KEY_D_PRESSED;
static bool KEY_W_PRESSED;
static bool KEY_S_PRESSED;

class PlayerSystem : public RXECS::ISystem
{
public:
    PlayerSystem()
    {
        m_Signature.AddComponent<MovementComponent>();
    }

    ~PlayerSystem() override = default;

    void Init() override;
    void Tick(float dt) override;
    void Render() override;
};
