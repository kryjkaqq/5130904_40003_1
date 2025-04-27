#ifndef POLYGON_H
#define POLYGON_H
#include <iostream>
#include <istream>
#include <numeric>
#include <vector>
#include <regex>
#include <string>


struct Point
{
  int x, y;

  friend std::istream& operator>>(std::istream& in, Point& point);

  friend bool operator==(const Point& lhs, const Point& rhs);
};

struct Polygon
{
  std::vector<Point> points;
  bool isCorrect = true;

  double getArea() const;

  friend bool operator==(const Polygon& lhs, const Polygon& rhs);

  int getMinX() const;

  int getMinY() const;

  int getMaxX() const;

  int getMaxY() const;
};

bool readPoints(std::istream& in, std::vector<Point>& points, unsigned int count);

std::istream& operator>>(std::istream& in, Polygon& polygon);

#endif //POLYGON_H
