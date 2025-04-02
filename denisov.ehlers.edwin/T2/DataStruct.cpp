#include "DataStruct.h"
#include <iomanip>
#include <regex>

std::istream& operator>>(std::istream& in, DataStruct& data)
{
  const std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string line;
  std::smatch match;
  const std::regex lineRegex(R"(\(:([^:]+:){3}\))");
  const std::regex key1Regex(R"(:key1\s([-+]?[1-9]\.\d+[eE][-+]\d+):)");
  const std::regex key2Regex(R"(:key2\s([-+]?\d+((ll)|(LL))):)");
  const std::regex key3Regex(R"(:key3\s"(.+)\":)");

  bool parsedOk = false;
  while (!parsedOk && std::getline(in, line))
  {
    if (!std::regex_search(line, match, lineRegex))
    {
      continue;
    }
    if (!std::regex_search(line, match, key1Regex))
    {
      continue;
    }
    data.key1 = std::stod(match[1].str());

    if (!std::regex_search(line, match, key2Regex))
    {
      continue;
    }
    data.key2 = std::stoll(match[1].str());

    if (!std::regex_search(line, match, key3Regex))
    {
      continue;
    }
    data.key3 = match[1].str();
    parsedOk = true;
  }

  if (!parsedOk)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
  const std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  {
    StreamGuard guard(out);

    out << "(:key1 " << std::scientific << std::setprecision(1) << data.key1
      << ":key2 " << data.key2 << "ll"
      << ":key3 \"" << data.key3 << "\":)";
  }

  return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b)
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
}

StreamGuard::StreamGuard(std::basic_ios<char>& s) :
  s_(s),
  precision_(s.precision()),
  fmt_(s.flags())
{
}

StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(fmt_);
}
