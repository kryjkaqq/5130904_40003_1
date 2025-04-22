#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "DataStruct.h"
#include "Operations.h"


int main()
{
    auto data = readDataFromStream(std::cin);
    if (data.empty())
    {
        std::cout << "No valid data entered.\n";
        return 0;
    }

    std::sort(data.begin(), data.end(), compareDataStruct);
    writeDataToStream(std::cout, data);

    return 0;
}
