#pragma once
#include "Core/Math/Vector2.h"
#include "..\..\Component\MovementComponent.h"
#include "Function/Framework/ECSFramework/ISystem.h"


class MovementSystem : public RXECS::ISystem
{
public:
    MovementSystem()
    {
        m_Signature.AddComponent<CommonComponent>();
        m_Signature.AddComponent<MovementComponent>();
    }

    ~MovementSystem() override = default;

    void Init() override;
    void Tick(float dt) override;
    void Render() override;
    
    void ApplyImpulse(CommonComponent* i_CommonComponent, MovementComponent* i_MovementComponent,
                      const Engine::Math::Vector2& impulse);
                      

};
