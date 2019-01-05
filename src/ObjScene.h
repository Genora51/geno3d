#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include "Scene.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"

namespace Geno3D
{
    class ObjScene : public Scene {
    public:
        ObjScene(std::string filename, float posy, float posz, std::string tex);
        ObjScene(std::string filename, float posy, float posz);
        void init(sf::RenderWindow *window, sf::Vector2i dims) override;
        void draw(float in) override;
        void update(float dt) override;
        void handleInput() override;
        ~ObjScene() {}
    private:
        sf::RenderWindow *window;
        Object object;
        std::shared_ptr<Camera> camera;
        std::vector<std::unique_ptr<Light>> lights;
        sf::Vector2i windowSize;
    };
}
