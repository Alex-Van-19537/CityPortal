#ifndef USER_HPP
#define USER_HPP
#include "entry.hpp"

enum class Role
{
    CITIZEN,
    ADMIN
};

string roleToStr(Role);

Role strToRole(const string&);

string vectorToStr(const vector<int>&);

class User : public Entry
{
public:
    User() = default;
    User(int, const string &, const string &, const string &, const string &, int, int = 0, const vector<int> & = {}, const vector<int> & = {}, const Role & = Role::CITIZEN);

    // getter
    string getFirstname() const { return firstname; }
    string getLastname() const { return lastname; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    unsigned getAge() const { return age; }
    unsigned getIncome() const { return income; }
    const vector<int>& getRealEstates() const { return real_estate; }
    const vector<int>& getVehicles() const { return vehicles; }
    void getInfo() const;
    const Role& getRole() const { return role; }

    // setter
    void setFirstname(const string &firstname) { this->firstname = firstname; }
    void setLastname(const string &lastname) { this->lastname = lastname; }
    void setAge(int age) { this->age = age; }
    void setIncome(unsigned i) { income = i; }
    void setRealEstates(vector<int> re) { real_estate = re; }
    void setVehicles(vector<int> v) { vehicles = v; }

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
    vector<int> real_estate;
    vector<int> vehicles;
    Role role = Role::CITIZEN;
};

#endif