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

  friend std::istream& operator>>(std::istream& in, Point& point)
  {
    const std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    std::string inStr;
    in >> inStr;

    const auto pointRegex = std::regex(R"(\((-?\d+);(-?\d+)\))");
    std::smatch match;

    if (!std::regex_match(inStr, match, pointRegex))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    point.x = std::stoi(match[1].str());
    point.y = std::stoi(match[2].str());

    return in;
  }
};

struct Polygon
{
  std::vector<Point> points;
  bool isCorrect = true;

  double getArea() const
  {
    if (points.size() < 3)
    {
      return 0.0;
    }
    auto first = points.begin();
    auto last = points.end();

    auto next = [first, last](auto it)
    {
      return std::next(it) == last ? first : std::next(it);
    };

    const double area = std::accumulate(
      first, last,
      0.0,
      [&](const double sum, const Point& p1)
      {
        const Point& p2 = *next(first + (&p1 - &*first));
        return sum + (p1.x * p2.y - p2.x * p1.y);
      }
      // &*first    // адрес первой точки
      // & p1       // адрес текущей точки
      // & p1 - &*first  // индекс текущей точки
      // & first + (&p1 - &*first)  // итератор на текущую точку
      // next(итератор на p1)  // получаем итератор на следующую точку
      // *next(...)  // разыменовываем итератор, получаем следующую точку
    );

    return std::abs(area) / 2.0;
  }
};

inline bool readPoints(std::istream& in, std::vector<Point>& points, const unsigned int count)
{
  if (count == 0)
  {
    return true;
  }

  Point point{};
  if (!(in >> point))
  {
    return false;
  }

  points.push_back(point);
  return readPoints(in, points, count - 1);
}

inline std::istream& operator>>(std::istream& in, Polygon& polygon)
{
  const std::istream::sentry sentry(in);
  if (!sentry)
  {
    polygon.isCorrect = false;
    return in;
  }

  polygon.points.clear();
  unsigned int pointsCount = 0;
  if (!(in >> pointsCount) || pointsCount == 0)
  {
    polygon.isCorrect = false;
    return in;
  }
  in.ignore();

  std::string line;
  std::getline(in, line);
  std::istringstream iss(line);


  if (!readPoints(iss, polygon.points, pointsCount))
  {
    polygon.isCorrect = false;
    return in;
  }
  if (iss >> std::ws && !iss.eof())
  {
    polygon.isCorrect = false;
  }
  if (polygon.points.size() != pointsCount || pointsCount < 3)
  {
    polygon.isCorrect = false;
  }

  return in;
}

#endif //POLYGON_H
