#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "entry.hpp"

enum class Fuel
{
    PETROL,
    DIESEL,
    LPG
};

string fuelToStr(const Fuel &);
Fuel strToFuel(const string &);

class Vehicle : public Entry
{
public:
    Vehicle() = default;
    Vehicle(int, string, string, Fuel, int);

    string getMake() const;
    string getModel() const;
    Fuel getFuel() const;
    int getPrice() const;

    void setMake(string make);
    void setModel(string model);
    void setFuel(Fuel fuel);
    void setPrice(int price);

    void writeToCSV(ofstream &) const override;
    bool loadFromCSV(ifstream &) override;

    ostream &ins(ostream &) const override;
    istream &ext(istream &) override;

private:
    string make = "";
    string model = "";
    Fuel fuel = Fuel::PETROL;
    int price = 0;
};

#endif