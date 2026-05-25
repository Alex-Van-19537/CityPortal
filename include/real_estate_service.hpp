#ifndef REAL_ESTATE_SERVICE_HPP
#define REAL_ESTATE_SERVICE_HPP

#include "database.hpp"
#include "real_estate.hpp"

bool getRealEstateForSale(const Database<RealEstate>& redb);

#endif