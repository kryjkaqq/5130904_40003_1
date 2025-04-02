#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>
#include <regex>

struct DataStruct
{
  double key1{};
  long long key2{};
  std::string key3;
};

std::istream& operator>>(std::istream& in, DataStruct& data)
{
  std::string line;
  if (!std::getline(in, line))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::smatch match;
  const std::regex lineRegex(R"(\(:([^:]+:){3}\))");
  const std::regex key1Regex(R"(:key1\s([-+]?[1-9]\.\d+[eE][-+]\d+):)");
  const std::regex key2Regex(R"(:key2\s([-+]?\d+((ll)|(LL))):)");
  const std::regex key3Regex(R"(:key3\s"(.+)\":)");

  if (!std::regex_search(line, match, lineRegex))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  if (!std::regex_search(line, match, key1Regex))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  data.key1 = std::stod(match[1].str());

  if (!std::regex_search(line, match, key2Regex))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  data.key2 = std::stoll(match[1].str());

  if (!std::regex_search(line, match, key3Regex))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  data.key3 = match[1].str();

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
  out << "(:key1 " << std::scientific << std::setprecision(1) << data.key1
    << ":key2 " << data.key2 << "ll"
    << ":key3 \"" << data.key3 << "\":)";

  return out;
}

int main()
{
  std::vector<DataStruct> dataVector;

  const std::istream_iterator<DataStruct> begin(std::cin), end;
  std::copy(begin, end, std::back_inserter(dataVector));

  std::sort(dataVector.begin(), dataVector.end(),
            [](const DataStruct& a, const DataStruct& b)
            {
              if (a.key1 != b.key1)
              {
                return a.key1 < b.key1;
              }
              if (a.key2 != b.key2)
              {
                return a.key2 < b.key2;
              }
              return a.key3.length() < b.key3.length();
            });

  const std::ostream_iterator<DataStruct> out(std::cout, "\n");
  std::copy(dataVector.begin(), dataVector.end(), out);

  return 0;
}
