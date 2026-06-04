#ifndef MENU_HPP
#define MENU_HPP
#include "menu.hpp"
#include "database.hpp"
#include "user.hpp"
#include "user_service.hpp"
#include "vehicle.hpp"
#include "vehicle_service.hpp"
#include "real_estate.hpp"
#include "real_estate_service.hpp"
#include <iostream>
#include <string>
#include <limits>
using std::cerr;
using std::cin;
using std::cout;
using std::string;

void login(Database<User> &, User *&);
bool enterLogInMenu(User *&, Database<User> &, Database<Vehicle> &, Database<RealEstate> &);
void enterAdminMenu(Database<User>&, Database<Vehicle>&, Database<RealEstate>&);
void enterCitizenMenu(User*& currentUser, Database<User>&, Database<Vehicle>&, Database<RealEstate>&);

#endif