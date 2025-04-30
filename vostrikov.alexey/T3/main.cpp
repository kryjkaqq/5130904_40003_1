#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include "structs.h"
#include <iomanip>


int main(int argc, char* argv[])
{
  try
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

    figures.clear();
    return 0;
  }
  catch (std::runtime_error &e)
  {
    std::cout << e.what();
    return 1;
  }
  catch (...)
  {
    return 1;
  }
}
