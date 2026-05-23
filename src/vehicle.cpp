#include "vehicle.hpp"

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

Vehicle::Vehicle(int id, string make, string model, Fuel fuel, int price) : Entry(id), make(make), model(model), fuel(fuel), price(price) {}

string Vehicle::getMake() const { return make; }
string Vehicle::getModel() const { return model; }
Fuel Vehicle::getFuel() const { return fuel; }
int Vehicle::getPrice() const { return price; }

void Vehicle::setMake(string make) { this->make = make; }
void Vehicle::setModel(string model) { this->model = model; }
void Vehicle::setFuel(Fuel fuel) { this->fuel = fuel; }
void Vehicle::setPrice(int price) { this->price = price; }

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
        if (!idStr.empty())
            setId(stoi(idStr));

        getline(ss, make, ';');

        getline(ss, model, ';');

        string fuelStr;
        getline(ss, fuelStr, ';');
        if (!fuelStr.empty())
            fuel = strToFuel(fuelStr);

        string priceStr;
        getline(ss, priceStr);
        if (!priceStr.empty())
            price = stoi(priceStr);

        return true;
    }
    return false;
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
    getline(in >> ws, make);
    getline(in >> ws, model);
    in >> fuelStr >> price;
    in.ignore();
    fuel = strToFuel(fuelStr);
    return in;
}