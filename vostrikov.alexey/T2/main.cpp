#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <regex>

bool isValidDouble(std::string str);

bool isValidChar(std::string str);

bool isValidStr(std::string str);

struct DataStruct
{
  float key1;
  char key2;
  std::string key3;

  DataStruct() = default;

  explicit DataStruct(std::string str) {
    std::regex inside(R"(\(\:(.*?)\:\))");
    std::smatch m, m1,m2,m3;
    if (std::regex_search(str, m, inside)) {
      std::vector<std::string> v;

      std::string result = m[1];

      std::regex key1pattern(R"(key1\s+([^:]+))");
      std::regex key2pattern(R"(key2\s+([^:]+))");
      std::regex key3pattern(R"(key3\s+([^:]+))");


      if (true) {
        if (std::regex_search(result, m1, key1pattern) and isValidDouble(m1[1])) {
          key1 = std::stof(m1[1]);
        }
        else {
          throw(std::invalid_argument("Invalid DBL SCI format"));
        }

        if (std::regex_search(result, m2, key2pattern) and isValidChar(m2[1])) {
          key2 = m2[1].str()[1];
        }
        else {
          throw(std::invalid_argument("Invalid CHR LIT format"));
        }

        if (std::regex_search(result, m3, key3pattern) and isValidStr(m3[1])) {
          key3 = m3[1];
        }
        else {
          throw(std::invalid_argument("Invalid string format (must be \"DATA\" only)"));
        }
      }
      else {
        throw(std::invalid_argument("Sometexthere"));
      }
    }
    else {
      throw(std::invalid_argument("Could not find patten (:...:)"));
    }
  }

  friend std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    if (!std::getline(in, line)) {
      return in;
    }

    if (line.empty()) {
      in.setstate(std::ios::failbit);
      return in;
    }

    ds = DataStruct(line);
    return in;
  }
};

void fillvector(std::vector<DataStruct> &vec);


int main()
{
  std::vector<DataStruct> v;
  fillvector(v);
  for (auto ds: v) {
    std::cout << "key1: " << ds.key1 << " key2: " << ds.key2 << " key3: " << ds.key3 << std::endl;
  }
  return 0;
}

void fillvector(std::vector<DataStruct> &vec) {
  std::copy(std::istream_iterator<DataStruct>(std::cin),
          std::istream_iterator<DataStruct>(),
          std::back_inserter(vec));
}

bool isValidDouble(std::string str) {
  std::regex dbl_pattern(R"([1-9](\.\d+)?[eE][+-]\d+)");
  std::smatch match;

  if (std::regex_search(str, match, dbl_pattern) and match[0] == str) {
    return true;
  }
  return false;

}

bool isValidChar(std::string str) {
  if (str.size() == 3 and str[0] == '\'' and str[2] == '\'') {
    return true;
  }
  return false;
}

bool isValidStr(std::string str) {
  if (str[0] == '"' and str[str.size() - 1] == '"') {
    return true;
  }
  return false;
}


