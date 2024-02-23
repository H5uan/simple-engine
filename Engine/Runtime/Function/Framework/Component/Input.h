#pragma once
#include "Core/Engine.h"
#include "Core/Math/Vector2.h"


struct KeyboardInputComponent : RXECS::Component<KeyboardInputComponent>
{
    KeyboardInputComponent() = default;
    bool keyAPressed = false;
    bool keyDPressed = false;
    bool keyQPressed = false;
    bool keySPressed = false;
    bool keyWPressed = false;
};
