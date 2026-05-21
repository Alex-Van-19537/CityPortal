#include "entry.hpp"

string vectorToStr(const vector<int> &varr)
{
    if (varr.empty())
        return "";
    string str = to_string(varr[0]);
    auto n = varr.size();
    for (int i = 1; i < int(n); i++)
        str += ',' + to_string(varr[i]);
    return str;
}

Entry::Entry(int id): id(id) {}

ostream& operator<<(ostream& out, const Entry& e){
    e.ins(out);
    return out;
}

istream& operator>>(istream& in, Entry& e){
    e.ext(in);
    return in;
}