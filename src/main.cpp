/*
Author:     Nick Roberts
Date:       6/30/23
Purpose:    Load in shapes and settings from a config file.
            Display them on the screen.
*/

#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char *[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce Shapes");
    window.setFramerateLimit(60);
    sf::CircleShape circle(25.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(50.0f, 50.0f);
    sf::Vector2f velocity(1.0f, 2.0f);
    float circleMoveSpeed = 1.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if ((circle.getPosition().x + (circle.getRadius() * 2)) >= window.getSize().x || (circle.getPosition().x <= 0))
        {
            velocity.x = -velocity.x;
        }

        if ((circle.getPosition().y + (circle.getRadius() * 2)) >= window.getSize().y || (circle.getPosition().y <= 0))
        {
            velocity.y = -velocity.y;
        }

        circle.setPosition(circle.getPosition().x + velocity.x, circle.getPosition().y + velocity.y);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}