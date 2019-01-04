#pragma once

#include <eigen3/Eigen/Dense>

namespace Geno3D
{
    class Light {
    public:
        virtual Eigen::VectorXf vertexLighting(const Eigen::Matrix3Xf& normals) = 0;
        virtual ~Light() {};
    };
}