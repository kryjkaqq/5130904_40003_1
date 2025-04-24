#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include "datastruct.hpp"

int main() {
    std::vector<DataStruct> items;
    DataStruct ds;
    while (!std::cin.eof()) {
        std::cin >> ds;
        if (std::cin) {
            items.push_back(ds);
        } else if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    sortData(items.begin(), items.end());
    std::ostream_iterator<DataStruct> out_it(std::cout, "\n");
    std::copy(items.begin(), items.end(), out_it);
    return 0;
}
