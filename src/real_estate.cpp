#include "real_estate.hpp"

string ETypeToStr(const EstateType &et)
{
    if (et == EstateType::APARTMENT)
        return "Apartment";
    else if (et == EstateType::HOUSE)
        return "House";
    else if (et == EstateType::STUDIO)
        return "Studio";
    else if (et == EstateType::MAISONETTE)
        return "Maisonette";
    else
        return "Unknown";
}

EstateType strToEType(const string &et)
{
    if (et == "Apartment")
        return EstateType::APARTMENT;
    else if (et == "House")
        return EstateType::HOUSE;
    else if (et == "Studio")
        return EstateType::STUDIO;
    else if (et == "Maisonette")
        return EstateType::MAISONETTE;
    else
        return EstateType::APARTMENT;
}

RealEstate::RealEstate(int id, EstateType et, string addr, int sz, int p) : Entry(id), estateType(et), address(addr), size(sz), price(p) {}

EstateType RealEstate::getEstateType() const { return estateType; }
string RealEstate::getAddress() const { return address; }
int RealEstate::getSize() const { return size; }
int RealEstate::getPrice() const { return price; }

void RealEstate::setEstateType(const EstateType &et) { estateType = et; }
void RealEstate::setAddress(const string &addr) { address = addr; }
void RealEstate::setSize(const int sz) { size = sz; }
void RealEstate::setPrice(int p) { price = p; }

bool RealEstate::loadFromCSV(ifstream &file)
{
    if (!file)
        return false;
    string line, estateTypeStr, sizeStr, priceStr, idStr;
    if (getline(file >> ws, line))
    {
        stringstream ss(line);

        getline(ss, idStr, ';');
        if (!idStr.empty())
            setId(stoi(idStr));

        getline(ss, estateTypeStr, ';');
        if (!estateTypeStr.empty())
            estateType = strToEType(estateTypeStr);

        getline(ss, address, ';');

        getline(ss, sizeStr, ';');
        if (!sizeStr.empty())
            size = stoi(sizeStr);

        getline(ss, priceStr);
        if (!priceStr.empty())
            price = stoi(priceStr);

        return true;
    }
    return false;
}

void RealEstate::writeToCSV(ofstream &file) const
{
    if (file)
    {
        file << getId() << ETypeToStr(estateType) << ';' << address << ';' << size << ';' << price << '\n';
    }
}

ostream &RealEstate::ins(ostream &out) const
{
    out << left << setw(6) << getId()
        << left << setw(15) << ETypeToStr(estateType)
        << left << setw(50) << address
        << left << setw(10) << size
        << left << setw(7) << price << '\n'
        << string(88, '-') << '\n';
    return out;
}

istream &RealEstate::ext(istream &in)
{
    string estateTypeStr;
    getline(in >> ws, estateTypeStr);
    if (!estateTypeStr.empty())
        estateType = strToEType(estateTypeStr);
    getline(in >> ws, address);
    in >> size;
    in >> price;
    in.ignore();
    return in;
}