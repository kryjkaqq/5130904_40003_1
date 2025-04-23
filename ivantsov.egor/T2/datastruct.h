#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <string>
#include <iosfwd> // Предварительное объявление std::ostream, std::istream


struct DataStruct_t
{
	double key1_;
	unsigned long long key2_;
	std::string key3_;
};

std::ostream& operator<<(std::ostream& out, const DataStruct_t& data);
std::istream& operator>>(std::istream& in, DataStruct_t& data);


bool dataStructComparator(const DataStruct_t& lhs, const DataStruct_t& rhs);
#endif 
