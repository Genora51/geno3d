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
    ObjScene::ObjScene(std::string filename, float posy, float posz) : camPos(posz, posy) {
        std::ifstream fst;
        fst.open(filename);
        object.load(fst);
        fst.close();
    }

    void ObjScene::init(sf::RenderWindow *window, sf::Vector2i dims) {
        windowSize = dims;
        this->window = window;
        camera = new PerspCamera;
        camera->displaySurface << windowSize.x / 2, windowSize.y / 2, windowSize.y / 2;
        camera->position(2) = camPos.x;
        camera->position(1) = camPos.y;
        Eigen::Vector3f lightDir(2, -2, 1);
        light = new SunLight(lightDir);
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
        r = Eigen::AngleAxisf(0.003, Eigen::Vector3f::UnitY());
        object.transform(r);
    }
    
    void ObjScene::draw(float in) {
        window->clear();
        projected = camera->project(object.verts);
        object.sortFaces(projected);
        Eigen::VectorXf lighting = light->vertexLighting(object.normals);
        sf::VertexArray shape(sf::Triangles, object.faces.size() * 3);
        int j = 0;
        for (auto face : object.faces) {
            for (int i=0; i<3; ++i) {
                int f = face(i) - 1;
                auto vec = projected.col(f);
                shape[j].position = sf::Vector2f(vec(0), windowSize.y - vec(1));
                float lightStrength = lighting(f) * 255;
                shape[j].color = sf::Color(lightStrength, lightStrength, lightStrength);
                ++j;
            }
        }
        window->draw(shape);
        window->display();
        
    }
}
