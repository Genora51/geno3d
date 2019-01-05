#pragma once

#include <eigen3/Eigen/Dense>
#include "Transformable.h"

namespace Geno3D
{
    class Transformation : public Transformable {
    public:
        Transformation();
        void translate(float x, float y, float z) override;
        void scale(float m) override;
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
        Eigen::Matrix3Xf apply(Eigen::Matrix3Xf m) const;
        float determinant() const;
    private:
        Eigen::Matrix3f tMatrix;
    };
}