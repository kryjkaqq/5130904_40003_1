#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include "DataStruct.h"

std::vector<DataStruct> readDataFromStream(std::istream& in);
void writeDataToStream(std::ostream& out, const std::vector<DataStruct>& data);

#endif
