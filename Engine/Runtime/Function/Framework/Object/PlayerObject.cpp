#include "PlayerObject.h"

#include "Function/Framework/Component/MovementComponent.h"
#include "Function/Framework/Component/SpriteRenderer.h"
#include "Resource/SpriteLoader.h"

#include <exception> 
#include <iostream>
#include <fstream>

void Player::Initialize(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filePath);
    }
    nlohmann::json data;
    file >> data;

    m_Entity = m_World.CreateEntity();

    if (!data.contains("Components") || !data["Components"].is_object()) {
        throw std::runtime_error("Components key missing or is not an object in Player JSON data.");
    }

    const auto& components = data["Components"];

    try {
        if (components.contains("SpriteRenderer")) {
            const auto& spriteRendererData = components.at("SpriteRenderer");
            auto textureSource = spriteRendererData.at("TextureSource").get<std::string>();
            GLib::Sprite* sprite = SpriteLoader::CreateSpriteFromFile(textureSource.c_str());
            m_Entity.AddComponent(SpriteRenderable(sprite));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error initializing SpriteRenderer: " << e.what() << std::endl;
    }

    try {
        if (components.contains("CommonComponent")) {
            const auto& commonComponentData = components.at("CommonComponent");
            float position = commonComponentData.at("Position").get<float>();
            float velocity = commonComponentData.at("Velocity").get<float>();
            m_Entity.AddComponent(CommonComponent(position, velocity));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error initializing CommonComponent: " << e.what() << std::endl;
    }

    try {
        if (components.contains("MovementComponent")) {
            const auto& movementComponentData = components.at("MovementComponent");
            float mass = movementComponentData.at("Mass").get<float>();
            float dragCoeff = movementComponentData.at("DragCoeff").get<float>();
            m_Entity.AddComponent(MovementComponent(mass, dragCoeff));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error initializing MovementComponent: " << e.what() << std::endl;
    }
}

