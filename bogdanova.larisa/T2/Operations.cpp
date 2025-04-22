#include "Operations.h"
#include <sstream>
#include <algorithm>
#include <iterator>

std::vector<DataStruct> readDataFromStream(std::istream& in)
{
    std::vector<DataStruct> dataVector;
    std::string line;

    while (std::getline(in, line))
    {
        std::istringstream iss(line);
        DataStruct ds;

        if (iss >> ds)
        {
            dataVector.push_back(ds);
        }
    }

    return dataVector;
}


void writeDataToStream(std::ostream& out, const std::vector<DataStruct>& data)
{
    std::copy(data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(out, "\n"));
}
