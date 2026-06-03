#include "vehicle_service.hpp"

bool getVehiclesForSale(const Database<Vehicle> &vdb)
{
    if (!vdb.find([](const Vehicle &v)
                 { return v.getForSale(); })){
        cout << "\n\t∅ There are no vehicles for sale right now!!\n\n";
        return false;
    }
    else
    {
        for (const auto &v : vdb.getData())
        {
            if (v.getForSale())
                cout << v;
        }
    }
    return true;
}