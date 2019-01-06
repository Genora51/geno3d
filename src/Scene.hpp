#pragma once

#include <SFML/Graphics.hpp>

namespace Geno3D
{
    /**
     * The abstract scene class, defining update and draw behaviour.
     * This class uses SFML bindings to draw to the render window.
     */
    class Scene {
    public:
        // TODO: objects, lights, camera, etc
        /**
         * Update at a "fixed-time" interval.
         * This allows an update which is independent of framerate.
         * @param dt the time between consecutive calls of this function
         * @see draw()
         * @see Engine::run()
         */
        virtual void update(float dt) = 0;
        /**
         * Update once per frame.
         * This allows efficiently rendering to the window.
         * @param in an interpolation factor
         * @see update()
         * @see Engine::run()
         */
        virtual void draw(float in) = 0;
        /**
         * Handle input events such as closing the window.
         * This function is called every frame.
         * @see update()
         * @see draw()
         * @see Engine::run()
         */
        virtual void handleInput() = 0;
        /**
         * Set up the scene with information about the render window.
         * This is called internally by the Engine class.
         * @see Engine
         */
        virtual void init(sf::RenderWindow *window, sf::Vector2i dims) = 0;
        virtual ~Scene() {};
    };
}
