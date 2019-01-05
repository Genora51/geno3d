#include "Engine.hpp"

namespace Geno3D
{
    Engine::Engine(int width, int height, std::string title) : winSize(width, height) {
        window.create(
            sf::VideoMode(width, height), title,
            sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize
        );
    }

    void Engine::run() {
        scene->init(&window, winSize);
        float newTime, frameTime, interpolation;
        float currentTime = this->clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while (window.isOpen()) {
            // TODO: Process state changes
            newTime = this->clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if (frameTime > 0.25f) {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= dt) {
                scene->handleInput();
                scene->update(dt);
                accumulator -= dt;
            }

            interpolation = accumulator / dt;
            scene->draw(interpolation);
        }
    }
}