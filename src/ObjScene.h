#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"

namespace Geno3D
{
    class ObjScene : public Scene {
    public:
        ObjScene(std::string filename, float posy, float posz, std::string tex="");
        void init(sf::RenderWindow *window, sf::Vector2i dims) override;
        void draw(float in) override;
        void update(float dt) override;
        void handleInput() override;
    private:
        sf::RenderWindow *window;
        Object object;
        Camera *camera;
        Light *light;
        sf::Vector2i windowSize;
        sf::Vector2f camPos;
    };
}
