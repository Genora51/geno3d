#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Scene.hpp"

namespace Geno3D
{
    /**
     * The base "game" engine.
     * This manages the update & draw loops,
     * and creates the render window to be used in a scene.
     */
    class Engine {
    public:
        /**
         * Constructor for the Engine class.
         * @param width the width of the render window
         * @param height the height of the render window
         * @param title the window title
         * @see run()
         */
        Engine(int width, int height, std::string title);
        /**
         * The scene, defining draw & update behaviour.
         * This should be assigned before calling run()
         * to a subclass of the abstract class Scene.
         * @see Scene
         */
        std::shared_ptr<Scene> scene;
        /**
         * Display the window and run the gameloop.
         * @see scene
         */
        void run();
    private:
        /// The target frame time in seconds (target of 60fps)
        const float dt = 1.0f / 60.0f;
        /// The gameloop clock
        sf::Clock clock;
        /// The render window object
        sf::RenderWindow window;
        /// Size of the window in x & y
        sf::Vector2i winSize;
    };
}