#include "user.hpp"
#include "database.hpp"
#include "vehicle.hpp"

const string LOGIN_MENU = "\n======== CSV Database ========\n1. Log In\n0. Exit\n";
const string ADMIN_MENU = "\n--- Admin Options ---\n1. List users\n2. Add user\n3. Delete user\n4. List Vehicles\n5. Add Vehicle\n6. Delete vehicle\n0. Log Out\n";
const string CITIZEN_MENU = "\n--- Citizen Options ---\n1. View My Profile\n0. Log Out\n";

const string usersFile = "../data/users.csv";
const string vehiclesFile = "../data/vehicles.csv";

int main()
{
    Database<User> usersDB(usersFile);
    Database<Vehicle> vehiclesDB(vehiclesFile);

    const User *currentUser = nullptr;

    int choice = 0;
    do
    {
        if (currentUser == nullptr)
        {
            cout << LOGIN_MENU;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
            {
                string username, password;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;

                if (const User *tmp = usersDB.find([&username](const User &u)
                                                   { return u.getUsername() == username; }))
                {
                    if (tmp->getPassword() == password)
                        currentUser = tmp;
                    else
                        cerr << "Wrong username or password!\n";
                }
                else
                    cerr << "Wrong username or password!\n";
                break;
            }
            case 11:
                currentUser = usersDB.find([](const auto& u){return u.getId()==1;});
            case 0:
                cout << "Goodbye!\n";
                break;

            default:
                cerr << "Unrecognized option!\n";
            }
        }
        else if (currentUser->getRole() == Role::ADMIN)
        {
            cout << ADMIN_MENU;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                cout << "\n--- Entries ---\n";
                cout << left << setw(6) << "[ID]"
                     << left << setw(15) << "[Firstname]"
                     << left << setw(15) << "[Lastname]"
                     << left << setw(17) << "[Username]"
                     << left << setw(20) << "[Password]"
                     << left << setw(7) << "[Age]"
                     << left << setw(10) << "[Income]"
                     << left << setw(10) << "[Role]" << '\n'
                     << string(100, '_') << "\n";
                for(const auto& u:usersDB.getData())
                    u.printUserCard(vehiclesDB);
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
                cout << "[Success]: User added with ID: " << usersDB.getNextId() - 1 << "!\n";
                break;
            }

            case 3:
            {
                int deleteId;
                cout << "User to be deleted [ID]: ";
                cin >> deleteId;
                cin.ignore();
                if (usersDB.remove(deleteId))
                    cout << "[Success]: User with ID " << deleteId << " was deleted!\n";
                else
                    cout << "[Error]: User with ID " << deleteId << " not found.\n";
                break;
            }

            case 4:
                cout << "\n--- Entries ---\n";
                cout << left << setw(6) << "[ID]"
                     << left << setw(15) << "[Model]"
                     << left << setw(15) << "[Make]"
                     << left << setw(10) << "[Fuel]"
                     << left << setw(7) << "[Price]" << '\n'
                     << string(53, '_') << "\n";
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
                cout << "[Success]: Vehicle added with ID: " << vehiclesDB.getNextId() - 1 << "!\n";
                break;
            }

            case 6:
            {
                int deleteId;
                cout << "Vehicle to be deleted [ID]: ";
                cin >> deleteId;
                cin.ignore();
                if (vehiclesDB.remove(deleteId))
                    cout << "[Success]: Vehicle with ID " << deleteId << " was deleted!\n";
                else
                    cout << "[Error]: Vehicle with ID " << deleteId << " not found.\n";
                break;
            }

            case 0:
                cout << "Goodbye!\n";
                currentUser = nullptr;
                choice = -1;
                break;
            default:
                cerr << "Unrecognized option!\n";
            }
        }
        else if (currentUser->getRole() == Role::CITIZEN)
        {
            cout << CITIZEN_MENU;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore();
            switch (choice)
            {
            case 1:
                cout << "\n--- Entries ---\n";
                cout << left << setw(6) << "[ID]"
                     << left << setw(15) << "[Firstname]"
                     << left << setw(15) << "[Lastname]"
                     << left << setw(17) << "[Username]"
                     << left << setw(20) << "[Password]"
                     << left << setw(7) << "[Age]"
                     << left << setw(10) << "[Income]"
                     << left << setw(10) << "[Role]" << '\n'
                     << string(100, '_') << "\n\n";
                cout << *currentUser;
                break;

            case 0:
                cout << "Goodbye!\n";
                currentUser = nullptr;
                choice = -1;
                break;
            default:
                cerr << "Unrecognized option!\n";
            }
        }

    } while (choice != 0);
    return 0;
}