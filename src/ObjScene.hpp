#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <eigen3/Eigen/Dense>
#include <vector>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Light.hpp"

namespace Geno3D
{
    /**
     * This class renders a 3D mesh in the viewport.
     */
    class ObjScene : public Scene {
    public:
        /**
         * Construct an object scene from a textured obj file.
         * @param filename the path to the obj file to load
         * @param posy the y-position of the camera
         * @param posz the z-position of the camera
         * @param tex the path to the texture image
         */
        ObjScene(std::string filename, float posy, float posz, std::string tex);
        /**
         * Construct an object scene from an obj file.
         * @param filename the path to the obj file to load
         * @param posy the y-position of the camera
         * @param posz the z-position of the camera
         */
        ObjScene(std::string filename, float posy, float posz);
        void init(sf::RenderWindow *window, sf::Vector2i dims) override;
        /**
         * Update once per frame.
         * This renders the mesh according to the scene's camera and lights
         * and draws the rendered image to the viewport.
         * @param in an interpolation factor
         */
        void draw(float in) override;
        void update(float dt) override;
        void handleInput() override;
        ~ObjScene() {}
    private:
        /// The viewport window
        sf::RenderWindow *window;
        /// The mesh object to render
        Object object;
        /// The camera used to render
        std::shared_ptr<Camera> camera;
        /// The lights used in the scene
        std::vector<std::unique_ptr<Light>> lights;
        /// The dimensions of the window
        sf::Vector2i windowSize;
    };
}
