#include "Camera.hpp"
#include "Transformation.hpp"

namespace Geno3D
{
    Camera::Camera() {
        position = Eigen::Vector3f::Zero();
        orientation = Eigen::Vector3f::Zero();
        displaySurface << 0, 0, 1;
    }

    void Camera::translate(float x, float y, float z) {
        Eigen::Vector3f t(x, y, z);
        position += t;
    }

    void Camera::rotate(float x, float y, float z) {
        Eigen::Matrix3f r;
        r = Eigen::AngleAxisf(x, Eigen::Vector3f::UnitX())
          * Eigen::AngleAxisf(y, Eigen::Vector3f::UnitY())
          * Eigen::AngleAxisf(z, Eigen::Vector3f::UnitZ());
        orientation = r * orientation;
    }

    void Camera::scale(float m) {
        displaySurface(2) *= m;
    }

    void Camera::transform(const Transformation& t) {
        position = t.apply(position);
        orientation = t.apply(orientation);
    }

    void Camera::setPosition(float x, float y, float z) {
        position << x, y, z;
    }

    void Camera::setOrientation(float x, float y, float z) {
        orientation << x, y, z;
    }

    void Camera::setSurface(float x, float y, float z) {
        displaySurface << x, y, z;
    }
}