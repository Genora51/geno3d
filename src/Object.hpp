#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>
#include <memory>
#include "Light.hpp"
#include "Camera.hpp"
#include "Transformable.hpp"

namespace Geno3D
{
    class Object : public Transformable {
    public:
        Object() : textured(false) {};
        void load(std::string str);
        void load(std::istream& stream);
        sf::VertexArray render(
            std::vector<std::unique_ptr<Light>>& lights,
            const std::shared_ptr<Camera>& camera,
            int winHeight
        );
        void loadTexture(sf::Texture texture);
        sf::Texture getTexture() { return texture; }
        bool isTextured() { return textured; }
        // Transformable
        void translate(float x, float y, float z) override;
        void scale(float m) override;
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
    private:
        void sortFaces(const Eigen::Matrix3Xf& projected);
        void calcNormals();
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