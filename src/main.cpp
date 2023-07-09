/*
Author:     Nick Roberts
Date:       07/08/23
Purpose:    Load in shapes and settings from a config file.
            Display them on the screen.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

class AssignmentShape
{
public:
    sf::CircleShape circle;
    sf::RectangleShape rectangle;
    sf::Vector2f velocity;
    std::string shapeName;
};

int main(int argc, char *[])
{
    std::vector<AssignmentShape> shapes;

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
            circle.setFillColor(sf::Color(rCircleColor, gCircleColor, bCircleColor));
            circle.setPosition(xPos, yPos);

            sf::Vector2f velocity(xSpeed, ySpeed);

            AssignmentShape aShape;
            aShape.circle = circle;
            aShape.velocity = velocity;
            aShape.shapeName = name;
            shapes.push_back(aShape);
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
            rectangle.setFillColor(sf::Color(rRectangleColor, gRectangleColor, bRectangleColor));
            rectangle.setPosition(xPos, yPos);

            sf::Vector2f velocity(xSpeed, ySpeed);

            AssignmentShape aShape;
            aShape.rectangle = rectangle;
            aShape.velocity = velocity;
            aShape.shapeName = name;
            shapes.push_back(aShape);
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
        text.setFillColor(sf::Color(rFontColor, gFontColor, bFontColor));

        // circles
        for (auto &shape : shapes)
        {
            if (shape.shapeName.rfind("C", 0) == 0)
            {
                // do circles
                if ((shape.circle.getPosition().x + (shape.circle.getRadius() * 2)) >= window.getSize().x || (shape.circle.getPosition().x <= 0))
                {
                    shape.velocity.x = -shape.velocity.x;
                }

                if ((shape.circle.getPosition().y + (shape.circle.getRadius() * 2)) >= window.getSize().y || (shape.circle.getPosition().y <= 0))
                {
                    shape.velocity.y = -shape.velocity.y;
                }

                shape.circle.setPosition(shape.circle.getPosition().x + shape.velocity.x, shape.circle.getPosition().y + shape.velocity.y);
                window.draw(shape.circle);

                // circle text
                // to find text x position we have to adjust for the length of the string in pixels (divide that in half)
                // to find text y position we have to adjust for the height of the font in pixels (divide that in half)
                float textX = (shape.circle.getPosition().x + (shape.circle.getRadius() - shape.shapeName.length() * 4)) + shape.velocity.x;
                float textY = (shape.circle.getPosition().y + (shape.circle.getRadius() - fontSize / 2)) + shape.velocity.y;
                text.setPosition(textX, textY);
                text.setString(shape.shapeName);
                window.draw(text);
            }
            else if (shape.shapeName.rfind("R", 0) == 0)
            {
                // do rectangles
                auto recSize = shape.rectangle.getSize();
                if (shape.rectangle.getPosition().x + recSize.x >= window.getSize().x || shape.rectangle.getPosition().x <= 0)
                {
                    shape.velocity.x = -shape.velocity.x;
                }

                if (shape.rectangle.getPosition().y + recSize.y >= window.getSize().y || shape.rectangle.getPosition().y <= 0)
                {
                    shape.velocity.y = -shape.velocity.y;
                }

                shape.rectangle.setPosition(shape.rectangle.getPosition().x + shape.velocity.x, shape.rectangle.getPosition().y + shape.velocity.y);
                window.draw(shape.rectangle);

                // rectangle text
                // to find text x position we have to adjust for the length of the string in pixels (multiply that by 4 for pixels)
                // to find text y position we have to adjust for the height of the font in pixels (divide that in half)
                float textX = (shape.rectangle.getPosition().x + (shape.rectangle.getSize().x / 2 - (shape.shapeName.length() * 4))) + shape.velocity.x;
                float textY = (shape.rectangle.getPosition().y + (shape.rectangle.getSize().y / 2 - (fontSize / 2)) + shape.velocity.y);
                text.setPosition(textX, textY);
                text.setString(shape.shapeName);
                window.draw(text);
            }
            else
            {
                std::cout << "This is not a valid shape!";
            }
        }

        window.display();
    }

    return 0;
}