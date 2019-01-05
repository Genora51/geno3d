#pragma once

#include <SFML/Graphics.hpp>

namespace Geno3D
{
    class Scene {
    public:
        // TODO: objects, lights, camera, etc
        virtual void update(float dt) = 0;
        virtual void draw(float in) = 0;
        virtual void handleInput() = 0;
        virtual void init(sf::RenderWindow *window, sf::Vector2i dims) = 0;
        virtual ~Scene() {};
    };
}
