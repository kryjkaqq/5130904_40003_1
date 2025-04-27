#ifndef COMMAND_H
#define COMMAND_H
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "Polygon.h"
#include "StreamGuard.h"

const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";

struct Command
{
  std::string data;

  friend std::istream& operator>>(std::istream& in, Command& command)
  {
    const std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    std::getline(in, command.data);

    return in;
  }
};

double getTotalArea(const std::vector<Polygon>& polygons, const std::string& parity);

double getTotalAreaMean(const std::vector<Polygon>& polygons);

double getTotalArea(const std::vector<Polygon>& polygons, unsigned int numOfVertexes);

double getMaxArea(const std::vector<Polygon>& polygons);

double getMinArea(const std::vector<Polygon>& polygons);

int getMaxVertexes(const std::vector<Polygon>& polygons);

int getMinVertexes(const std::vector<Polygon>& polygons);

int countByVertexCondition(const std::vector<Polygon>& polygons, const std::string& parity);

int countByVertexCondition(const std::vector<Polygon>& polygons, unsigned int numOfVertexes);

int echoImplementation(std::vector<Polygon>& polygons,
                       const Polygon& polygon, std::vector<Polygon>::iterator it, int count);

int echo(std::vector<Polygon>& polygons, const Polygon& polygon);

bool isInFrame(std::vector<Polygon>& polygons, const Polygon& polygon);

bool handleCommand(const std::vector<Polygon>& polygons, const Command& command);

void begin(const std::ifstream& ifs);


#endif //COMMAND_H
