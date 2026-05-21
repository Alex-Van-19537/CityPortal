#include "vehicle.hpp"

Vehicle::Vehicle(int id, string make, string model, Fuel fuel, int price) : Entry(id), make(make), model(model), fuel(fuel), price(price) {}

string fuelToStr(const Fuel &f)
{
    if (f == Fuel::PETROL)
        return "Petrol";
    else if (f == Fuel::DIESEL)
        return "Diesel";
    else if (f == Fuel::LPG)
        return "LPG";
    else
        return "Unknown";
}
Fuel strToFuel(const string &f)
{
    if (f == "Petrol")
        return Fuel::PETROL;
    else if (f == "Diesel")
        return Fuel::DIESEL;
    else if (f == "LPG")
        return Fuel::LPG;
    else
        return Fuel::PETROL;
}

ostream &Vehicle::ins(ostream &out) const
{
    out << left << setw(6) << getId()
        << left << setw(15) << make
        << left << setw(15) << model
        << left << setw(10) << fuelToStr(fuel)
        << left << setw(7) << price << '\n'
        << string(53, '-') << '\n';
    return out;
}

istream &Vehicle::ext(istream &in)
{
    string fuelStr;
    getline(in>>ws, make);
    getline(in >> ws, model);
    in >> fuelStr >> price;
    in.ignore();
    fuel = strToFuel(fuelStr);
    return in;
}

void Vehicle::writeToCSV(ofstream &file) const
{
    if (file)
        file << getId() << ';' << make << ';' << model << ';' << fuelToStr(fuel) << ';' << price << '\n';
}
bool Vehicle::loadFromCSV(ifstream &file)
{
    if (!file)
        return false;
    string line;

    if (getline(file >> ws, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, ';');
        if(!idStr.empty()) setId(stoi(idStr));
        getline(ss, make, ';');
        getline(ss, model, ';');
        string fuelStr, priceStr;
        getline(ss, fuelStr, ';');
        if(!fuelStr.empty()) fuel = strToFuel(fuelStr);
        getline(ss, priceStr);
        if(!priceStr.empty())price = stoi(priceStr);
        return true;
    }
    return false;
}
