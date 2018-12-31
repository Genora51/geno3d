#include <cmath>
#include "PerspCamera.h"


namespace Geno3D
{
    Eigen::Matrix3Xf PerspCamera::project(const Eigen::Matrix3Xf &points) {
        Eigen::Matrix3f rot;
        rot = Eigen::AngleAxisf(orientation(0), Eigen::Vector3f::UnitX())
            * Eigen::AngleAxisf(orientation(1), Eigen::Vector3f::UnitY())
            * Eigen::AngleAxisf(orientation(2), Eigen::Vector3f::UnitZ());
        Eigen::Matrix3Xf camDist = rot * (points.colwise() - position);
        Eigen::MatrixXf projected = camDist.topRows(2) * displaySurface(2);
        projected.array().rowwise() /= camDist.array().row(2);
        projected.colwise() += displaySurface.head(2);
        projected.conservativeResize(3, projected.cols());
        projected.row(2) = camDist.row(2);
        return projected;
    }
}