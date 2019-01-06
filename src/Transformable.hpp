#pragma once

namespace Geno3D
{
    class Transformation;
    /**
     * An interface for transforming points and vectors in 3D space.
     */
    class Transformable {
    public:
        /**
         * Translate by a 3D vector.
         * @param x the amount to translate in the x-axis
         * @param y the amount to translate in the y-axis
         * @param z the amount to translate in the z-axis
         */
        virtual void translate(float x, float y, float z) = 0;
        /**
         * Scale by a factor.
         * @param m the factor to scale by
         */
        virtual void scale(float m) = 0;
        /**
         * Rotate by Euler angles, in radians.
         * @param x the angle to rotate by about the x-axis
         * @param y the angle to rotate by about the y-axis
         * @param z the angle to rotate by about the z-axis
         */
        virtual void rotate(float x, float y, float z) = 0;
        /**
         * Transform by a compound transformation.
         * @param t the transformation to apply
         */
        virtual void transform(const Transformation& t) = 0;
    };
}