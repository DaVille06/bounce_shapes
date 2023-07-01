/*
Author:     Nick Roberts
Date:       6/30/23
Purpose:    Load in shapes and settings from a config file.
            Display them on the screen.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char *[])
{
    std::vector<sf::CircleShape> circles;
    std::vector<sf::RectangleShape> rectangles;
    int windowWidth = 0, windowHeight = 0;
    std::string fileName = "shapeconfig.txt";

    std::ifstream fin(fileName);
    // config code tells us what the line is
    // ex. rectangle, window, font, etc.
    std::string configCode;
    while (fin >> configCode)
    {
        if (configCode == "Window")
        {
            // read in the next 2 tokens into width and height
            fin >> windowWidth;
            fin >> windowHeight;
            std::cout << "Window width " << windowWidth << " and height " << windowHeight << " loaded...\n";
        }
        else if (configCode == "Font")
        {
            // TODO: get font values
        }
        else if (configCode == "Circle")
        {
            // TODO: get circle values
        }
        else if (configCode == "Rectangle")
        {
            // TODO: get rectangle values
        }
        // commenting this out until we get through all the FIN's
        // else
        // {
        //     perror("Something has been entered into the config which should not be here. Please check the file and try again...\n");
        //     return -1;
        // }
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bounce Shapes");
    window.setFramerateLimit(60);
    sf::CircleShape circle(25.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(50.0f, 50.0f);
    sf::Vector2f velocity(1.0f, 2.0f);

    int r = 0, g = 0, b = 0;

    // loop after read in values
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::C)
                {
                    std::cout << "Change color initiated\n";
                    circle.setFillColor(sf::Color::Magenta);
                }
                break;
            default:
                break;
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