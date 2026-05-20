#include "user.hpp"
#include "database.hpp"

const string LOGIN_MENU = "\nLog In as:\n1. Admin\n2. users\n0. Exit\n";
const string ADMIN_MENU = "\nOptions:\n1. List users\n2. Add entry\n3. Delete entry\n0. Log Out\n";
const string users_MENU = "";

int main()
{
    const string usersFile = "../data/users.csv";
    Database<User> usersDB(usersFile);

    int choice = 0;
    do
    {
        cout << "\n======== CSV Database ========\n";

        cout << ADMIN_MENU;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
            // case 1:
            // {
            //     string username, password;
            //     cout << "Username: ";
            //     cin >> username;
            //     cout << "Password: ";
            //     cin >> password;

            // }
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
            getline(cin>>ws, firstname);
            cout << "Lastname: ";
            getline(cin>>ws, lastname);
            cout << "Username: ";
            getline(cin>>ws, username);
            cout << "Password: ";
            getline(cin>>ws, password);
            cout << "Age: ";
            cin >> age;
            cin.ignore();

            // Създаваме обекта с новото му ID
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
            break;

        default:
            cerr << "Unrecodnised option!\n";
            break;
        }
    } while (choice != 0);
    return 0;
}