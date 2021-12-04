#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "../headers/Timer.hpp"
#include "../headers/Simulation.hpp"


Simulate::Simulate()
{

    float pos[P_NUMBER][2], speed[P_NUMBER][2];

    for(int i=0; i<P_NUMBER;i++)
    {
        pos[i][0] = rand()%S_WIDTH+10;
        pos[i][1] = rand()%HEIGHT+10;
        
//        speed[i][0] = (rand()%P_S_MAX+P_S_MIN)/100.f;
//        speed[i][1] = (rand()%P_S_MAX+P_S_MIN)/100.f;
        speed[i][0] = 0;
        speed[i][1] = 0;
    }

    for(u_int64_t i=0;i<P_NUMBER; i++)   particles.push_back(new Particle(pos[i][0], pos[i][1], speed[i][0], speed[i][1]));

    _texture.create(S_WIDTH, HEIGHT);
    this->setTexture(_texture.getTexture());

    isRunning = false;

    radius = PX_P_M*P_SIZE;
}
Simulate::~Simulate()
{
    for (u_int64_t i = 0; i < P_NUMBER; i++) delete particles[i];
}
void Simulate::renderParticles()
{
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(radius, radius);
    for(auto p:particles)
    {
        circle.setPosition(sf::Vector2f(p->posX, p->posY));
        _texture.draw(circle);
    }
}
void Simulate::render()
{
    _texture.clear();
    renderParticles();
}
void Simulate::start()
{
    isRunning = true;
    timer.start();
    while(true)
    {
        double time_taken = timer.timeGoneMicro()/1000000;
        for(auto particle:particles)
        {
            if (isRunning) particle->update(time_taken, particles);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(I_DELAY));
    }
    std::cout << "Start thread has received exit signal!" << std::endl;
}
void Simulate::handle(sf::Event& event)
{
    switch (event.key.code)
    {
        case sf::Keyboard::Space:
            toggle();
            break;
        default:
            std::cout << "No handler for class Simulate" << std::endl;
            break;
    }
}
void Simulate::toggle()
{
    isRunning = !isRunning;
}