#include "DataStruct.h"
#include <sstream>
#include <iomanip>
#include <cctype>

std::istream& operator>>(std::istream& in, DataStruct& data) {
    std::string line;
    bool parsed = false;
    while (!parsed && std::getline(in, line)) {
        // найти границы записи "(: ... :)"
        auto p1 = line.find("(:");
        auto p2 = line.rfind(":)");
        if (p1 == std::string::npos || p2 == std::string::npos || p2 <= p1+2)
            continue;
        size_t i = p1 + 2;
        long long tmp1 = 0;
        std::complex<double> tmp2;
        std::string tmp3;
        bool has1 = false, has2 = false, has3 = false;

        while (i < p2) {
            if (line[i] != ':') { ++i; continue; }
            ++i;
            size_t name_start = i;
            while (i < p2 && !std::isspace(line[i])) ++i;
            std::string name = line.substr(name_start, i - name_start);
            if (i >= p2 || line[i] != ' ') break;
            ++i;
            if (name == "key1") {
                size_t vstart = i;
                if (line[i]=='+'||line[i]=='-') ++i;
                while (i < p2 && std::isdigit(line[i])) ++i;
                size_t vend = i;
                while (i < p2 && std::isalpha(line[i])) ++i;
                std::string num = line.substr(vstart, vend - vstart);
                try {
                    tmp1 = std::stoll(num);
                    has1 = true;
                } catch(...) { break; }
            }
            else if (name == "key2") {
                if (i+3 >= p2 || line.substr(i,3) != "#c(") break;
                i += 3;
                size_t rstart = i;
                while (i < p2 && !std::isspace(line[i])) ++i;
                std::string real_s = line.substr(rstart, i - rstart);
                ++i;
                size_t istart = i;
                while (i < p2 && line[i] != ')') ++i;
                std::string imag_s = line.substr(istart, i - istart);
                if (i >= p2 || line[i] != ')') break;
                ++i;
                try {
                    double r = std::stod(real_s);
                    double im = std::stod(imag_s);
                    tmp2 = std::complex<double>(r, im);
                    has2 = true;
                } catch(...) { break; }
            }
            else if (name == "key3") {
                if (i >= p2 || line[i] != '"') break;
                ++i;
                size_t sstart = i;
                while (i < p2 && line[i] != '"') ++i;
                if (i >= p2) break;
                tmp3 = line.substr(sstart, i - sstart);
                ++i;
                has3 = true;
            }
            else {
                has1 = has2 = has3 = false;
                break;
            }
            if (i < p2 && line[i] == ':') ++i;
        }

        if (has1 && has2 && has3) {
            data.key1 = tmp1;
            data.key2 = tmp2;
            data.key3 = tmp3;
            parsed = true;
        }
    }
    if (!parsed) in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << "(:key1 " << data.key1 << "ll";
    out << ":key2 #c("
        << std::fixed << std::setprecision(1) << data.key2.real()
        << " " << data.key2.imag() << ")";
    out << ":key3 \"" << data.key3 << "\":)";
    return out;
}

bool compareDataStructs(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1)
        return a.key1 < b.key1;
    double ma = std::abs(a.key2), mb = std::abs(b.key2);
    if (ma != mb)
        return ma < mb;
    return a.key3.size() < b.key3.size();
}

