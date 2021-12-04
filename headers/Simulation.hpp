#pragma once
#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include "config.hpp"
#include "Timer.hpp"

class Simulate: public sf::Sprite
{
    private:
        std::vector<Particle*> particles;
        sf::RenderTexture _texture;
        bool isRunning;
        Timer timer;

        float radius;
    public:
        Simulate();
        ~Simulate();
        void renderParticles();
        void render();
        void handle(sf::Event&);
        void start();
        void stop();
        void toggle();
};