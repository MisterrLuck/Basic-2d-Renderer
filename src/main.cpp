#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "shape.hpp"
#include "drawFuncs.hpp"


// #ifdef DEBUG
// #else
// #endif

enum class state {
    Normal,
    DrawShape,
    DrawLine,
    DrawPoint,
    Reflect,
    Rotate,
    Translate,
    Delete
};


int main(void) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "geometry", sf::Style::Default^sf::Style::Resize);

    window.setKeyRepeatEnabled(false); // disables hold down for multiple events

    vector<Point> points;      // points on screen
    vector<Line> lines;        // lines on screen
    vector<Shape> shapes;      // shapes on screen
    vector<Point> pointBuffer; // the points on screen that will make a new shape

    vector<int> inputInts;

    state currState = state::Normal;

    sf::Font font;
    if (!font.loadFromFile("..\\..\\src\\Roboto-Regular.ttf")) {
        cout << "Error loading font file \"Roboto-Regular.ttf\"\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::Key::S:
                            if (currState == state::Delete) {
                                if (shapes.size() != 0) shapes.pop_back();
                            }
                            else if (currState == state::Normal) currState = state::DrawShape;
                            break;
                        case sf::Keyboard::Key::L:
                            if (currState == state::Delete) {
                                if (lines.size() != 0) lines.pop_back();
                            }
                            else if (currState == state::Normal) currState = state::DrawLine;
                            break;
                        case sf::Keyboard::Key::P:
                            if (currState == state::Delete) {
                                if (points.size() != 0) points.pop_back();
                            }
                            else if (currState == state::Normal) currState = state::DrawLine;
                            break;
                        case sf::Keyboard::Key::D:
                            if (currState == state::Normal) currState = state::Delete;
                            break;
                        case sf::Keyboard::Key::C:
                            currState = state::Normal;
                            pointBuffer.clear();
                            points.clear();
                            lines.clear();
                            shapes.clear();
                            inputInts.clear();
                            break;

                        case sf::Keyboard::Key::R: // Reflect
                            if (currState == state::Normal) {
                                currState = state::Reflect;
                                #ifdef DEBUG
                                cout << "Reflect Mode\n";
                                #endif
                            }
                            break;
                        case sf::Keyboard::Key::O: // Rotate
                            if (currState == state::Normal) {
                                currState = state::Rotate;
                                #ifdef DEBUG
                                cout << "Rotate Mode\n";
                                #endif
                            }
                            break;
                        case sf::Keyboard::Key::T: // Translate
                            if (currState == state::Normal) {
                                currState = state::Translate;
                                #ifdef DEBUG
                                cout << "Translate Mode\n";
                                #endif
                            }
                            break;

                    }
                    if (event.key.code >= sf::Keyboard::Key::Num0 && event.key.code <= sf::Keyboard::Key::Num9) {
                        #ifdef DEBUG
                        cout << "numbers were pressed\n" << (int) currState << "\n";
                        #endif
                        if (currState == state::Reflect) {
                            inputInts.push_back(keyCodeToInt(event.key.code));
                            if (inputInts.size() >= 2) {
                                if (inputInts[0]+1 <= shapes.size() && inputInts[1]+1 <= lines.size()) {
                                    shapes.push_back(shapes[inputInts[0]].reflect(lines[inputInts[1]]));
                                    #ifdef DEBUG
                                    cout << "input ints were valid " << inputInts[0] << " " << inputInts[1] << "\n";
                                    #endif
                                }
                                #ifdef DEBUG
                                cout << "input ints were not valid " << inputInts[0] << " " << inputInts[1] << "\n";
                                #endif
                                currState = state::Normal;
                                inputInts.clear();
                            }
                        } else if (currState == state::Rotate) {
                            inputInts.push_back(keyCodeToInt(event.key.code));
                            if (inputInts.size() >= 5) {
                                if (inputInts[0]+1 <= shapes.size() && inputInts[1]+1 <= points.size()) {
                                    int angle = (inputInts[2]*100) + (inputInts[3]*10) + inputInts[4];
                                    shapes.push_back(shapes[inputInts[0]].rotate(points[inputInts[1]], angle));
                                    #ifdef DEBUG
                                    cout << "input ints were valid " << inputInts[2] << " " << inputInts[3] << " " << inputInts[4] << "\n";
                                    #endif
                                }
                                #ifdef DEBUG
                                cout << "input ints were not valid " << inputInts[0] << " " << inputInts[1] << "\n";
                                #endif
                                currState = state::Normal;
                                inputInts.clear();
                            }
                        } else if (currState == state::Translate) {
                            inputInts.push_back(keyCodeToInt(event.key.code));
                            if (inputInts.size() >= 9) {
                                if (inputInts[0]+1 <= shapes.size() && inputInts[1] == (bool) inputInts[1] && inputInts[5] == (bool) inputInts[5]) {
                                    int xOff = pow(-inputInts[1], -inputInts[1]) * (inputInts[2]*100) + (inputInts[3]*10) + inputInts[4];
                                    int yOff = pow(-inputInts[5], -inputInts[5]) * (inputInts[6]*100) + (inputInts[7]*10) + inputInts[8];
                                    shapes.push_back(shapes[inputInts[0]].translate(xOff, yOff));
                                    #ifdef DEBUG
                                    cout << "input ints were valid " << inputInts[0] << " " << inputInts[1] << " " << xOff << " " << yOff << "\n";
                                    #endif
                                }
                                #ifdef DEBUG
                                cout << "input ints were not valid " << inputInts[0] << " " << inputInts[1] << "\n";
                                #endif
                                currState = state::Normal;
                                inputInts.clear();
                            }
                        }
                    }

                case sf::Event::MouseButtonPressed:
                    switch(currState) {
                        case state::DrawShape:
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                Point p(event.mouseButton.x, event.mouseButton.y);
                                pointBuffer.push_back(p);

                            } else if (event.mouseButton.button == sf::Mouse::Right) {
                                if (pointBuffer.size() != 0) {
                                    shapes.push_back(Shape(pointBuffer));
                                    pointBuffer.clear();
                                }
                                currState = state::Normal;
                            }
                            break;
                        case state::DrawLine:
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                Point p(event.mouseButton.x, event.mouseButton.y);
                                pointBuffer.push_back(p);

                                if (pointBuffer.size() >= 2) {
                                    lines.push_back(Line(pointBuffer[0], pointBuffer[1]));
                                    pointBuffer.clear();
                                    currState = state::Normal;
                                }
                            }
                            break;
                        case state::DrawPoint:
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                Point p(event.mouseButton.x, event.mouseButton.y);
                                points.push_back(p);
                                currState = state::Normal;
                            }
                            break;
                    }
                    break;
            }
        }



        window.clear(sf::Color::White);

        for (Point p : points) {
            drawPoint(p, &window);
        }
        for (Point p : pointBuffer) {
            drawPoint(p, &window);
        }
        for (Line l : lines) {
            drawLine(l, &window);
        }
        for (Shape s : shapes) {
            drawShape(s, &window);
        }

        string str;
        switch (currState) {
            case state::Reflect:
                str.append("Reflect ");
                break;
            case state::Rotate:
                str.append("Rotate ");
                break;
            case state::Translate:
                str.append("Translate ");
                break;
            case state::DrawShape:
                str.append("Shape");
                break;
            case state::DrawLine:
                str.append("Line");
                break;
            case state::DrawPoint:
                str.append("Point");
                break;
        }

        for (auto i : inputInts) {
            str.push_back(i+48);
            str.push_back(' ');
        }

        text.setString(str);
        window.draw(text);

        window.display();
    }
}
