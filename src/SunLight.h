#pragma once

#include <eigen3/Eigen/Dense>
#include "Light.h"

namespace Geno3D
{
    class SunLight : public Light {
    public:
        SunLight(Eigen::Vector3f direction);
        Eigen::Vector3f direction;
        Eigen::VectorXf vertexLighting(Eigen::Matrix3Xf normals) override;
        ~SunLight() {}
    };
}