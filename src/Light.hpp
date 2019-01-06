#pragma once

#include <eigen3/Eigen/Dense>
#include "Transformable.hpp"

namespace Geno3D
{
    /**
     * The abstract light class.
     * Defines an individual light.
     */
    class Light : public Transformable {
    public:
        /**
         * Calculate the lighting on each vertex of an object.
         * Uses vertex normals to calculate the clamped light intensity on each vertex.
         * @param normals a 3 by X matrix containing the normals as 3D unit vectors
         * @see Object::render()
         */
        virtual Eigen::VectorXf vertexLighting(const Eigen::Matrix3Xf& normals) = 0;
        virtual ~Light() {};
    };
}