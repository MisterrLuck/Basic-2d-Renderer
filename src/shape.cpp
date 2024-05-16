#include "shape.hpp"
#include <math.h>
#include <vector>
#include <iostream>
#include <limits>
using namespace std;


Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(double xPos, double yPos) {
    x = xPos;
    y = yPos;
}


Point Point::rotatePoint(Point origin, double angle) {
    double angleInRads = angle * 3.14159 / 180;

    double s = sin(angleInRads);
    double c = cos(angleInRads);

    Point p = *this;

    p.x -= origin.x;
    p.y -= origin.y;

    double xNew = p.x * c - p.y * s; // 200*0.6428 = 128.56
    double yNew = p.x * s + p.y * c; // 200*0.766 = 153.2

    p.x = xNew + origin.x;
    p.y = yNew + origin.y;

    p = Point(p.x, p.y);

    return p;
}

bool operator==(const Point& p1, const Point& p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        return true;
    }
    return false;
}


Line::Line(Point p1, Point p2) {
    point1 = p1;
    point2 = p2;

    calcLength();
    calcSlope();
    calcYIntercept();
}

// Line::Line(Point p1, double rise, double run, double distance, bool forwards) {
//     point1 = p1;

//     if (!forwards) {
//         rise *= -1;
//         run *= -1;
//     }

//     double num1 = pow(rise, 2);
//     double num2 = pow(run, 2);
//     double hypotenuese = sqrt(num1+num2);

//     double mult = distance/hypotenuese;

//     point2 = Point(p1.x+(run*mult), p1.y+(rise*mult));
// }

void Line::update() {
    calcLength();
    calcSlope();
    calcYIntercept();
}

// Calculates the length of the line, and stores it in the length member
void Line::calcLength() {
    double num1 = pow((point1.x-point2.x), 2);
    double num2 = pow((point1.y-point2.y), 2);
    length = sqrt(num1+num2);
}

// Calculates the slope of the line, and stores it in the rise and run members
void Line::calcSlope() {
    rise = point1.y-point2.y;
    run = point1.x-point2.x;

    if (run < 0) {
        run *= -1;
        rise *= -1;
    }

    if (run == 0) {
        slope = numeric_limits<double>::infinity();;
    }
    else {
        slope = rise/run;
    }
}


void Line::calcYIntercept() {
    double y = point1.y;
    double x = point1.x;
    calcSlope();

    yIntercept = y-(slope*x);
    // y = 1/3x + b
    // b = y-1/3x
    // -b = -y+1/3x
    // b = (-y+1/3x)*-1
    // b = y-1/3x
}

double Line::calcYIntercept(Point point, double slope) {
    double y = point.y; // 500
    double x = point.x; // 800

    #ifdef DEBUG
    cout << "point.y in y int: " << point.y << " x: " << point.x << " y intercept  " << y-(slope*x) << " slope " << slope << "\n";
    #endif

    return y-(slope*x); // 500-(0*800)
}

bool Line::isPointOnLine(Point point) {
    double y = ((rise/run)*point.x)+yIntercept;

    if (y == point.y) {
        return true;
    }
    return false;
}

// https://www.cuemath.com/geometry/intersection-of-two-lines/
Point Line::getIntersectionPoint(double newRise, double newRun, double newYIntercept) {
//     cout << "\nRise: " << rise << " new Rise: " << newRise;
//     cout << "\nRun: " << run << " new Run: " << newRun;
//     cout << "\nY Intercept: " << yIntercept << " new Y Intercept: " << newYIntercept;

    double A1 = -rise;
    double A2 = -newRise;
    double B1 = run;
    double B2 = newRun;
    double C1 = -yIntercept * run;
    double C2 = -newYIntercept * newRun;

    #ifdef DEBUG
    cout << "\nA1: " << A1 << " A2: " << A2;
    cout << "\nB1: " << B1 << " B2: " << B2;
    cout << "\nC1: " << C1 << " C2: " << C2;
    cout << "\nYInt" << yIntercept;
    #endif

    double x = ((B1*C2)-(B2*C1))/((A1*B2)-(A2*B1));
    double y = ((C1*A2)-(C2*A1))/((A1*B2)-(A2*B1));
    #ifdef DEBUG
    cout << "\nx: " << x << " y: " << y << "\n";
    #endif

    return Point(x, y);
}

Line Line::getPerpendicular(Point point) {
    double newRise, newRun, newSlope;

    // get the negative reciprocal of the slope
    newRise = run;
    newRun = rise;

    newRise *= -1;
    if (newRun < 0) {
        newRun *= -1;
        newRise *= -1;
    }

    if (newRun == 0)
        newSlope = numeric_limits<double>::infinity();
    else 
        newSlope = newRise/newRun;

    #ifdef DEBUG
    cout << "new slope " << newSlope << " new rise " << newRise << " newRun " << newRun << "\n";
    #endif

    Point newPoint = getIntersectionPoint(newRise, newRun, calcYIntercept(point, newSlope));
    #ifdef DEBUG
    cout << "after new point 1, x: " << point.x << ", y: " << point.y << "\n";
    cout << "after new point 2, x: " << newPoint.x << ", y: " << newPoint.y << "\n";
    #endif

    Line line(point, newPoint);
    #ifdef DEBUG
    cout << "after line, slop: " << line.rise << " over " << line.run <<  "\n";
    #endif
    return line;
}

Shape Line::toShape() {
    vector<Point> points = {point1, point2};

    return Shape(points);
}

bool operator==(const Line& l1, const Line& l2) {
    if (l1.point1 == l2.point1 && l1.point2 == l2.point2) {
        return true;
    }
    if (l1.point1 == l2.point2 && l1.point2 == l2.point1) {
        return true;
    }
    return false;
}



Shape::Shape(vector<Point> newPoints) {
    points = newPoints;

    int size = newPoints.size();
    int j;

    for (int i = 0; i < size; i++) {
        j = i+1;
        if (j == size) {j = 0;}
        // cout << "success: " << i << "\n";
        lines.push_back(Line(newPoints[i], newPoints[j]));
    }
    // lines = points;
    numSides = lines.size();
}

Shape Shape::reflect(Line reflectionLine) {
    vector<Point> newPoints;

    for (Point p : points) {
        Line line = reflectionLine.getPerpendicular(p);

        line.calcSlope();
        Point newPoint(2*line.point2.x-line.point1.x, 2*line.point2.y-line.point1.y);
        newPoints.push_back(newPoint);
    }

    return Shape(newPoints);
}

Shape Shape::translate(double x, double y) {
    vector<Point> newPoints;

    for (Point p : points) {
        Point newPoint(p.x + x, p.y + y);
        newPoints.push_back(newPoint);
    }

    return Shape(newPoints);
} 

Shape Shape::rotate(Point origin, double angle) {
    vector<Point> newPoints;

    for (Point p : points) {
        Point newPoint = p.rotatePoint(origin, angle);
        newPoints.push_back(newPoint);
    }

    return Shape(newPoints);
}

bool operator==(const Shape& s1, const Shape& s2) {
    if (s1.numSides != s2.numSides) {
        return false;
    }

    return false;
}