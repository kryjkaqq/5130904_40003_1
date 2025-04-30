#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include "structs.h"
#include <iomanip>


int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    return 1;
  }
  std::string filename = argv[1];
  std::vector<Polygon> figures;

  std::cout << std::fixed << std::setprecision(1);

  figures_input(filename, figures);

  command_process_recursive(figures);

  return 0;
}
