#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include <string>
#include <memory>
#include "Light.hpp"
#include "Camera.hpp"
#include "Transformable.hpp"

namespace Geno3D
{
    /**
     * This class holds data about a 3D mesh.
     * Provides utilities to load a mesh from an obj file.
     */
    class Object : public Transformable {
    public:
        Object() : textured(false) {};
        /**
         * Load the mesh from a string in the format of an obj file.
         * @param str the string to parse
         * @see load(std::istream&)
         */
        void load(std::string str);
        /**
         * Load the mesh from a stream in the format of an obj file.
         * @param stream the stream to load
         * @see load(std::string)
         */
        void load(std::istream& stream);
        /**
         * Render the object as an SFML shape.
         * Uses lighting and camera information to generate an
         * sf::VertexArray object which can be rendered to a window.
         * @param lights a list of the lights in a scene
         * @param camera the camera to use for the render
         * @param winHeight the height of the window.
         * Used to flip the image y-axis so the render is not inverted.
         * @see Light
         * @see Camera
         */
        sf::VertexArray render(
            std::vector<std::unique_ptr<Light>>& lights,
            const std::shared_ptr<Camera>& camera,
            int winHeight
        );
        /**
         * Load a texture into the object.
         * This marks the object as being textured
         * so isTextured will return true if this function has been called.
         * @param texture the texture to load
         * @see getTexture()
         * @see isTextured()
         */
        void loadTexture(sf::Texture texture);
        /**
         * Retrieve the current texture of the object.
         * @see loadTexture()
         * @see isTextured()
         */
        sf::Texture getTexture() { return texture; }
        /**
         * Check if a texture is loaded.
         * @see loadTexture()
         * @see getTexture()
         */
        bool isTextured() { return textured; }
        // Transformable
        void translate(float x, float y, float z) override;
        void scale(float m) override;
        void rotate(float x, float y, float z) override;
        void transform(const Transformation& t) override;
    private:
        /// Sort the mesh faces by distance from the camera so they render in the correct order
        void sortFaces(const Eigen::Matrix3Xf& projected);
        /// Calculate vertex normals based on the mesh faces
        void calcNormals();
        /// The texture to render with, if any
        sf::Texture texture;
        /// Has the object been textured
        bool textured;
        /// The vertices of the object as points in 3D space
        Eigen::Matrix3Xf verts;
        /// A list of normalised UV points to map the texture to the mesh
        std::vector<sf::Vector2f> uvMap;
        /// A list of scaled points to map this object's texture to the mesh
        std::vector<sf::Vector2f> uvTexMap;
        /// A list of faces made up of three vertices to use
        std::vector<Eigen::Vector3i> faces;
        /// The object's vertex normals
        Eigen::Matrix3Xf normals;
        /// A list of which UVs to use for each face
        std::vector<Eigen::Vector3i> texCoords;
    };
}