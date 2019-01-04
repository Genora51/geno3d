#include "SunLight.h"

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
}