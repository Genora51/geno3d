#pragma once

#include <eigen3/Eigen/Dense>

namespace Geno3D
{
    class Camera {
    public:
        Camera() {
            position = Eigen::Vector3f::Zero();
            orientation = Eigen::Vector3f::Zero();
            displaySurface << 0, 0, 1;
        };
        Eigen::Vector3f position;
        Eigen::Vector3f orientation;
        Eigen::Vector3f displaySurface;
        virtual Eigen::Matrix3Xf project(const Eigen::Matrix3Xf &points) = 0;
        virtual ~Camera() {};
    };
}
