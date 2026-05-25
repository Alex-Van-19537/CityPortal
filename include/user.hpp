#ifndef USER_HPP
#define USER_HPP
#include "entry.hpp"
#include "database.hpp"
#include "vehicle.hpp"
#include "real_estate.hpp"

enum class Role
{
    CITIZEN,
    ADMIN
};

string roleToStr(Role);

Role strToRole(const string &);

class User : public Entry
{
public:
    User() = default;
    User(int, const string &, const string &, const string &, const string &, int, int = 0, unsigned = 0, const vector<int> & = {}, const vector<int> & = {}, const Role & = Role::CITIZEN);

    // getter
    string getFirstname() const;
    string getLastname() const;
    string getUsername() const;
    string getPassword() const;
    unsigned getAge() const;
    unsigned getIncome() const;
    unsigned getMoney() const;
    vector<int> getRealEstates() const;
    vector<int> getVehicles() const;
    const Role &getRole() const;
    void getInfo() const;
    bool showVehicles(const Database<Vehicle> &) const;
    bool showRealEstate(const Database<RealEstate> &) const;
    

    // setter
    void setFirstname(const string &);
    void setLastname(const string &);
    void setAge(int);
    void setIncome(unsigned);
    void setMoney(unsigned);
    void setRealEstates(vector<int>);
    void setVehicles(vector<int>);

    void writeToCSV(ofstream &) const override;
    bool loadFromCSV(ifstream &) override;

    ostream &ins(ostream &) const override;
    istream &ext(istream &) override;

private:
    string firstname = "";
    string lastname = "";
    string username = "";
    string password = "";
    unsigned age = 0;
    unsigned income = 0;
    unsigned money = 0;
    vector<int> real_estate;
    vector<int> vehicles;
    Role role = Role::CITIZEN;
};

#endif