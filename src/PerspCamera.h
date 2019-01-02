#pragma once

#include <eigen3/Eigen/Dense>

#include "Camera.h"

namespace Geno3D
{
    class PerspCamera : public Camera {
    public:
        Eigen::Matrix3Xf project(const Eigen::Matrix3Xf &points) override;
        ~PerspCamera() {}
    };
}