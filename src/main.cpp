#include "../headers/Simulation.hpp"
#include "../headers/Controller.hpp"
#include <iostream>
#include <thread>

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fluid Simulation");
    sf::Event event;
    window.setFramerateLimit(FPS);

    Simulate simulation;
    Controller controller;
    std::thread simulation_thread(&Simulate::start, &simulation);
    simulation_thread.detach();
    while(window.isOpen())
    {
        window.pollEvent(event);
        
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                {
                    switch(event.key.code){
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            simulation.handle(event);
                            break;
                    }
                }
                break;
            case sf::Event::MouseButtonPressed:
                controller.handle(event, simulation);
                break;
        }

        simulation.render();

        //Render Controller State
        window.clear();
        window.draw(simulation);
        window.draw(controller);
        window.display();
    }
    return 0;
}