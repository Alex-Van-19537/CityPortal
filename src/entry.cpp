#include "entry.hpp"

Entry::Entry(int id): id(id) {}

ostream& operator<<(ostream& out, const Entry& e){
    e.ins(out);
    return out;
}

istream& operator>>(istream& in, Entry& e){
    e.ext(in);
    return in;
}