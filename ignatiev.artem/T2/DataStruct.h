#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <complex>
#include <iostream>

struct DataStruct {
    long long key1{};
    std::complex<double> key2{};
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool compareDataStructs(const DataStruct& a, const DataStruct& b);

#endif