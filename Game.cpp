#include "Game.h"

Game::Game()
{
    srand(static_cast <unsigned> (time(0)));
    initWindow(sf::VideoMode(winWidth, winHeight));
    initText(&text);
    for (unsigned i = 0; i < maxEntities; ++i)
    {
        float x = randRangef(0.f, static_cast<float>(winWidth));
        float y = randRangef(0.f, static_cast<float>(winHeight));
        float speed = randRangef(minSpeed, maxSpeed);
        float angle = randRangef(0.f, 360.f);
        float vx = speed * std::cosf(angle * DegToRad);
        float vy = speed * std::sinf(angle * DegToRad);
        centers.push_back(sf::Vector2f(x, y));
        velocities.push_back(sf::Vector2f(vx, vy));
        vertices.push_back(sf::Vertex(sf::Vector2f(boidModel.p0x, boidModel.p0y), sf::Color::Magenta));
        vertices.push_back(sf::Vertex(sf::Vector2f(boidModel.p1x, boidModel.p1y), sf::Color::Cyan));
        vertices.push_back(sf::Vertex(sf::Vector2f(boidModel.p2x, boidModel.p2y), sf::Color::Yellow));
        numEntities++;
    }
}

Game::~Game()
{
}


void Game::initWindow(sf::VideoMode videoMode)
{
    window.create(videoMode, "Boiderinos",
        sf::Style::Close | sf::Style::Titlebar);
    winColor = sf::Color::Black;
    window.setFramerateLimit(120);
}



void Game::initText(sf::Text* textObj)
{
    displayText = true;
    if (!font.loadFromFile("GohuFont14NerdFont-Regular.ttf"))
    {
        // error...
        std::cout << "ERROR loading font\n";
    }
    textObj->setFont(font);
    textObj->setFillColor(sf::Color::White);
    textObj->setCharacterSize(18);  // pixels, not points
    textObj->setStyle(sf::Text::Bold);
    textObj->setString("");
    textObj->setPosition(10.f, 10.f);
}


// TODO: add random perturbations
void Game::applyForce()
{
    for (unsigned i = 0; i < numEntities; ++i)
    {
        sf::Vector2f centerOfMass;
        int numNeighbors = 0;
        sf::Vector2f dxdy;
        for (unsigned other = 0; other < numEntities; ++other)
        {
            if (i == other)
                continue;
            float a = centers[other].x - centers[i].x;
            float b = centers[other].y - centers[i].y;
            float dist = std::sqrtf(a * a + b * b);
            if (dist <= visualRange)
            {
                if (dist <= closeRange)
                {
                    dxdy += (centers[i] - centers[other]) * separationFactor;
                }
                else
                {
                    centerOfMass += centers[other];
                    ++numNeighbors;
                    dxdy += (velocities[other] - velocities[i]) * alignmentFactor;
                }
            }
        }
        if (numNeighbors > 0)
        {
            dxdy += (centerOfMass / static_cast<float>(numNeighbors) - centers[i]) * cohesionFactor;
        }
        velocities[i] += dxdy;
        float speed = std::sqrtf(velocities[i].x * velocities[i].x + velocities[i].y * velocities[i].y);
        if (speed > maxSpeed)
        {
            velocities[i] *= maxSpeed / speed;
        }
        else if (speed < minSpeed)
        {
            velocities[i] *= minSpeed / speed;
        }
    }
}

// TODO: consider joining centers and velocities into one array: c0,v0,c1,v1...cN,vN
// Also, it may be worth storing velocity mags since they need to be checked for min/max: c0,v0,m0,c1,v1,m1...cN,vN,mN
// Vertices need to be in their own array for sfml to handle them quickly (otherwise, it's a draw call for each one...)
void Game::moveCenters()
{
    for (unsigned i = 0; i < numEntities; ++i)
    {
        // Steer away from edges
        if (centers[i].x < edgePadding)
        {
            velocities[i].x += edgeFactor;
        }
        else if (centers[i].x > static_cast<float>(winWidth) - edgePadding)
        {
            velocities[i].x -= edgeFactor;
        }

        if (centers[i].y < edgePadding)
        {
            velocities[i].y += edgeFactor;
        }
        else if (centers[i].y > static_cast<float>(winHeight) - edgePadding)
        {
            velocities[i].y -= edgeFactor;
        }

        centers[i].x += velocities[i].x * dt;
        centers[i].y += velocities[i].y * dt;
    }
}


