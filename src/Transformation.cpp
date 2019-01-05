#include "Transformation.h"

namespace Geno3D
{
    Transformation::Transformation() : tMatrix(Eigen::Matrix3f::Identity()) {}

    void Transformation::translate(float x, float y, float z) {
        Eigen::Vector3f translation(x, y, z);
        tMatrix.colwise() += translation;
    }

    void Transformation::scale(float m) {
        tMatrix *= m;
    }

    void Transformation::rotate(float x, float y, float z) {
        Eigen::Matrix3f r;
        r = Eigen::AngleAxisf(x, Eigen::Vector3f::UnitX())
          * Eigen::AngleAxisf(y, Eigen::Vector3f::UnitY())
          * Eigen::AngleAxisf(z, Eigen::Vector3f::UnitZ());
        tMatrix = r * tMatrix;
    }

    void Transformation::transform(const Transformation& t) {
        tMatrix = t.tMatrix * tMatrix;
    }

    Eigen::Matrix3Xf Transformation::apply(Eigen::Matrix3Xf m) const {
        return tMatrix * m;
    }

    float Transformation::determinant() const {
        return tMatrix.determinant();
    }
}