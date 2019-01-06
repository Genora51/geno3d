#pragma once

#include <eigen3/Eigen/Dense>
#include "Transformable.hpp"

namespace Geno3D
{
    /**
     * A compound transformation to apply to a Transformable.
     * Chain multiple transformations in order as a single transformation matrix.
     */
    class Transformation : public Transformable {
    public:
        Transformation();
        /**
         * Translate the transformation by a 3D vector.
         * This will not translate the object,
         * rather the rows of the transformation matrix will be translated.
         * @param x the amount to translate in the x-axis
         * @param y the amount to translate in the y-axis
         * @param z the amount to translate in the z-axis
         */
        void translate(float x, float y, float z) override;
        void scale(float m) override;
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
        /**
         * Apply the transformation to a matrix.
         * @param m the matrix to apply to.
         */
        Eigen::Matrix3Xf apply(Eigen::Matrix3Xf m) const;
        /**
         * Get the determinant of the transformation matrix.
         */
        float determinant() const;
    private:
        /// The transformation matrix
        Eigen::Matrix3f tMatrix;
    };
}