#include "user.hpp"

string User::getFirstname() const { return firstname; }
string User::getLastname() const { return lastname; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
int User::getAge() const { return age; }
int User::getIncome() const { return income; }
int User::getMoney() const { return money; }
vector<int> User::getRealEstates() const { return real_estate; }
vector<int> User::getVehicles() const { return vehicles; }
const Role &User::getRole() const { return role; }

void User::setFirstname(const string &firstname) { this->firstname = firstname; }
void User::setLastname(const string &lastname) { this->lastname = lastname; }
void User::setAge(int age) { this->age = age; }
void User::setIncome(int i) { income = i; }
void User::setMoney(int m) { money = m; }
void User::setRealEstates(vector<int> re) { real_estate = re; }
void User::setVehicles(vector<int> v) { vehicles = v; }
void User::setRole(const Role &r) { role = r; }

string roleToStr(Role role)
{
    switch (role)
    {
    case Role::CITIZEN:
        return "Citizen";
    case Role::ADMIN:
        return "Admin";
    default:
        return "Unknown";
    }
}

Role strToRole(const string &str)
{
    if (str == "Admin")
        return Role::ADMIN;
    return Role::CITIZEN;
}

User::User(int id,
           const string &fname,
           const string &lname,
           const string &username,
           const string &password,
           int age,
           int income,
           int money,
           const vector<int> &re,
           const vector<int> &v,
           const Role &role) : Entry(id),
                               firstname(fname),
                               lastname(lname),
                               username(username),
                               password(password),
                               age(age),
                               income(income),
                               money(money),
                               real_estate(re),
                               vehicles(v),
                               role(role) {}

void User::writeToCSV(ofstream &out) const
{
    if (out)
        out << getId() << ';' << firstname << ';' << lastname << ';' << username << ';' << password << ';' << age << ';' << income << ';' << money << ';' << vectorToStr(real_estate) << ';' << vectorToStr(vehicles) << ';' << roleToStr(role) << '\n';
}

bool User::loadFromCSV(ifstream &in)
{
    if (!in)
        return false;

    real_estate.clear();
    vehicles.clear();

    string line;
    if (getline(in >> std::ws, line))
    {
        stringstream ss(line);
        string idStr, ageStr, incomeStr, moneyStr, real_estate_line, roleStr, vehicles_line;
        getline(ss, idStr, ';');
        getline(ss, firstname, ';');
        getline(ss, lastname, ';');
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, ageStr, ';');
        getline(ss, incomeStr, ';');
        getline(ss, moneyStr, ';');

        getline(ss, real_estate_line, ';');
        if (!real_estate_line.empty())
        {
            stringstream real_estate_vector(real_estate_line);
            string real_estate_id;

            while (getline(real_estate_vector, real_estate_id, ','))
            {
                if (!real_estate_id.empty())
                    real_estate.push_back(stoi(real_estate_id));
            }
        }

        getline(ss, vehicles_line, ';');
        if (!vehicles_line.empty())
        {
            stringstream vehicles_vector(vehicles_line);
            string vehicle_id;

            while (getline(vehicles_vector, vehicle_id, ','))
            {
                if (!vehicle_id.empty())
                    vehicles.push_back(stoi(vehicle_id));
            }
        }

        getline(ss, roleStr);

        if (!idStr.empty())
            setId(stoi(idStr));
        if (!ageStr.empty())
            age = stoi(ageStr);
        if (!incomeStr.empty())
            income = stoi(incomeStr);
        if (!moneyStr.empty())
            money = stoi(moneyStr);
        if (!roleStr.empty())
            role = strToRole(roleStr);
        return true;
    }
    return false;
}

void User::getInfo() const
{
    cout << left << setw(6) << getId()
         << left << setw(15) << firstname
         << left << setw(15) << lastname
         << left << setw(10) << income
         << left << setw(10) << money
         << left << setw(10) << roleToStr(role) << '\n'
         << string(70, '-') << '\n';
}

bool User::showVehicles(const Database<Vehicle> &vdb) const
{
    if (vehicles.empty())
    {
        cout << "\n\t∅ Does not own vehicle!\n\n";
        return false;
    }
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Make]"
             << left << setw(15) << "[Model]"
             << left << setw(10) << "[Fuel]"
             << left << setw(7) << "[Price]"
             << left << setw(9) << "[For Sale]" << '\n'
             << string(63, '=') << '\n';
        for (const auto &v : vehicles)
        {
            auto vptr = vdb.find([&v](const auto &vobj)
                                 { return vobj.getId() == v; });
            if (vptr)
                cout << *vptr;
            else
                cerr << "\t🤷 Missing data for Vehicle [ID]: " << v << '\n';
        }
    }
    cout << string(63, '=') << "\n\n";
    return true;
}

bool User::showRealEstate(const Database<RealEstate> &redb) const
{
    if (real_estate.empty())
    {
        cout << "\n\t∅ Does not own real estate!\n\n";
        return false;
    }
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Type]"
             << left << setw(50) << "[Address]"
             << left << setw(10) << "[Size]"
             << left << setw(7) << "[Price]"
             << left << setw(9) << "[For Sale]" << '\n'
             << string(98, '=') << '\n';
        for (const auto &re : real_estate)
        {
            auto reptr = redb.find([&re](const auto &reobj)
                                   { return reobj.getId() == re; });
            if (reptr)
                cout << *reptr;
            else
                cerr << "\t🤷 Missing data for Real Estate [ID]: " << re << '\n';
        }
    }
    cout << string(98, '=') << "\n\n";
    return true;
}
ostream &User::ins(ostream &out) const
{
    out << left << setw(6) << getId()
        << left << setw(15) << firstname
        << left << setw(15) << lastname
        << left << setw(17) << username
        << left << setw(20) << password
        << left << setw(7) << age
        << left << setw(8) << income
        << left << setw(10) << money
        << left << setw(10) << roleToStr(role) << '\n'
        << string(108, '.') << "\n";
    return out;
}

istream &User::ext(istream &in)
{
    getline(in >> ws, firstname);
    getline(in >> ws, lastname);
    in >> username;
    in >> password;
    in >> age;
    in >> income;
    in >> money;
    in.ignore();
    return in;
}