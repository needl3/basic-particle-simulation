#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"
class Particle{
    public:
        float posX;
        float posY;
        float mass;
        float size;

        float speedX;
        float speedY;
        float accelerationX, accelerationY;
        float gravity_constant;
        
        Particle(float, float, float, float);
        void collide(Particle&);
        void update(float, std::vector<Particle*>&);
        void checkCollision(std::vector<Particle*>&);
};