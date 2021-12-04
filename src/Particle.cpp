#include "../headers/Particle.hpp"
#include <iostream>
Particle::Particle(float X, float Y, float sX, float sY)
{
    mass = P_MASS;

    speedX = sX*PX_P_M;
    speedY = sY*PX_P_M;

    posX = X;
    posY = Y;

    accelerationY = U_GRAVITY*PX_P_M;
    accelerationX = 0*PX_P_M;

    size = P_SIZE*PX_P_M;

    gravity_constant = G_CONST;
}
void Particle::collide(Particle& p)
{
    //Calculate new acceleration, speedX, speedY
    float mass_constant = (mass - p.mass)/(mass + p.mass);

    float tmpS1X = speedX;
    float tmpS1Y = speedY;
    float tmpS2X = p.speedX;
    float tmpS2Y = p.speedY;

    speedX = mass_constant * tmpS1X + 2 * p.mass/(mass+p.mass) * tmpS2X; 
    speedY = mass_constant * tmpS1Y + 2 * p.mass/(mass+p.mass) * tmpS2Y; 
    
    p.speedX = -mass_constant * tmpS2X + 2 * mass/(mass+p.mass) * tmpS1X; 
    p.speedY = -mass_constant * tmpS2Y + 2 * mass/(mass+p.mass) * tmpS1Y;
}
void Particle::update(float delta_seconds /* = 1 */, std::vector<Particle*>& particles)
{
    
    speedX += accelerationX*delta_seconds;
    speedY += accelerationY*delta_seconds;

    posX += (speedX+0.5f*accelerationX*delta_seconds)*delta_seconds;
    posY -= (speedY+0.5f*accelerationY*delta_seconds)*delta_seconds;

//    std::cout << "Particle: " << this << " posX: " << posX << " speedX: " << speedX << " Seconds: " << delta_seconds << std::endl;

    checkCollision(particles);
}
void Particle::checkCollision(std::vector<Particle*>& particles)
{
    //If collides with boundary perform perfectly elastic collision with heavy object at rest
    if(posX+size>=S_WIDTH || posX-size<0)
    {
//        std::cout << "Collision BoundaryX: " << posX << std::endl;
        speedX *= -1;
    }
    if(posY+size>=HEIGHT || posY-size<0)
    {
//        std::cout << "Collision BoundaryY: " << posY-size/2 << std::endl;
        speedY *= -1;
    }

    // Check if there are other particles that intersect this one;
    for(auto particle:particles)
    {
        float distance = std::sqrt(std::pow(posX-particle->posX, 2)+std::pow(posY-particle->posY, 2));
        if(distance < size*2 && this != particle)
        {
            collide(*particle);
        }
    }
}