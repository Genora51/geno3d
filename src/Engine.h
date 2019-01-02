#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Scene.h"

namespace Geno3D
{
    class Engine {
    public:
        Engine(int width, int height, std::string title);
        std::shared_ptr<Scene> scene;
        void run();
    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock clock;
        sf::RenderWindow window;
        sf::Vector2i winSize;
    };
}