#include <fstream>
#include <iostream>

#include "Command.h"


int main(const int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Incorrect filename";
    return EXIT_FAILURE;
  }
  const std::string fileName(argv[1]);
  std::ifstream ifs(fileName);

  if (!ifs)
  {
    std::cout << "Incorrect file" << "\n";
    return EXIT_FAILURE;
  }

  begin(ifs);
  return 0;
}
