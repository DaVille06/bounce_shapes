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
    // TODO: move things to methods out of main function
    std::vector<sf::CircleShape> circles;
    std::vector<sf::Vector2f> circleVelocities;
    std::vector<std::string> circleNames;

    std::vector<sf::RectangleShape> rectangles;
    std::vector<sf::Vector2f> rectangleVelocities;
    std::vector<std::string> rectangleNames;

    sf::Font font;
    int fontSize;
    int rFontColor, gFontColor, bFontColor;

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
            fin >> windowWidth;
            fin >> windowHeight;
            std::cout << "Window width " << windowWidth << " and height " << windowHeight << " loaded...\n";
        }
        else if (configCode == "Font")
        {
            // TODO: get font values
            std::string fontFileName;
            fin >> fontFileName;

            if (!font.loadFromFile(fontFileName))
            {
                perror("There was a problem loading the specified font file. Please check the config and try again...\n");
                return -1;
            }
            fin >> fontSize;
            fin >> rFontColor;
            fin >> gFontColor;
            fin >> bFontColor;
            std::cout << "Font loaded...size " << fontSize << " RGB(" << rFontColor << " " << gFontColor << " " << bFontColor << ")\n\n";
        }
        else if (configCode == "Circle")
        {
            // define vars
            std::string name;
            int xPos, yPos;
            float xSpeed, ySpeed;
            int rCircleColor, gCircleColor, bCircleColor;
            int radius;

            // get vals
            fin >> name;
            std::cout << "Name " << name << "\n";
            fin >> xPos;
            std::cout << "xPos " << xPos << "\n";
            fin >> yPos;
            std::cout << "yPos " << yPos << "\n";
            fin >> xSpeed;
            std::cout << "xSpeed " << xSpeed << "\n";
            fin >> ySpeed;
            std::cout << "ySpeed " << ySpeed << "\n";
            fin >> rCircleColor;
            fin >> gCircleColor;
            fin >> bCircleColor;
            std::cout << "RGB(" << rCircleColor << " " << gCircleColor << " " << bCircleColor << ")\n";
            fin >> radius;
            std::cout << "radius " << radius << "\n\n";

            // make circles
            sf::CircleShape circle(radius);
            circle.setFillColor(sf::Color{rCircleColor, gCircleColor, bCircleColor});
            circle.setPosition(xPos, yPos);
            circles.push_back(circle);

            circleNames.push_back(name);

            sf::Vector2f velocity(xSpeed, ySpeed);
            circleVelocities.push_back(velocity);
        }
        else if (configCode == "Rectangle")
        {
            // define vars
            std::string name;
            int xPos, yPos;
            float xSpeed, ySpeed;
            int rRectangleColor, gRectangleColor, bRectangleColor;
            int width, height;

            // get vals
            fin >> name;
            std::cout << "Name " << name << "\n";
            fin >> xPos;
            fin >> yPos;
            std::cout << "xPos " << xPos << " yPos " << yPos << "\n";
            fin >> xSpeed;
            fin >> ySpeed;
            std::cout << "xSpeed " << xSpeed << " ySpeed " << ySpeed << "\n";
            fin >> rRectangleColor;
            fin >> gRectangleColor;
            fin >> bRectangleColor;
            std::cout << "RGB(" << rRectangleColor << " " << gRectangleColor << " " << bRectangleColor << ")\n";
            fin >> width;
            fin >> height;
            std::cout << "width " << width << " height " << height << "\n\n";

            // make rectangles
            sf::Vector2f recSize(width, height);
            sf::RectangleShape rectangle(recSize);
            rectangle.setFillColor(sf::Color{rRectangleColor, gRectangleColor, bRectangleColor});
            rectangle.setPosition(xPos, yPos);
            rectangles.push_back(rectangle);

            rectangleNames.push_back(name);

            sf::Vector2f velocity(xSpeed, ySpeed);
            rectangleVelocities.push_back(velocity);
        }
        else
        {
            perror("Something has been entered into the config which should not be here. Please check the file and try again...\n");
            return -1;
        }
    }

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bounce Shapes");
    window.setFramerateLimit(60);

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
            default:
                break;
            }
        }

        window.clear();

        // text
        sf::Text text("", font, fontSize);
        text.setFillColor(sf::Color{rFontColor, gFontColor, bFontColor});

        // circles
        for (size_t i = 0; i < circles.size(); i++)
        {
            if ((circles[i].getPosition().x + (circles[i].getRadius() * 2)) >= window.getSize().x || (circles[i].getPosition().x <= 0))
            {
                circleVelocities[i].x = -circleVelocities[i].x;
            }

            if ((circles[i].getPosition().y + (circles[i].getRadius() * 2)) >= window.getSize().y || (circles[i].getPosition().y <= 0))
            {
                circleVelocities[i].y = -circleVelocities[i].y;
            }

            circles[i].setPosition(circles[i].getPosition().x + circleVelocities[i].x, circles[i].getPosition().y + circleVelocities[i].y);
            window.draw(circles[i]);

            // circle text
            // to find text x position we have to adjust for the length of the string in pixels (divide that in half)
            // to find text y position we have to adjust for the height of the font in pixels (divide that in half)
            float textX = (circles[i].getPosition().x + (circles[i].getRadius() - circleNames[i].length() * 4)) + circleVelocities[i].x;
            float textY = (circles[i].getPosition().y + (circles[i].getRadius() - fontSize / 2)) + circleVelocities[i].y;
            text.setPosition(textX, textY);
            text.setString(circleNames[i]);
            window.draw(text);
        }

        // rectangles
        for (size_t i = 0; i < rectangles.size(); i++)
        {
            auto recSize = rectangles[i].getSize();
            if (rectangles[i].getPosition().x + recSize.x >= window.getSize().x || rectangles[i].getPosition().x <= 0)
            {
                rectangleVelocities[i].x = -rectangleVelocities[i].x;
            }

            if (rectangles[i].getPosition().y + recSize.y >= window.getSize().y || rectangles[i].getPosition().y <= 0)
            {
                rectangleVelocities[i].y = -rectangleVelocities[i].y;
            }

            rectangles[i].setPosition(rectangles[i].getPosition().x + rectangleVelocities[i].x, rectangles[i].getPosition().y + rectangleVelocities[i].y);
            window.draw(rectangles[i]);

            // rectangle text
            // to find text x position we have to adjust for the length of the string in pixels (multiply that by 4 for pixels)
            // to find text y position we have to adjust for the height of the font in pixels (divide that in half)
            float textX = (rectangles[i].getPosition().x + (rectangles[i].getSize().x / 2 - (rectangleNames[i].length() * 4))) + rectangleVelocities[i].x;
            float textY = (rectangles[i].getPosition().y + (rectangles[i].getSize().y / 2 - (fontSize / 2)) + rectangleVelocities[i].y);
            text.setPosition(textX, textY);
            text.setString(rectangleNames[i]);
            window.draw(text);
        }

        window.display();
    }

    return 0;
}