#include "Command.h"

auto polygonAreaComparator = [](const Polygon& a, const Polygon& b)
{
  return a.getArea() < b.getArea();
};

auto polygonVertexesComparator = [](const Polygon& a, const Polygon& b)
{
  return a.points.size() < b.points.size();
};

double getTotalArea(const std::vector<Polygon>& polygons, const std::string& parity)
{
  if (parity == "EVEN")
  {
    return std::accumulate(
      polygons.begin(),
      polygons.end(),
      0.0,
      [](const double sum, const Polygon& polygon)
      {
        return sum + (polygon.points.size() % 2 == 0 ? polygon.getArea() : 0.0);
      }
    );
  }
  if (parity == "ODD")
  {
    return std::accumulate(
      polygons.begin(),
      polygons.end(),
      0.0,
      [](const double sum, const Polygon& polygon)
      {
        return sum + (polygon.points.size() % 2 != 0 ? polygon.getArea() : 0.0);
      }
    );
  }

  return -1;
}

double getTotalAreaMean(const std::vector<Polygon>& polygons)
{
  return std::accumulate(
    polygons.begin(),
    polygons.end(),
    0.0,
    [](const double sum, const Polygon& polygon) { return sum + (polygon.getArea()); }
  ) / static_cast<double>(polygons.size());
}

double getTotalArea(const std::vector<Polygon>& polygons, const unsigned int numOfVertexes)
{
  return std::accumulate(
    polygons.begin(),
    polygons.end(),
    0.0,
    [numOfVertexes](const double sum, const Polygon& polygon)
    {
      return sum + (polygon.points.size() == numOfVertexes ? polygon.getArea() : 0.0);
    }
  ) / static_cast<double>(polygons.size());
}

double getMaxArea(const std::vector<Polygon>& polygons)
{
  const auto it = std::max_element(
    polygons.begin(), polygons.end(), polygonAreaComparator
  );

  return it != polygons.end() ? it->getArea() : -1;
}

double getMinArea(const std::vector<Polygon>& polygons)
{
  const auto it = std::min_element(
    polygons.begin(), polygons.end(), polygonAreaComparator
  );

  return it != polygons.end() ? it->getArea() : -1;
}

int getMaxVertexes(const std::vector<Polygon>& polygons)
{
  const auto it = std::max_element(
    polygons.begin(), polygons.end(), polygonVertexesComparator
  );

  return static_cast<int>(it->points.size());
}

int getMinVertexes(const std::vector<Polygon>& polygons)
{
  const auto it = std::min_element(
    polygons.begin(), polygons.end(), polygonVertexesComparator
  );

  return static_cast<int>(it->points.size());
}

int countByVertexCondition(const std::vector<Polygon>& polygons, const std::string& parity)
{
  if (parity == "EVEN")
  {
    return static_cast<int>(std::count_if(
      polygons.begin(), polygons.end(),
      [](const Polygon& polygon) { return polygon.points.size() % 2 == 0; }
    ));
  }
  if (parity == "ODD")
  {
    return static_cast<int>(std::count_if(
      polygons.begin(), polygons.end(),
      [](const Polygon& polygon) { return polygon.points.size() % 2 != 0; }
    ));
  }

  return -1;
}

int countByVertexCondition(const std::vector<Polygon>& polygons, const unsigned int numOfVertexes)
{
  return static_cast<int>(std::count_if(
    polygons.begin(), polygons.end(),
    [numOfVertexes](const Polygon& polygon) { return polygon.points.size() == numOfVertexes; }
  ));
}

bool handleCommand(const std::vector<Polygon>& polygons, const Command& command)
{
  StreamGuard streamGuard(std::cout);
  const auto areaRegex = std::regex(R"(AREA (EVEN|ODD|MEAN|\d+))");
  const auto maxRegex = std::regex(R"(MAX (AREA|VERTEXES))");
  const auto minRegex = std::regex(R"(MIN (AREA|VERTEXES))");
  const auto countRegex = std::regex(R"(COUNT (EVEN|ODD|\d+))");
  const auto echoRegex = std::regex(R"(ECHO)");
  const auto inframeRegex = std::regex(R"(INFRAME)");

  if (std::regex_match(command.data, areaRegex))
  {
    std::cout << std::fixed << std::setprecision(1);
    if (command.data == "AREA EVEN")
    {
      std::cout << getTotalArea(polygons, "EVEN") << "\n";
    }
    else if (command.data == "AREA ODD")
    {
      std::cout << getTotalArea(polygons, "ODD") << "\n";
    }
    else if (command.data == "AREA MEAN")
    {
      if (polygons.empty())
      {
        std::cout << INVALID_COMMAND;
        return false;
      }
      std::cout << getTotalAreaMean(polygons) << "\n";
    }
    else
    {
      const unsigned int numOfVertexes = std::stoi(command.data.substr(5));
      std::cout << getTotalArea(polygons, numOfVertexes) << "\n";
    }
  }
  else if (std::regex_match(command.data, maxRegex))
  {
    if (polygons.empty())
    {
      std::cout << INVALID_COMMAND;
      return false;
    }
    if (command.data == "MAX AREA")
    {
      std::cout << std::fixed << std::setprecision(1);
      std::cout << getMaxArea(polygons) << "\n";
    }
    else if (command.data == "MAX VERTEXES")
    {
      std::cout << getMaxVertexes(polygons) << "\n";
    }
  }
  else if (std::regex_match(command.data, minRegex))
  {
    if (polygons.empty())
    {
      std::cout << INVALID_COMMAND;
      return false;
    }
    if (command.data == "MIN AREA")
    {
      std::cout << std::fixed << std::setprecision(1);
      std::cout << getMinArea(polygons) << "\n";
    }
    else if (command.data == "MIN VERTEXES")
    {
      std::cout << getMinVertexes(polygons) << "\n";
    }
  }
  else if (std::regex_match(command.data, countRegex))
  {
    if (command.data == "COUNT EVEN")
    {
      std::cout << countByVertexCondition(polygons, "EVEN") << "\n";
    }
    else if (command.data == "COUNT ODD")
    {
      std::cout << countByVertexCondition(polygons, "ODD") << "\n";
    }
    else
    {
      const unsigned int numOfVertexes = std::stoi(command.data.substr(6));
      std::cout << countByVertexCondition(polygons, numOfVertexes) << "\n";
    }
  }
  else
  {
    std::cout << INVALID_COMMAND;
    return false;
  }

  return true;
}

void begin(std::ifstream& ifs)
{
  std::vector<Polygon> polygons;
  std::copy_if(std::istream_iterator<Polygon>(ifs),
               std::istream_iterator<Polygon>(),
               std::back_inserter(polygons),
               [](const Polygon& polygon) { return !polygon.points.empty(); }
  );

  std::vector<Command> commands;
  std::copy_if(std::istream_iterator<Command>(std::cin),
               std::istream_iterator<Command>(),
               std::back_inserter(commands),
               [&polygons](const Command& command) { return handleCommand(polygons, command); }
  );
}
