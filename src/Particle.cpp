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
void Particle::update(float delta_seconds /* = 1 */, Particle* p)
{
    
    speedX += accelerationX*delta_seconds;
    speedY += accelerationY*delta_seconds;

    posX += (speedX+0.5f*accelerationX*delta_seconds)*delta_seconds;
    posY -= (speedY+0.5f*accelerationY*delta_seconds)*delta_seconds;

    p->speedX += p->accelerationX*delta_seconds;
    p->speedY += p->accelerationY*delta_seconds;

    p->posX += (p->speedX+0.5f*p->accelerationX*delta_seconds)*delta_seconds;
    p->posY -= (p->speedY+0.5f*p->accelerationY*delta_seconds)*delta_seconds;


//    std::cout << "Particle: " << this << " posX: " << posX << " speedX: " << speedX << " Seconds: " << delta_seconds << std::endl;
	checkCollision(p,calculateGravitation(p));
}
void Particle::checkCollision(Particle* p, float distance)
{
    //If collides with boundary perform perfectly elastic collision with heavy object at rest
    //  This particle
    if(posX+size>=S_WIDTH || posX-size<0)        speedX *= -1;
    if(posY+size>=HEIGHT || posY-size<0)        speedY *= -1;

    //  Comparing particle
    if(p->posX+size>=S_WIDTH || p->posX-size<0)        p->speedX *= -1;
    if(p->posY+size>=HEIGHT || p->posY-size<0)        p->speedY *= -1;

    //  Check for particle collision
    if(distance <= 2*size)   collide(*p);

}
float Particle::calculateGravitation(Particle* particle){
	float acc=0, distance, g_x, g_y, h;

    distance = std::sqrt((posX-particle->posX)*(posX-particle->posX)+(posY-particle->posY)*(posY-particle->posY));

    g_x = posX - particle->posX;
    g_y = posY - particle->posY;

    acc = G_CONST * mass * particle->mass/(distance * distance)*PX_P_M*PX_P_M;

    h = std::sqrt(g_x*g_x+g_y*g_y);
    //					For proper direction
    accelerationX = (1*!(g_x>0)+-1*(g_x>0)) * acc * std::abs(g_x/h);
    accelerationY = (1*!(g_y<0)+-1*(g_y<0)) * acc * std::abs(g_y/h);

    particle->accelerationX = -accelerationX;
    particle->accelerationY = -accelerationY;

    return distance;
}