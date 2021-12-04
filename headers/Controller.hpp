#pragma once
#include <SFML/Graphics.hpp>
#include "Simulation.hpp"

class Controller: public sf::Sprite
{
    
    public:
        void handle(sf::Event&, Simulate&);
};