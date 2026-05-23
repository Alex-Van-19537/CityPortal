#include "user.hpp"
#include "database.hpp"
#include "vehicle.hpp"
#include "real_estate.hpp"

const string LOGIN_MENU = "1. Log In\n0. Exit\n";
const string ADMIN_MENU = "1. List users\n2. Add user\n3. Delete user\n4. List Vehicles\n5. Add Vehicle\n6. Delete vehicle\n7. List Real Estate\n8. Add Real Estate\n9. Delete Real Estate\n0. Log Out\n";
const string CITIZEN_MENU = "\n--- Citizen Options ---\n1. View My Profile\n0. Log Out\n";

const string usersFile = "../data/users.csv";
const string vehiclesFile = "../data/vehicles.csv";
const string real_estateFile = "../data/real_estate.csv";

void login(const Database<User>&,const User*&);

int main()
{
    Database<User> usersDB(usersFile);
    Database<Vehicle> vehiclesDB(vehiclesFile);
    Database<RealEstate> real_estateDB(real_estateFile);

    const User *currentUser = nullptr;

    int choice = 0;
    do
    {
        if (currentUser == nullptr)
        {
            cout << "\n====================== City Portal Application ======================\n\n";
            cout << LOGIN_MENU;
            cout << "\nChoice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
            {
                login(usersDB, currentUser);
                break;
            }
            case 11:
                currentUser = usersDB.find([](const auto &u)
                                           { return u.getId() == 1; });
                cout << "🥹  Welcome back, " << currentUser->getUsername() << "!\n";
                break;
            case 0:
                cout << "😵 Shutting down...\n";
                break;

            default:
                cerr << "❓ Unrecognized option!\n";
            }
        }
        else if (currentUser->getRole() == Role::ADMIN)
        {
            cout << "\n====================== Admin Menu ======================\n\n";
            cout << ADMIN_MENU;
            cout << "\nChoice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cout << "\n====================== Users ======================\n\n";
                for (const auto &u : usersDB.getData())
                    u.printUserCard(vehiclesDB, real_estateDB);
                break;
            case 2:
            {
                string firstname, lastname, username, password;
                int age;
                cout << "Firstname: ";
                getline(cin >> ws, firstname);
                cout << "Lastname: ";
                getline(cin >> ws, lastname);
                cout << "Username: ";
                getline(cin >> ws, username);
                cout << "Password: ";
                getline(cin >> ws, password);
                cout << "Age: ";
                cin >> age;
                cin.ignore();

                usersDB.add(User(usersDB.getNextId(), firstname, lastname, username, password, age));
                cout << "✅ [Success]: User added with ID: " << usersDB.getNextId() - 1 << "!\n";
                break;
            }

            case 3:
            {
                int deleteId;
                cout << "User to be deleted [ID]: ";
                cin >> deleteId;
                cin.ignore();
                if (usersDB.remove(deleteId))
                    cout << "✅ [Success]: User with ID " << deleteId << " was deleted!\n";
                else
                    cout << "❌ [Error]: User with ID " << deleteId << " not found.\n";
                break;
            }

            case 4:
                cout << "\n====================== Vehicles ======================\n\n";
                cout << left << setw(6) << "[ID]"
                     << left << setw(15) << "[Model]"
                     << left << setw(15) << "[Make]"
                     << left << setw(10) << "[Fuel]"
                     << left << setw(7) << "[Price]" << '\n'
                     << string(53, '=') << "\n";
                vehiclesDB.list();
                break;

            case 5:
            {
                string make, model, fuelStr;
                int price;
                cout << "Make: ";
                getline(cin >> ws, make);
                cout << "Model: ";
                getline(cin >> ws, model);
                cout << "Fuel [ Petrol, Diesel, LPG ]: ";
                getline(cin >> ws, fuelStr);
                cout << "Price: ";
                cin >> price;
                cin.ignore();

                vehiclesDB.add(Vehicle(vehiclesDB.getNextId(), make, model, strToFuel(fuelStr), price));
                cout << "✅ [Success]: Vehicle added with ID: " << vehiclesDB.getNextId() - 1 << "!\n";
                break;
            }

            case 6:
            {
                int deleteId;
                cout << "Vehicle to be deleted [ID]: ";
                cin >> deleteId;
                cin.ignore();
                if (vehiclesDB.remove(deleteId))
                    cout << "✅ [Success]: Vehicle with ID " << deleteId << " was deleted!\n";
                else
                    cout << "❌ [Error]: Vehicle with ID " << deleteId << " not found.\n";
                break;
            }

            case 7:
                cout << "\n====================== Real Estate ======================\n\n";
                cout << left << setw(6) << "[ID]"
                     << left << setw(15) << "[Type]"
                     << left << setw(50) << "[Address]"
                     << left << setw(10) << "[Size(m2)]"
                     << left << setw(7) << "[Price]" << '\n'
                     << string(88, '=') << "\n";
                real_estateDB.list();
                break;

            case 8:
            {
                string type, address;
                int price, size;
                cout << "Type [Apartment, House, Studio, Maisonette]: ";
                getline(cin >> ws, type);
                cout << "Address: ";
                getline(cin >> ws, address);
                cout << "Size [m2]: ";
                cin >> size;
                cout << "Price: ";
                cin >> price;
                cin.ignore();

                real_estateDB.add(RealEstate(real_estateDB.getNextId(), strToEType(type), address, size, price));
                cout << "✅ [Success]: Real Estate added with ID: " << vehiclesDB.getNextId() - 1 << "!\n";
                break;
            }

            case 9:
            {
                int deleteId;
                cout << "Real Estate to be deleted [ID]: ";
                cin >> deleteId;
                cin.ignore();
                if (real_estateDB.remove(deleteId))
                    cout << "✅ [Success]: Real Estate with ID " << deleteId << " was deleted!\n";
                else
                    cout << "❌ [Error]: Real Estate with ID " << deleteId << " not found.\n";
                break;
            }

            case 0:
                cout << "🥲  Goodbye, " << currentUser->getUsername() << "!\n";
                currentUser = nullptr;
                choice = -1;
                break;
            default:
                cerr << "❓ Unrecognized option!\n";
            }
        }
        else if (currentUser->getRole() == Role::CITIZEN)
        {
            cout << "\n====================== Citizen Menu ======================\n\n";
            cout << CITIZEN_MENU;
            cout << "\nChoice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
                currentUser->printUserCard(vehiclesDB, real_estateDB);
                break;

            case 0:
                cout << "🥲  Goodbye, " << currentUser->getUsername() << "!\n";
                currentUser = nullptr;
                choice = -1;
                break;
            default:
                cerr << "❓ Unrecognized option!\n";
            }
        }

    } while (choice != 0);
    return 0;
}

void login(const Database<User>& usersDB, const User*& currentUser){
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (const User *tmp = usersDB.find([&username](const User &u)
                                        { return u.getUsername() == username; }))
    {
        if (tmp->getPassword() == password)
        {
            currentUser = tmp;
            cout << "🥹  Welcome back, " << currentUser->getUsername() << "!\n";
        }
        else
            cerr << "⛔ Wrong username or password!\n";
    }
    else
        cerr << "⛔ Wrong username or password!\n";
}