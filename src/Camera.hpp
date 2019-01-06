#pragma once

#include <eigen3/Eigen/Dense>
#include "Transformable.hpp"

namespace Geno3D
{
    /**
     * The abstract camera class. To be used within a scene.
     */
    class Camera : public Transformable {
    public:

        Camera();
        virtual ~Camera() {};

        /**
         * Project a set of points in 3D space onto the 2D camera.
         * This should project the points onto the camera's display surface,
         * using a projection algorithm e.g. Perspective or Orthographic projection.
         * @param points a 3-row matrix holding points in 3D space
         * @see PerspCamera
         * @see OrthCamera
         */
        virtual Eigen::Matrix3Xf project(const Eigen::Matrix3Xf &points) = 0;

        void translate(float x, float y, float z) override;
        /**
         * Scale the position in 3D space by a factor.
         * @param m the factor to scale by
         */
        void scale(float m) override;
        void rotate(float x, float y, float z) override;
        /**
         * Transform position and rotation of the camera by a compound transformation.
         * @param t the transformation to apply
         */
        void transform(const Transformation& t) override;
        /**
         * Set the position of the camera in 3D space.
         * @param x the position on the x-axis
         * @param y the position on the y-axis
         * @param z the position on the z-axis
         * @see getPosition()
         * @see setOrientation()
         * @see setSurface()
         */
        void setPosition(float x, float y, float z);
        /**
         * Get the current position of the camera in 3D space.
         * @see setPosition()
         * @see getOrientation()
         * @see getSurface()
         */
        Eigen::Vector3f getPosition() { return position; }
        /**
         * Set the 3D orientation of the camera.
         * @param x the orientation about the x-axis
         * @param y the orientation about the y-axis
         * @param z the orientation about the z-axis
         * @see getOrientation()
         * @see setPosition()
         * @see setSurface()
         */
        void setOrientation(float x, float y, float z);
        /**
         * Get the current 3D orientation of the camera.
         * @see setOrientation()
         * @see getPosition()
         * @see getSurface()
         */
        Eigen::Vector3f getOrientation() { return orientation; }
        /**
         * Configure the camera's display surface.
         * @param x the x-position of the surface.
         * It is recommended to set this to half the width of the rendering window.
         * @param y the y-position of the surface.
         * It is recommended to set this to half the height of the rendering window.
         * @param z the z-position of the surface.
         * This acts as a scaling factor for the rendered image.
         * It is recommended to set this to around half the height of the rendering window.
         * @see getSurface()
         * @see setPosition()
         * @see setOrientation()
         */
        void setSurface(float x, float y, float z);
        /**
         * Get the current configuration of the camera's display surface
         * @see setSurface()
         * @see getPosition()
         * @see getOrientation()
         */
        Eigen::Vector3f getSurface() { return displaySurface; }
    protected:
        /// 3D Position of the camera
        Eigen::Vector3f position;
        /// 3D Orientation of the camera
        Eigen::Vector3f orientation;
        /// Configuration of the camera's display surface
        Eigen::Vector3f displaySurface;
    };
}
