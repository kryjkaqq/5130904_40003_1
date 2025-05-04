#include "Polygon.h"

std::istream& operator>>(std::istream& in, Point& point)
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

bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x
    && lhs.y == rhs.y;
}

double Polygon::getArea() const
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

bool operator==(const Polygon& lhs, const Polygon& rhs)
{
  return lhs.points == rhs.points
    && lhs.isCorrect == rhs.isCorrect;
}

int Polygon::getMinX() const
{
  return std::min_element(
    points.begin(), points.end(),
    [](const Point& a, const Point& b) { return a.x < b.x; }
  )->x;
}

int Polygon::getMinY() const
{
  return std::min_element(
    points.begin(), points.end(),
    [](const Point& a, const Point& b) { return a.y < b.y; }
  )->y;
}

int Polygon::getMaxX() const
{
  return std::max_element(
    points.begin(), points.end(),
    [](const Point& a, const Point& b) { return a.x < b.x; }
  )->x;
}

int Polygon::getMaxY() const
{
  return std::max_element(
    points.begin(), points.end(),
    [](const Point& a, const Point& b) { return a.y < b.y; }
  )->y;
}

bool readPoints(std::istream& in, std::vector<Point>& points, const unsigned int count)
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

std::istream& operator>>(std::istream& in, Polygon& polygon)
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
    return in;
  }
  if (polygon.points.size() != pointsCount || pointsCount < 3)
  {
    polygon.isCorrect = false;
    return in;
  }

  return in;
}
