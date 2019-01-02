#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>
#include <memory>
#include "Light.h"
#include "Camera.h"

namespace Geno3D
{
    class Object {
    public:
        Object() : textured(false) {};
        void load(std::string str);
        void load(std::istream& stream);
        void sortFaces(const Eigen::Matrix3Xf& projected);
        sf::VertexArray render(
            std::vector<std::unique_ptr<Light>>& light,
            std::shared_ptr<Camera> camera,
            int winHeight
        );
        void transform(Eigen::Matrix3f t);
        void calcNormals();
        void loadTexture(sf::Texture texture);
        sf::Texture texture;
        bool textured;
        Eigen::Matrix3Xf verts;
        std::vector<sf::Vector2f> uvMap;
        std::vector<sf::Vector2f> uvTexMap;
        std::vector<Eigen::Vector3i> faces;
        Eigen::Matrix3Xf normals;
        std::vector<Eigen::Vector3i> texCoords;
    };
}