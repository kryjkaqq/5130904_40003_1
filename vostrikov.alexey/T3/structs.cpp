#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <regex>
#include <iterator>
#include <numeric>
#include "structs.h"

std::ostream& operator<<(std::ostream& out, const Point& p)
{
  out << "(" << p.x_ << ";" << p.y_ << ")";
  return out;
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly)
{
  for (const auto& point : poly.points_) {
    out << point << " ";
  }
  return out;
}

void figures_input(const std::string &filename, std::vector<Polygon> &polygons)
{

  if (filename.empty())
  {
    throw std::runtime_error("Filename is empty");
  }

  std::ifstream inputFile(filename);
  if (!inputFile) {
    throw std::runtime_error("Cannot open file");
  }

  std::string line;

  const std::regex CORRECT_lINE(R"((\d+)((?: \(-?\d+;-?\d+\))+)?)");
  const std::regex POINT_PATTERN(R"(\((-?\d+);(-?\d+)\))");

  std::smatch match, mch;


  while (std::getline(inputFile, line))
  {

    if (std::regex_search(line,match,CORRECT_lINE))
    {
      long unsigned int vert = std::stoul(match.str(1));
      std::vector<Point> form_vertex;

      std::for_each(
          std::sregex_iterator(line.begin(), line.end(), POINT_PATTERN),
          std::sregex_iterator(),
          [&form_vertex](const std::smatch& match) {
              form_vertex.push_back(Point(std::stoi(match.str(1)), std::stoi(match.str(2))));
          }
      );
      if (form_vertex.size() == vert and vert > 2)
      {
        polygons.push_back(Polygon(form_vertex));
        form_vertex.clear();
      }
      else
      {
        form_vertex.clear();
        continue;
      }
    }
    else
    {
      continue;
    }
  }

  match = std::smatch();
}

double area(const Polygon &poly)
{
  double area = std::accumulate(poly.points_.begin(), poly.points_.end(), 0.0,
  [&poly](double acc, const Point& point) {
    size_t idx = &point - &poly.points_[0];
    const Point& next = poly.points_[(idx + 1) % poly.points_.size()];
    return acc + (point.x_ * next.y_ - next.x_ * point.y_);
  });
  return std::abs(area)/2.0;
}

bool is_even(const Polygon& poly) {
  return poly.points_.size() % 2 == 0;
}

void command_process_recursive(std::vector<Polygon> &figures)
{
  std::string line;
  if (!std::getline(std::cin, line)) {
    return;
  }

  if (!line.empty()) {
    command_process(line, figures);
  }

  command_process_recursive(figures);
}

