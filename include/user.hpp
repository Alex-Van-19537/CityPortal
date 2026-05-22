#ifndef USER_HPP
#define USER_HPP
#include "entry.hpp"

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
    User(int, const string &, const string &, const string &, const string &, int, int = 0, const vector<int> & = {}, const vector<int> & = {}, const Role & = Role::CITIZEN);

    // getter
    string getFirstname() const { return firstname; }
    string getLastname() const { return lastname; }
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    unsigned getAge() const { return age; }
    unsigned getIncome() const { return income; }
    const vector<int> &getRealEstates() const { return real_estate; }
    const vector<int> &getVehicles() const { return vehicles; }
    void getInfo() const;
    const Role &getRole() const { return role; }

    // setter
    void setFirstname(const string &firstname) { this->firstname = firstname; }
    void setLastname(const string &lastname) { this->lastname = lastname; }
    void setAge(int age) { this->age = age; }
    void setIncome(unsigned i) { income = i; }
    void setRealEstates(vector<int> re) { real_estate = re; }
    void setVehicles(vector<int> v) { vehicles = v; }

    void writeToCSV(ofstream &) const override;
    bool loadFromCSV(ifstream &) override;

    template <typename V, typename RE>
    void printUserCard(const V &, const RE &) const;
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

// template<typename V, typename R>
// void User::printUserCard(const V& vdb, const R& rdb) const{

template <typename V, typename RE>
void User::printUserCard(const V &vdb, const RE &redb) const
{
    cout << left << setw(6) << "[ID]"
         << left << setw(15) << "[Firstname]"
         << left << setw(15) << "[Lastname]"
         << left << setw(17) << "[Username]"
         << left << setw(20) << "[Password]"
         << left << setw(7) << "[Age]"
         << left << setw(10) << "[Income]"
         << left << setw(10) << "[Role]" << '\n'
         << string(100, '=') << "\n";

    cout << left << setw(6) << getId()
         << left << setw(15) << firstname
         << left << setw(15) << lastname
         << left << setw(17) << username
         << left << setw(20) << password
         << left << setw(7) << age
         << left << setw(10) << income
         << left << setw(10) << roleToStr(role) << '\n'
         << string(100, '.') << "\n\n"
         << "🚘 Vehicles:\n";

    if (vehicles.empty())
        cout << "\n\t∅ Does not own vehicle!\n\n";
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Make]"
             << left << setw(15) << "[Model]"
             << left << setw(10) << "[Fuel]"
             << left << setw(7) << "[Price]" << '\n'
             << string(53, '=') << '\n';
        for (const auto &v : vehicles)
        {
            auto vptr = vdb.find([&v](const auto &vobj)
                                 { return vobj.getId() == v; });
            if (vptr)
                cout << *vptr;
            else
                cerr << "\t🤷‍♂️ Missing data for Vehicle [ID]: " << v << '\n';
        }
    }

    cout << "🏠 Real Estate:\n";

    if (real_estate.empty())
        cout << "\n\t∅ Does not own real estate!\n\n";
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Type]"
             << left << setw(30) << "[Address]"
             << left << setw(10) << "[Size]"
             << left << setw(7) << "[Price]" << '\n'
             << string(68, '=') << '\n';
        for (const auto &re : real_estate)
        {
            auto reptr = redb.find([&re](const auto &reobj)
                                   { return reobj.getId() == re; });
            if (reptr)
                cout << *reptr;
            else
                cerr << "\t🤷‍♂️ Missing data for Real Estate [ID]: " << re << '\n';
        }
    }
    cout << string(100, '=') << "\n\n";
}

#endif