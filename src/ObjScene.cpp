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
    : ObjScene(filename, posy, posz) {
        sf::Texture t;
        t.loadFromFile(tex);
        object.loadTexture(t);
    }

    ObjScene::ObjScene(std::string filename, float posy, float posz)
    : camera(new PerspCamera) {
        std::ifstream fst;
        fst.open(filename);
        object.load(fst);
        fst.close();
        camera->setPosition(0, posy, posz);
            sf::Texture t;
    }

    void ObjScene::init(sf::RenderWindow *window, sf::Vector2i dims) {
        windowSize = dims;
        this->window = window;
        camera->setSurface(windowSize.x / 2, windowSize.y / 2, windowSize.y / 2);
        Eigen::Vector3f lightDir(2, -2, 1);
        lights.emplace_back(new SunLight(lightDir));
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
        object.rotate(0, 0.006, 0);
    }

    void ObjScene::draw(float in) {
        window->clear();
        auto shape = object.render(lights, camera, windowSize.y);
        if (object.isTextured()) {
            sf::Texture tex(object.getTexture());
            window->draw(shape, &tex);
        } else {
            window->draw(shape);
        }
        window->display();
    }
}
