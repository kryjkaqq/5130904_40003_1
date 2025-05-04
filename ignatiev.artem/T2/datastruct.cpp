#include "datastruct.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>

struct Delim       { char ch; };
struct ReadLL      { long long& value; };
struct ReadComplex { std::complex<double>& value; };
struct ReadString  { std::string& value; };

static std::istream& operator>>(std::istream& in, Delim d) {
    char c;
    if (in >> c && c != d.ch) in.setstate(std::ios::failbit);
    return in;
}

static std::istream& operator>>(std::istream& in, ReadLL r) {
    if (!(in >> r.value)) return in;
    char c1, c2;
    in >> c1 >> c2;
    if (c1!='l' || c2!='l') in.setstate(std::ios::failbit);
    return in;
}

static std::istream& operator>>(std::istream& in, ReadComplex r) {
    char hash, c, paren;
    double re, im;
    if (in >> hash >> c >> paren >> re >> im >> paren) {
        r.value = std::complex<double>(re, im);
    } else {
        in.setstate(std::ios::failbit);
    }
    return in;
}

static std::istream& operator>>(std::istream& in, ReadString r) {
    char q;
    if (!(in >> q) || q!='"') {
        in.setstate(std::ios::failbit);
        return in;
    }
    return std::getline(in, r.value, '"');
}

std::istream& operator>>(std::istream& in, DataStruct& out) {
    std::string key;
    if (!(in >> Delim{'('} >> Delim{':'})) return in;
    DataStruct tmp;
    while (true) {
        if (!(in >> key)) {
            in.setstate(std::ios::failbit);
            break;
        }
        if (key == "key1") {
            if (!(in >> ReadLL{tmp.key1} >> Delim{':' })) break;
        }
        else if (key == "key2") {
            if (!(in >> ReadComplex{tmp.key2} >> Delim{':' })) break;
        }
        else if (key == "key3") {
            if (!(in >> ReadString{tmp.key3} >> Delim{':' })) break;
        }
        else if (key == ")") {
            break;
        }
        else {
            in.setstate(std::ios::failbit);
            break;
        }
    }
    if (in) out = tmp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << "(:key1 " << ds.key1 << "ll:";
    out << "key2 #c("
        << std::fixed << std::setprecision(1)
        << ds.key2.real() << ' ' << ds.key2.imag()
        << "):";
    out << "key3 \"" << ds.key3 << "\":)";
    return out;
}

void sortData(std::vector<DataStruct>::iterator b,
              std::vector<DataStruct>::iterator e)
{
    std::sort(b, e, [](const DataStruct& a, const DataStruct& b){
        if (a.key1 != b.key1)
            return a.key1 < b.key1;
        double ma = std::abs(a.key2), mb = std::abs(b.key2);
        if (std::fabs(ma - mb) > 1e-10)
            return ma < mb;
        return a.key3.size() < b.key3.size();
    });
}
