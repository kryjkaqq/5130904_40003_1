#include "DataStruct.h"
#include <sstream>
#include <cctype>

namespace {
    bool parseKey1(std::istream& in, DataStruct& data)
    {
        char quote;

        if (!(in >> quote) || quote != '\'')
        {
            return false;
        }

        if (!(in >> data.key1))
        {
            return false;
        }

        if (!(in >> quote) || quote != '\'')
        {
            return false;
        }

        return true;
    }

    const int ASCII_ZER0 = 48;
    const int ASCII_NINE = 57;

    bool parseKey2(std::istream& in, DataStruct& data)
    {
        char c;
        std::string token;

        if (!(in >> c) || c != '(')
        {
            return false;
        }

        if (!(in >> token) || token != ":N")
        {
            return false;
        }

        if (!(in >> data.key2.first))
        {
            return false;
        }

        if (!(in >> token) || token != ":D")
        {
            return false;
        }

        token = "";
        c = ' ';
        in >> c;

        while (c != ':')
        {
            if (static_cast<int>(c) < ASCII_ZER0 || static_cast<int>(c) > ASCII_NINE)
            {
                return false;
            }
            token += c;
            in >> c;
        }
        if (std::stoi(token))
        {
            data.key2.second = std::stoi(token);
        }
        else
        {
            return false;
        }

        if (!(in >> c) || c != ')')
        {
            return false;
        }

        return true;
    }


    bool parseKey3(std::istream& in, DataStruct& data)
    {
        char quote;

        if (!(in >> quote) || quote != '"')
        {
            return false;
        }

        std::getline(in, data.key3, '"');

        if (in.peek() == '\n')
        {
            in.get();
        }
        return true;
    }

}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    DataStruct temp;
    char c;
    std::string key;

    if (!(in >> c) || c != '(')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    while (true) {
        in >> std::ws;

        if (hasKey1 && hasKey2 && hasKey3)
        {
            break;
        }

        if (!(in >> c) || c != ':')
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (!(in >> key))
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        if (key == "key1")
        {
            if (!parseKey1(in, temp))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey1 = true;
        }
        else if (key == "key2")
        {
            if (!parseKey2(in, temp))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey2 = true;
        }
        else if (key == "key3")
        {
            if (!parseKey3(in, temp))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            hasKey3 = true;
        }
        else
        {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!(in >> c) || c != ':')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!(in >> c) || c != ')')
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    data = temp;
    return in;
}


std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    out << "(:key1 '" << data.key1 << "'"
        << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)"
        << ":key3 \"" << data.key3 << "\"";
    out << ":)";
    return out;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;

    const long long left = a.key2.first * static_cast<long long>(b.key2.second);
    const long long right = b.key2.first * static_cast<long long>(a.key2.second);
    if (left != right) return left < right;

    if (a.key3.size() != b.key3.size())
    {
        return a.key3.size() < b.key3.size();
    }
    return a.key3 < b.key3;
}
