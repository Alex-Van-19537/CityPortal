#include "app.hpp"

App::App(): usersDB(usersFile), vehiclesDB(vehiclesFile), real_estateDB(real_estateFile), currentUser(nullptr), isRunning(false) {}

App::~App(){}

bool App::init(){
    isRunning = true;
    return true;
}

void App::run(){
    while(isRunning){
        if (!currentUser)
        {
            if (!enterLogInMenu(currentUser, usersDB, vehiclesDB, real_estateDB))
                isRunning = false;
                continue;
        }

        if (currentUser->getRole() == Role::ADMIN)
        {
            enterAdminMenu(usersDB, vehiclesDB, real_estateDB);
        }

        else if (currentUser->getRole() == Role::CITIZEN)
        {
            enterCitizenMenu(currentUser, usersDB, vehiclesDB, real_estateDB);
        }
        cout << "🥲 See you the next time " << currentUser->getUsername() << "!\n";
        currentUser = nullptr;
    }
}