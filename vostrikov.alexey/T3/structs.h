#include <iostream>
#include <vector>

#ifndef STRUCTS_H
#define STRUCTS_H
struct Point
{
  int x_, y_;
  explicit Point(int x, int y): x_(x), y_(y) {};

  Point(const Point& other) = default;

  Point& operator=(const Point& other) = default;

  Point(Point&& other) noexcept = default;

  Point& operator=(Point&& other) noexcept = default;

  ~Point() = default;

  bool operator==(const Point& other) const
  {
    return x_ == other.x_ && y_ == other.y_;
  }

  friend std::ostream& operator<<(std::ostream& out, const Point& p);
};




struct Polygon
{
  std::vector< Point > points_;
  explicit Polygon(const std::vector<Point> &points): points_(points) {};

  Polygon(const Polygon& other) = default;

  Polygon& operator=(const Polygon& other) = default;

  Polygon(Polygon&& other) noexcept = default;

  Polygon& operator=(Polygon&& other) noexcept = default;

  ~Polygon() = default;

  bool operator==(const Polygon &p1)
  {
    return (p1.points_ == this->points_);
  }

  friend std::ostream& operator<<(std::ostream& out, const Polygon& poly);

};



void figures_input(const std::string &filename, std::vector<Polygon> &polygons);

void command_process_recursive(std::vector<Polygon> &figures);

void command_process(std::string line,std::vector<Polygon> &figures);

double area(const Polygon &poly);

bool is_even(const Polygon& poly);
#endif //STRUCTS_H
