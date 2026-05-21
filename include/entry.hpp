#ifndef ENTRY_HPP
#define ENTRY_HPP
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
using std::cout;
using std::cin;
using std::cerr;
using std::to_string;
using std::ifstream;
using std::istream;
using std::left;
using std::ofstream;
using std::ostream;
using std::setw;
using std::stoi;
using std::string;
using std::stringstream;
using std::vector;
using std::ws;

string vectorToStr(const vector<int> &varr);
class Entry
{
public:
    Entry() = default;
    Entry(int);
    virtual ~Entry() = default;
    // getter
    int getId() const { return id; }

    // setter
    void setId(int id) { this->id = id; }

    virtual void writeToCSV(ofstream &) const = 0;
    virtual bool loadFromCSV(ifstream &) = 0;

    virtual ostream &ins(ostream &) const = 0;
    virtual istream &ext(istream &) = 0;

private:
    int id = 0;
};

ostream &operator<<(ostream &, const Entry &);
istream &operator>>(istream &, Entry &);

#endif