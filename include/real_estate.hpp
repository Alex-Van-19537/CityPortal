#ifndef REAL_ESTATE_HPP
#define REAL_ESTATE_HPP
#include "entry.hpp"

enum class EstateType
{
    APARTMENT,
    HOUSE,
    STUDIO,
    MAISONETTE
};

string ETypeToStr(const EstateType &);
EstateType strToEType(const string &);

class RealEstate : public Entry
{
public:
    RealEstate() = default;
    RealEstate(int, EstateType, string, int, int, bool = true);

    EstateType getEstateType() const;
    string getAddress() const;
    int getSize() const;
    int getPrice() const;
    bool getForSale() const;

    void setEstateType(const EstateType &);
    void setAddress(const string &);
    void setSize(int);
    void setPrice(int);
    void setForSale(bool);

    bool loadFromCSV(ifstream &) override;
    void writeToCSV(ofstream &) const override;

    ostream &ins(ostream &) const override;
    istream &ext(istream &) override;

private:
    EstateType estateType = EstateType::APARTMENT;
    string address = "";
    int size = 0;
    int price = 0;
    bool forSale = true;
};

#endif