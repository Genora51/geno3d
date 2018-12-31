#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>

namespace Geno3D
{
    class Object {
    public:
        void load(std::string str);
        void load(std::istream& stream);
        void sortFaces(const Eigen::Matrix3Xf& projected);
        void transform(Eigen::Matrix3f t);
        void calcNormals();
        Eigen::Matrix3Xf verts;
        std::vector<Eigen::Vector3i> faces;
        Eigen::Matrix3Xf normals;
    };
}