#ifndef VEHICLE_SERVICE_HPP
#define VEHICLE_SERVICE_HPP
#include "database.hpp"
#include "vehicle.hpp"

bool getVehiclesForSale(const Database<Vehicle> &);
void getAllVehicles(const Database<Vehicle> &);

#endif