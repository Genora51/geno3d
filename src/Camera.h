#pragma once

#include <eigen3/Eigen/Dense>
#include "Transformable.h"

namespace Geno3D
{
    class Camera : public Transformable {
    public:
        Camera();
        virtual ~Camera() {};
        virtual Eigen::Matrix3Xf project(const Eigen::Matrix3Xf &points) = 0;
        void translate(float x, float y, float z) override;
        void scale(float m) override;
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
        // Getters & Setters
        void setPosition(float x, float y, float z);
        Eigen::Vector3f getPosition() { return position; }
        void setOrientation(float x, float y, float z);
        Eigen::Vector3f getOrientation() { return orientation; }
        void setSurface(float x, float y, float z);
        Eigen::Vector3f getSurface() { return displaySurface; }
    protected:        
        Eigen::Vector3f position;
        Eigen::Vector3f orientation;
        Eigen::Vector3f displaySurface;
    };
}
