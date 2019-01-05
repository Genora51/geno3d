#pragma once

#include <eigen3/Eigen/Dense>
#include "Light.hpp"

namespace Geno3D
{
    class SunLight : public Light {
    public:
        SunLight(Eigen::Vector3f direction);
        Eigen::VectorXf vertexLighting(const Eigen::Matrix3Xf& normals) override;
        Eigen::Vector3f getDirection() { return direction; }
        void setDirection(float x, float y, float z);
        void translate(float x, float y, float z) override;
        void scale(float m) override {};
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
        ~SunLight() {}
    private:
        Eigen::Vector3f direction;
    };
}