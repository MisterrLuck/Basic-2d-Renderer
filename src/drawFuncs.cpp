#include "drawFuncs.hpp"
#include <SFML/Graphics.hpp>

int keyCodeToInt(sf::Keyboard::Key keyCode) {
    switch (keyCode) {
        case sf::Keyboard::Key::Num0:
            return 0;
            break;
        case sf::Keyboard::Key::Num1:
            return 1;
            break;
        case sf::Keyboard::Key::Num2:
            return 2;
            break;
        case sf::Keyboard::Key::Num3:
            return 3;
            break;
        case sf::Keyboard::Key::Num4:
            return 4;
            break;
        case sf::Keyboard::Key::Num5:
            return 5;
            break;
        case sf::Keyboard::Key::Num6:
            return 6;
            break;
        case sf::Keyboard::Key::Num7:
            return 7;
            break;
        case sf::Keyboard::Key::Num8:
            return 8;
            break;
        case sf::Keyboard::Key::Num9:
            return 9;
            break;
        default:
            return -1;
            break;
    }
}

void drawPoint(Point point, sf::RenderWindow* window) {
    sf::CircleShape shape(2.f);

    // shape.setOrigin(0, window->getSize().y);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(sf::Vector2f(point.x - 1.f, point.y - 1.f)); // 1.f is half the radius

    window->draw(shape);
}

void drawLine(Line line, sf::RenderWindow* window) {
    sf::Vertex line2[] =
    {
        sf::Vertex(sf::Vector2f(line.point1.x, line.point1.y)),
        sf::Vertex(sf::Vector2f(line.point2.x, line.point2.y)),
    };

    for (int i = 0; i < 2; ++i) {
        line2[i].color = sf::Color::Black;
    }

    window->draw(line2, 2, sf::Lines);
}

void drawShape(Shape shape, sf::RenderWindow* window) {
    for (auto line : shape.lines) {
        drawLine(line, window);
    }
}
