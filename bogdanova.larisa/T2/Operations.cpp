#include "Operations.h"
#include <algorithm>
#include <iterator>

std::vector<DataStruct> readDataFromStream(std::istream& in)
{
    std::vector<DataStruct> dataVector;
    DataStruct ds;
    while (in >> ds) {
        dataVector.push_back(ds);
    }
    in.clear(std::ios_base::goodbit);
    return dataVector;
}

void writeDataToStream(std::ostream& out, const std::vector<DataStruct>& data)
{
    std::copy(data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(out, "\n"));
}
