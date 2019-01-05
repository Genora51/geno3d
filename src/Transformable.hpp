#pragma once

namespace Geno3D
{
    class Transformation;

    class Transformable {
    public:
        virtual void translate(float x, float y, float z) = 0;
        virtual void scale(float m) = 0;
        virtual void rotate(float x, float y, float z) = 0;
        virtual void transform(const Transformation& t) = 0;
    };
}