#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#define PI 3.1415

typedef const unsigned short cu_chort;

//  Window Properties
static cu_chort WIDTH              = sf::VideoMode().getDesktopMode().width;
static cu_chort HEIGHT             = sf::VideoMode().getDesktopMode().height;
static cu_chort FPS                = 30;
static cu_chort S_WIDTH            = WIDTH; //Width of simulation field
static cu_chort C_WIDTH            = WIDTH-S_WIDTH; //Width of controlling field

//  Particle Properties
static cu_chort P_NUMBER           = 2;     // Number of particles
static cu_chort P_MASS             = 1;     // Kilograms
static int P_DENSITY               = 1;     // Kg/meter-cubed
static cu_chort P_S_MAX            = 100;
static cu_chort P_S_MIN            = 10;
static float P_SIZE                = std::pow(3.0f/(4.0f*PI)*float(P_MASS)/P_DENSITY, 1.0f/3);    // Radius of circular particle in meters

// Universe Properties
static float U_GRAVITY             = 1;    //Meters per second squared
static cu_chort U_SIZE             = 10;    //Means this display length is scaled to 5 meters
static cu_chort I_DELAY            = 10;    //Delay of particle interaction in milliseconds
static float G_CONST               = 0.01;

// Misc Constants
static float PX_P_M                = S_WIDTH/U_SIZE;