/*
     x,y = original vector
     x',y' = rotated vector
     ax,ay = vector to rotate by
     M = magnitude of ax,ay = sqrt(ax*ax + ay*ay)
     x' = xcosT - ysinT
     y' = xsinT + ycosT
     cosT = ax/M
     sinT = ay/M
     x' = x*ax/M - y*ay/M
     y' = x*ay/M + y*ax/M
*/
void Game::updateVertices()
{
    for (unsigned i = 0; i < numEntities; ++i)
    {
        BoidModel boidRotated;
        float ax = velocities[i].x;
        float ay = velocities[i].y;
        float mag = std::sqrtf(ax * ax + ay * ay);
        if (mag == 0.0f)
            mag = 0.01f;
        boidRotated.p0x = boidModel.p0x * ax / mag - boidModel.p0y * ay / mag;
        boidRotated.p0y = boidModel.p0x * ay / mag + boidModel.p0y * ax / mag;
        boidRotated.p1x = boidModel.p1x * ax / mag - boidModel.p1y * ay / mag;
        boidRotated.p1y = boidModel.p1x * ay / mag + boidModel.p1y * ax / mag;
        boidRotated.p2x = boidModel.p2x * ax / mag - boidModel.p2y * ay / mag;
        boidRotated.p2y = boidModel.p2x * ay / mag + boidModel.p2y * ax / mag;

        vertices[i * 3].position.x = boidRotated.p0x + centers[i].x;
        vertices[i * 3].position.y = boidRotated.p0y + centers[i].y;
        vertices[i * 3 + 1].position.x = boidRotated.p1x + centers[i].x;
        vertices[i * 3 + 1].position.y = boidRotated.p1y + centers[i].y;
        vertices[i * 3 + 2].position.x = boidRotated.p2x + centers[i].x;
        vertices[i * 3 + 2].position.y = boidRotated.p2y + centers[i].y;
    }
}


const bool Game::running() const
{
    return window.isOpen();
}

void Game::pollEvents()
{
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            break;
        case sf::Event::KeyReleased:
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                clicked = true;
            }
        }

    }
}

void Game::update()
{
    dt = dt_clock.restart().asSeconds();
    static float fpsAvg = 0.f;
    static float fpsAccumulated = 0.f;
    static float tempfpsMin = 1000.f;
    static float tempfpsMax = 0.f;
    static float fpsMin = 0.f;
    static float fpsMax = 0.f;
    float fps = 1.f / dt;
    int sampleMax = 10;
    int minMaxSampleMax = 50;
    static int sample = 0;
    static int minMaxSample = 0;
    if (sample < sampleMax)
    {
        fpsAccumulated += fps;
        sample++;
    }
    else
    {
        fpsAvg = fpsAccumulated / sampleMax;
        fpsAccumulated = 0.f;
        sample = 0;
    }
    if (minMaxSample < minMaxSampleMax)
    {
        if (fps < tempfpsMin)
            tempfpsMin = fps;
        if (fps > tempfpsMax)
            tempfpsMax = fps;
        minMaxSample++;
    }
    else
    {
        fpsMin = tempfpsMin;
        fpsMax = tempfpsMax;
        minMaxSample = 0;
        tempfpsMin = 1000.f;
        tempfpsMax = 0.f;
    }
    pollEvents();

    applyForce();
    moveCenters(); 
    updateVertices();

    text.setString("FPS: " + str(static_cast<unsigned int>(fpsAvg)) + "\n"
                   "Min: " + str(static_cast<unsigned int>(fpsMin)) + "\n"
                   "Max: " + str(static_cast<unsigned int>(fpsMax)) + "\n"
                   "QTY: " + str(numEntities) + "\n"
    );
}

void Game::render()
{
    window.clear(winColor);
    
    // Draw entities
    window.draw(&vertices[0], vertices.size(), sf::Triangles);

    // Draw GUI
    if (displayText) {
        window.draw(text);
    }

    window.display();
}
