#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>
#include <utility>

struct DataStruct {
    char key1 = '\0';
    std::pair<long long, unsigned long long> key2{ 0, 0 };
    std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);
bool compareDataStruct(const DataStruct& lhs, const DataStruct& rhs);

#endif
