#include <iostream>
#include <iterator>
#include <vector>
#include <regex>
/*
 * 8. DBL SCI, SLL LIT
 *
 * [DBL SCI] Вещественное поле с двойной точностью (double) в научном
 * формате:
 * :keyX 5.45e-2:
 * :keyX 5.45E-2:
 * Число должно выводиться в стандартном виде, т.е. мантисса должна быть
 * меньше 10 и не меньше 1
 *
 * [SLL LIT] Знаковое максимально доступной ёмкости (long long) в формате
 * литерала:
 * :keyX 89ll:
 * :keyX -89LL:
 *
*/

// (:key1 5.45e-2:key2 89ll:key3 "Data":)
// (:key2 89ll:key1 5.45e-2:key3 "Data":)

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
    return in;

  std::smatch match;
  const std::regex lineRegex(R"(\(:([^:]+:){3}\))");
  const std::regex key1Regex(R"(:key1\s([-+]?[1-9]\.\d+[eE][-+]\d+):)");
  const std::regex key2Regex(R"(:key2\s([-+]?\d+((ll)|(LL))):)");
  const std::regex key3Regex(R"(:key3\s"(.+)\":)");

  if (!std::regex_search(line, match, lineRegex))
  {
    return in;
  }
  if (!std::regex_search(line, match, key1Regex))
  {
    return in;
  }
  std::cout << match[1].str() << '\n';
  data.key1 = std::stod(match[1].str());

  if (!std::regex_search(line, match, key2Regex))
  {
    return in;
  }
  std::cout << match[1].str() << '\n';
  data.key2 = std::stoll(match[1].str());

  if (!std::regex_search(line, match, key3Regex))
  {
    return in;
  }
  std::cout << match[1].str() << '\n';
  data.key3 = match[1].str();

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
  out << "(:key1 " << std::scientific << data.key1
    << ":key2 " << data.key2 << "ll"
    << ":key3 \"" << data.key3 << "\":)";
  return out;
}

int main()
{
  std::vector<DataStruct> data;
  DataStruct ds;
  std::cin >> ds;
  std::cout << ds;

  // std::ostream_iterator<DataStruct> out(std::cout, ", ");
  // std::copy(
  //   std::istream_iterator<DataStruct>(std::cin),
  //   std::istream_iterator<DataStruct>(),
  //   std::back_inserter(data)
  // );
  //
  // std::copy(data.begin(), data.end(), out);

  return 0;
}
