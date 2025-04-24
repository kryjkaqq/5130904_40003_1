#include "DataStruct.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

int main() {
    std::vector<DataStruct> v;
    std::copy(
        std::istream_iterator<DataStruct>(std::cin),
        std::istream_iterator<DataStruct>(),
        std::back_inserter(v)
    );
    std::sort(v.begin(), v.end(), compareDataStructs);
    std::copy(
        v.begin(), v.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );
    return 0;
}
