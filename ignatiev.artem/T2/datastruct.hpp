
#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <complex>
#include <vector>
#include <iosfwd>

struct DataStruct {
    long long              key1;
    std::complex<double>   key2;
    std::string            key3;
};

std::istream& operator>>(std::istream& in, DataStruct& ds);
std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

void sortData(std::vector<DataStruct>::iterator begin,
              std::vector<DataStruct>::iterator end);

#endif
