#ifndef USER_SERVICE_HPP
#define USER_SERVICE_HPP
#include "user.hpp"
#include "database.hpp"
#include "vehicle.hpp"
#include "real_estate.hpp"

void printUserCard(const User &, const Database<Vehicle> &, const Database<RealEstate> &);
void buyRealEstate(User *, Database<User> &, Database<RealEstate> &);
void buyVehicle(User *, Database<User> &, Database<Vehicle> &);
void comleteMonth(Database<User> &);

#endif