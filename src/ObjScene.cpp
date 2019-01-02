#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include "ObjScene.h"
#include "PerspCamera.h"
#include "SunLight.h"

namespace Geno3D
{
    ObjScene::ObjScene(std::string filename, float posy, float posz, std::string tex)
    : camera(new PerspCamera), camPos(posz, posy) {
        std::ifstream fst;
        fst.open(filename);
        object.load(fst);
        fst.close();
        if (tex.size() > 0) {
            sf::Texture t;
            t.loadFromFile(tex);
            object.loadTexture(t);
        }
    }

    void ObjScene::init(sf::RenderWindow *window, sf::Vector2i dims) {
        windowSize = dims;
        this->window = window;
        camera->displaySurface << windowSize.x / 2, windowSize.y / 2, windowSize.y / 2;
        camera->position(2) = camPos.x;
        camera->position(1) = camPos.y;
        Eigen::Vector3f lightDir(2, -2, 1);
        light.emplace_back(new SunLight(lightDir));
    }

    void ObjScene::handleInput() {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                window->close();
            }
        }
    }

    void ObjScene::update(float dt) {
        Eigen::Matrix3f r;
        r = Eigen::AngleAxisf(0.006, Eigen::Vector3f::UnitY());
        object.transform(r);
    }
    
    void ObjScene::draw(float in) {
        window->clear();
        auto shape = object.render(light, camera, windowSize.y);
        if (object.textured) {
            window->draw(shape, &object.texture);
        } else {
            window->draw(shape);
        }
        window->display();
    }
}
