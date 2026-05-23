#include "user.hpp"

string User::getFirstname() const { return firstname; }
string User::getLastname() const { return lastname; }
string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
unsigned User::getAge() const { return age; }
unsigned User::getIncome() const { return income; }
const vector<int> &User::getRealEstates() const { return real_estate; }
const vector<int> &User::getVehicles() const { return vehicles; }
const Role &User::getRole() const { return role; }

void User::setFirstname(const string &firstname) { this->firstname = firstname; }
void User::setLastname(const string &lastname) { this->lastname = lastname; }
void User::setAge(int age) { this->age = age; }
void User::setIncome(unsigned i) { income = i; }
void User::setRealEstates(vector<int> re) { real_estate = re; }
void User::setVehicles(vector<int> v) { vehicles = v; }


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
           const vector<int> &re,
           const vector<int> &v,
           const Role &role) : Entry(id),
                               firstname(fname),
                               lastname(lname),
                               username(username),
                               password(password),
                               age(age),
                               income(income),
                               real_estate(re),
                               vehicles(v),
                               role(role) {}

void User::writeToCSV(ofstream &out) const
{
    if (out)
        out << getId() << ';' << firstname << ';' << lastname << ';' << username << ';' << password << ';' << age << ';' << income << ';' << vectorToStr(real_estate) << ';' << vectorToStr(vehicles) << ';' << roleToStr(role) << '\n';
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
        string idStr, ageStr, incomeStr, real_estate_line, roleStr, vehicles_line;
        getline(ss, idStr, ';');
        getline(ss, firstname, ';');
        getline(ss, lastname, ';');
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, ageStr, ';');
        getline(ss, incomeStr, ';');

        getline(ss, real_estate_line, ';');
        if (!real_estate_line.empty()){
            stringstream real_estate_vector(real_estate_line);
            string real_estate_id;

            while (getline(real_estate_vector, real_estate_id, ',')){
                if(!real_estate_id.empty())
                    real_estate.push_back(stoi(real_estate_id));
            }
        }

        getline(ss, vehicles_line, ';');
        if(!vehicles_line.empty()){
            stringstream vehicles_vector(vehicles_line);
            string vehicle_id;
            
            while (getline(vehicles_vector, vehicle_id, ',')){
                if(!vehicle_id.empty())
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
         << left << setw(10) << roleToStr(role)
         << string(50, '-') << '\n';
}

ostream &User::ins(ostream &out) const
{
    out << left << setw(6) << getId()
        << left << setw(15) << firstname
        << left << setw(15) << lastname
        << left << setw(17) << username
        << left << setw(20) << password
        << left << setw(7) << age
        << left << setw(10) << income
        << left << setw(10) << roleToStr(role) << '\n'
        << string(100, '.') << "\n";
        return out;
}

istream &User::ext(istream &in)
{
    getline(in >> ws, firstname);
    getline(in >> ws, lastname);
    in >> username;
    in >> password;
    in >> age;
    in.ignore();
    return in;
}