void command_process(std::string line, std::vector<Polygon> &figures)
{
  const std::regex AREA(R"(^AREA (.+))");
  const std::regex MAX(R"(^MAX (.+))");
  const std::regex MIN(R"(^MIN (.+))");
  const std::regex COUNT(R"(^COUNT (.+))");
  const std::regex ECHO(R"(^ECHO (\d+)((?: \(-?\d*;-?\d*\))+)?)");
  const std::regex INFRAME(R"(^INFRAME (\d+)((?: \(-?\d*;-?\d*\))+)?)");

  std::smatch match;

  if (std::regex_search(line, match, AREA))
  {
    if (match.str(1) == "ODD")
    {

      auto odd_poly = std::bind(
        [](double acc,const Polygon& poly) {
            return !is_even(poly) ? (acc + area(poly)) : acc;
        },
        std::placeholders::_1, std::placeholders::_2
      );

      double ODDarea = std::accumulate(figures.begin(), figures.end(), 0.0,odd_poly);

      std::cout << ODDarea << "\n";
    }
    else if (match.str(1) == "EVEN")
    {

      auto even_area = std::bind(
        [](double acc, const Polygon &poly)
        {
          return is_even(poly)? (acc + area(poly)) : acc;
        },
        std::placeholders::_1, std::placeholders::_2
      );

      double EVENarea = std::accumulate(figures.begin(), figures.end(), 0.0,even_area);

      std::cout <<EVENarea << "\n";

    }
    else if (match.str(1) == "MEAN")
    {

      auto smAr = std::bind(
        [](double acc, const Polygon &poly)
        {
          return acc + area(poly);
        },
        std::placeholders::_1, std::placeholders::_2
      );

      double smArea = std::accumulate(figures.begin(), figures.end(), 0.0, smAr)/figures.size();

      std::cout << smArea << "\n";
    }
    else if (isdigit(match.str(1)[0]))
    {

      if (std::stoi(match.str(1)) < 3)
      {
        std::cout << "<INVALID COMMAND>\n";
      }

      else
      {

        double Numarea = std::accumulate(figures.begin(), figures.end(), 0.0,
        [&match](double acc, const Polygon &poly)
        {
          if (std::to_string(poly.points_.size()) == (match.str(1)))
          {
            return acc + area(poly);
          }
          else
          {
            return acc;
          }
        });

        std::cout << Numarea << "\n";
      }

    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  else if (std::regex_search(line,match,MAX))
  {
    if (match.str(1) == "AREA")
    {

      auto comp = std::bind(
          std::less<>(),
          std::bind(area, std::placeholders::_1),
          std::bind(area, std::placeholders::_2)
      );

      auto mx = std::max_element(figures.begin(), figures.end(), comp);

      if (mx != figures.end())
      {
        std::cout << area(*mx) << "\n";
      }
      else
      {
        throw std::invalid_argument("Cannot find max element");
      }
    }
    else if (match.str(1) == "VERTEXES")
    {

      auto mx = std::max_element(figures.begin(), figures.end(),
        [](const Polygon &poly1, const Polygon &poly2)
        {
          return poly1.points_.size() < poly2.points_.size();
        }
      );

      if (mx != figures.end())
      {
        std::cout << mx->points_.size() << "\n";
      }
      else
      {
        throw std::invalid_argument("Cannot find max element");
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  else if (std::regex_search(line,match,MIN))
  {
    if (match.str(1) == "AREA")
    {

      auto comp = std::bind(
          std::less<>(),
          std::bind(area, std::placeholders::_1),
          std::bind(area, std::placeholders::_2)
      );

      auto mn = std::min_element(figures.begin(), figures.end(), comp);

      if (mn != figures.end())
      {
        std::cout << area(*mn) << "\n";
      }
      else
      {
        throw std::invalid_argument("Cannot find min element");
      }
    }
    else if (match.str(1) == "VERTEXES")
    {

      auto mn = std::min_element(figures.begin(), figures.end(),
                [](const Polygon &poly1, const Polygon &poly2)
                {
                  return poly1.points_.size() < poly2.points_.size();
                }
              );

      if (mn != figures.end())
      {
        std::cout << mn->points_.size() << "\n";
      }
      else
      {
        throw std::invalid_argument("Cannot find min element");
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  else if (std::regex_match(line, match, COUNT))
  {
    if (match.str(1) == "ODD")
    {

      auto is_odd = std::bind(
        [](const Polygon &poly)
        {
          return poly.points_.size() % 2 != 0;
        },
        std::placeholders::_1
        );

      size_t count = std::count_if(figures.begin(), figures.end(),is_odd);
      std::cout << count << "\n";
    }
    else if (match.str(1) == "EVEN")
    {

      auto is_even = std::bind(
        [](const Polygon &poly)
        {
          return poly.points_.size() % 2 == 0;
        },
        std::placeholders::_1
        );

      size_t count = std::count_if(figures.begin(), figures.end(),is_even);
      std::cout << count << "\n";

    }
    else if (isdigit(match.str(1)[0]))
    {
      if (std::stoi(match.str(1)) < 3)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {

        size_t size = std::stoi(match.str(1));
        auto valid_vertex = std::bind(
        [&size](const Polygon &poly)
        {
          return poly.points_.size() == size;
        },
        std::placeholders::_1
        );

        size_t count = std::count_if(figures.begin(), figures.end(),valid_vertex);
        std::cout << count << "\n";

      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  else if (std::regex_match(line, match, ECHO))
  {

    const std::regex POINT_PATTERN(R"(\((-?\d+);(-?\d+)\))");

    long unsigned int vert = std::stoul(match.str(1));
    std::vector<Point> form_vertex;
    std::transform(
      std::sregex_iterator(line.begin(), line.end(), POINT_PATTERN),
      std::sregex_iterator(),
      std::back_inserter(form_vertex),
      [](const std::smatch& match)
      {
        return Point(std::stoi(match[1]), std::stoi(match[2]));
      }
      );

    if (form_vertex.size() == vert and vert > 2)
    {

      std::vector<Polygon> duplicated = std::accumulate(
      figures.begin(), figures.end(),
      std::vector<Polygon>{},
      [&form_vertex](std::vector<Polygon> acc, const Polygon& poly)
      {
        acc.push_back(poly);
        if (poly.points_ == form_vertex)
          {
            acc.push_back(poly);
          }
        return acc;
      }
      );
      std::cout  << duplicated.size() - figures.size() << "\n";
      figures = std::move(duplicated);

    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  else if (std::regex_match(line, match, INFRAME))
  {

    const std::regex POINT_PATTERN(R"(\((-?\d+);(-?\d+)\))");

    long unsigned int vert = std::stoul(match.str(1));
    std::vector<Point> form_vertex;
    std::transform(
      std::sregex_iterator(line.begin(), line.end(), POINT_PATTERN),
      std::sregex_iterator(),
      std::back_inserter(form_vertex),
      [](const std::smatch& match)
      {
        return Point(std::stoi(match[1]), std::stoi(match[2]));
      }
      );

    if (form_vertex.size() == vert and vert > 2)
    {
      std::vector<Point> all_points = std::accumulate(
        figures.begin(), figures.end(),
        std::vector<Point>{},
        [](std::vector<Point> acc, const Polygon& poly) {
            std::copy(poly.points_.begin(), poly.points_.end(), std::back_inserter(acc));
            return acc;
        });

      auto comp_x = std::bind(
        [](const Point &p1, const Point &p2)
        {
          return (p1.x_ < p2.x_);
        },
        std::placeholders::_1, std::placeholders::_2
      );

      auto comp_y = std::bind(
      [](const Point &p1, const Point &p2)
      {
        return (p1.y_ < p2.y_);
      },
      std::placeholders::_1, std::placeholders::_2

    );

      auto pt_max_x = std::max_element(all_points.begin(), all_points.end(), comp_x);
      auto pt_min_x = std::min_element(all_points.begin(), all_points.end(), comp_x);

      auto pt_max_y = std::max_element(all_points.begin(), all_points.end(), comp_y);
      auto pt_min_y = std::min_element(all_points.begin(), all_points.end(), comp_y);

      std::vector<Point> temp;
      std::copy_if(form_vertex.begin(), form_vertex.end(), std::back_inserter(temp),
        [pt_max_x, pt_max_y, pt_min_x, pt_min_y](const Point &p)
        {
          return p.x_ >= pt_min_x->x_ and p.x_ <= pt_max_x->x_ and p.y_ >= pt_min_y->y_ and p.y_ <= pt_max_y->y_;
        });

      if (temp.size() == form_vertex.size())
      {
        std::cout << "<TRUE>\n";
      }
      else
      {
        std::cout << "<FALSE>\n";
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  match = std::smatch();
}
