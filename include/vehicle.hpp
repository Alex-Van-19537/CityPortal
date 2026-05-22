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

    string getMake() const { return make; }
    string getModel() const { return model; }
    Fuel getFuel() const { return fuel; }
    int getPrice() const { return price; }

    void setMake(string make) { this->make = make; }
    void setModel(string model) { this->model = model; }
    void setFuel(Fuel fuel) { this->fuel = fuel; }
    void setPrice(int price) { this->price = price; }

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