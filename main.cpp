#include "menu.hpp"

const string usersFile = "../data/users.csv";
const string vehiclesFile = "../data/vehicles.csv";
const string real_estateFile = "../data/real_estate.csv";

int main()
{
    Database<User> usersDB(usersFile);
    Database<Vehicle> vehiclesDB(vehiclesFile);
    Database<RealEstate> real_estateDB(real_estateFile);

    User *currentUser = nullptr;

    int choice = 0;
    do
    {
        
        if (!currentUser)
        {
            if (!enterLogInMenu(currentUser, usersDB, vehiclesDB, real_estateDB))
                return 0;
        }

        else if (currentUser->getRole() == Role::ADMIN)
        {
            enterAdminMenu(usersDB, vehiclesDB, real_estateDB);
            currentUser = nullptr;
        }

        else if (currentUser->getRole() == Role::CITIZEN)
        {
            enterCitizenMenu(currentUser, usersDB, vehiclesDB, real_estateDB);
            currentUser = nullptr;
        }

    } while (1);
    return 0;
}