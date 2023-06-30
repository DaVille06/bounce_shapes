#include <SFML/Graphics.hpp>
#include <iostream>

int main(int argc, char *[])
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works!");
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);

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

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}