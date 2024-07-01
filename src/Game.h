#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "GameUtil.h"
#include "Components.h"

constexpr auto DegToRad = 3.14159265f / 180.0f;

class Game
{
private:
    // Window Objects
    sf::RenderWindow window;
    sf::Event event;
    sf::Color winColor;
    sf::Vector2i mousePos;  // future use
    const unsigned int winWidth = 1280;
    const unsigned int winHeight = 720;

    // GUI Objects
    sf::Font font;
    sf::Text text;
    bool displayText;

    // Game Objects
    bool clicked = false;   // future use
    unsigned int maxEntities = 1000;
    unsigned int numEntities = 0;
    float minSpeed = 200.f;
    float maxSpeed = 300.f;
    float visualRange = 60.0f;
    float closeRange = 20.0f;
    float alignmentFactor = 0.005f;
    float separationFactor = 0.7f;
    float cohesionFactor = 0.03f;
    float edgeFactor = 10.f;
    float edgePadding = 150.f;

    // Components
    std::vector<sf::Vector2f> centers;
    std::vector<sf::Vector2f> velocities;
    std::vector<sf::Vertex> vertices;
    const BoidModel boidModel;

    // Time Objects
    float dt;
    sf::Clock dt_clock;

    // Private Functions
    void initWindow(sf::VideoMode videoMode);
    void initText(sf::Text* textObj);
    void updateVertices();
    void moveCenters();
    void applyForce();


public:
    Game();
    ~Game();

    // Accessors
    const bool running() const;

    // Functions
    void pollEvents();
    void update();
    void render();
};

