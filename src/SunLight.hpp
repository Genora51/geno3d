#pragma once

#include <eigen3/Eigen/Dense>
#include "Light.hpp"

namespace Geno3D
{
    /**
     * A directional light class.
     */
    class SunLight : public Light {
    public:
        /**
         * Construct a sun light with a direction vector.
         * @param direction the 3D direction vector of the light
         * @see getDirection()
         * @see setDirection()
         */
        SunLight(Eigen::Vector3f direction);
        Eigen::VectorXf vertexLighting(const Eigen::Matrix3Xf& normals) override;
        /**
         * Get the current direction of the light as a 3D unit vector.
         * @see setDirection()
         */
        Eigen::Vector3f getDirection() { return direction; }
        /**
         * Set the direction of the light as a 3D vector.
         * @param x the magnitude of the direction in the x-axis
         * @param y the magnitude of the direction in the y-axis
         * @param z the magnitude of the direction in the z-axis
         * @see getDirection()
         */
        void setDirection(float x, float y, float z);
        void translate(float x, float y, float z) override;
        void scale(float m) override {};
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
        ~SunLight() {}
    private:
        /// The 3d direction unit vector of the light
        Eigen::Vector3f direction;
    };
}