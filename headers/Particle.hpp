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

        bool x_collided=false, y_collided=false;
        
        Particle(float, float, float, float);
        void collide(Particle&);
        void update(float, Particle*);
        void checkCollision(Particle*, float);
        float calculateGravitation(Particle*);
};