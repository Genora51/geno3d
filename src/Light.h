#pragma once

#include <eigen3/Eigen/Dense>
#include "Transformable.h"

namespace Geno3D
{
    class Light : public Transformable {
    public:
        virtual Eigen::VectorXf vertexLighting(const Eigen::Matrix3Xf& normals) = 0;
        virtual ~Light() {};
    };
}