#pragma once

#include <eigen3/Eigen/Dense>

#include "Camera.hpp"

namespace Geno3D
{
    /**
     * A perspective camera.
     * This class uses a perspective projection algorithm.
     */
    class PerspCamera : public Camera {
    public:
        /**
         * Project a set of points in 3D space onto the 2D camera.
         * This should project the points onto the camera's display surface,
         * using a perspective projection algorithm.
         * @param points a 3-row matrix holding points in 3D space
         * @see Camera
         * @see OrthCamera
         */
        Eigen::Matrix3Xf project(const Eigen::Matrix3Xf &points) override;
        ~PerspCamera() {}
    };
}