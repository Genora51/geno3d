#pragma once

#include <eigen3/Eigen/Dense>

#include "Camera.hpp"

namespace Geno3D
{
    /**
     * An orthographic camera.
     * This class uses an orthographic projection algorithm.
     */
    class OrthCamera : public Camera {
    public:
        /**
         * Project a set of points in 3D space onto the 2D camera.
         * This should project the points onto the camera's display surface,
         * using an orthographic projection algorithm.
         * @param points a 3-row matrix holding points in 3D space
         * @see Camera
         * @see PerspCamera
         */
        Eigen::Matrix3Xf project(const Eigen::Matrix3Xf &points) override;
        ~OrthCamera() {}
    };
}