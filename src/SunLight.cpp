#include "SunLight.h"
#include "Transformation.h"

namespace Geno3D
{
    SunLight::SunLight(Eigen::Vector3f direction) : direction(direction)
    {
        this->direction.normalize();
    }

    Eigen::VectorXf SunLight::vertexLighting(const Eigen::Matrix3Xf& normals)
    {
        Eigen::VectorXf unbounded = normals.transpose() * direction;
        return unbounded.cwiseMax(0);
    }

    void SunLight::translate(float x, float y, float z) {
        Eigen::Vector3f t(x, y, z);
        direction += t;
        direction.normalize();
    }

    void SunLight::rotate(float x, float y, float z) {
        Eigen::Matrix3f r;
        r = Eigen::AngleAxisf(x, Eigen::Vector3f::UnitX())
          * Eigen::AngleAxisf(y, Eigen::Vector3f::UnitY())
          * Eigen::AngleAxisf(z, Eigen::Vector3f::UnitZ());
        direction = r * direction;
    }

    void SunLight::transform(const Transformation& t) {
        direction = t.apply(direction);
        direction.normalize();
    }
}