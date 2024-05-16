#pragma once
#include <SFML/Graphics.hpp>
#include "shape.hpp"

void drawPoint(Point, sf::RenderWindow*);
void drawLine(Line, sf::RenderWindow*);
void drawShape(Shape, sf::RenderWindow*);

int keyCodeToInt(sf::Keyboard::Key keyCode);
