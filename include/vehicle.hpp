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
    Vehicle(int, string, string, Fuel, int, bool = true);

    string getMake() const;
    string getModel() const;
    Fuel getFuel() const;
    int getPrice() const;
    bool getForSale() const;

    void setMake(string);
    void setModel(string);
    void setFuel(Fuel);
    void setPrice(int);
    void setForSale(bool);

    void writeToCSV(ofstream &) const override;
    bool loadFromCSV(ifstream &) override;

    ostream &ins(ostream &) const override;
    istream &ext(istream &) override;

private:
    string make = "";
    string model = "";
    Fuel fuel = Fuel::PETROL;
    int price = 0;
    bool forSale = true;
};

#endif