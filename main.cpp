#include "user.hpp"
#include "database.hpp"

const string LOGIN_MENU = "\n======== CSV Database ========\n1. Log In\n0. Exit\n";
const string ADMIN_MENU = "\n--- Admin Options ---\n1. List users\n2. Add entry\n3. Delete entry\n0. Log Out\n";
const string CITIZEN_MENU = "\n--- Citizen Options ---\n1. View My Profile\n0. Log Out\n";

int main()
{
    const string usersFile = "../data/users.csv";
    Database<User> usersDB(usersFile);

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
                     << string(100, '_') << "\n\n";
                usersDB.list();
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
                cout << "[Success]: Entry added with ID: " << usersDB.getNextId() - 1 << "!\n";
                break;
            }

            case 3:
            {
                int deleteId;
                cout << "Entry to be deleted [ID]: ";
                cin >> deleteId;
                cin.ignore();
                if (usersDB.remove(deleteId))
                    cout << "[Success]: Entry with ID " << deleteId << " was deleted!\n";
                else
                    cout << "[Error]: Entry with ID " << deleteId << " not found.\n";
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