#include "../headers/Controller.hpp"
void Controller::handle(sf::Event& event, Simulate& sim)
{
     if(event.key.code == sf::Keyboard::Space)  sim.toggle();
}