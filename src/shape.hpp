#pragma once
#include <vector>
using namespace std;

const int HEIGHT = 1000;
const int WIDTH  = 1700;

struct Point;
struct Line;
struct Shape;

struct Point {
    double x, y;
    double drawX, drawY;

    Point();
    Point(double xPos, double yPos);
    Point rotatePoint(Point origin, double angle);

    friend bool operator==(const Point& p1, const Point& p2);
};

struct Line {
    Point point1, point2;
    float length;
    double rise, run;
    double slope;
    double yIntercept;

    Line(Point p1, Point p2);

    void update();
    void calcLength();
    void calcSlope();
    void calcYIntercept();
    double calcYIntercept(Point point, double slope);
    bool isPointOnLine(Point point);
    Point getIntersectionPoint(double newRise, double newRun, double newYIntercept);
    Line getPerpendicular(Point point);

    Shape toShape();

    friend bool operator==(const Line& l1, const Line& l2);
};

class Shape {
    public:
        int numSides;
        vector<Line> lines;
        vector<Point> points;

        Shape(vector<Point> newPoints);
        Shape reflect(Line reflectionLine);
        Shape translate(double x, double y);
        Shape rotate(Point origin, double angle);

        friend bool operator==(const Shape&, const Shape&);
};
