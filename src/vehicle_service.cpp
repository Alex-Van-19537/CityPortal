#include "vehicle_service.hpp"

void getAllVehicles(const Database<Vehicle> &vdb)
{
    if (vdb.empty())
    {
        cerr << "\n\t∅ There are no vehicles!\n\n";
    }
    cout << left << setw(6) << "[ID]"
         << left << setw(15) << "[Make]"
         << left << setw(15) << "[Model]"
         << left << setw(10) << "[Fuel]"
         << left << setw(7) << "[Price]"
         << left << setw(9) << "[For Sale]" << '\n'
         << string(63, '=') << '\n';
    for (auto &v : vdb.getData())
    {
        cout << v;
    }
}

bool getVehiclesForSale(const Database<Vehicle> &vdb)
{
    if (!vdb.find([](const Vehicle &v)
                  { return v.getForSale(); }))
    {
        cout << "\n\t∅ There are no vehicles for sale right now!!\n\n";
        return false;
    }
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Make]"
             << left << setw(15) << "[Model]"
             << left << setw(10) << "[Fuel]"
             << left << setw(7) << "[Price]"
             << left << setw(9) << "[For Sale]" << '\n'
             << string(63, '=') << '\n';
        for (const auto &v : vdb.getData())
        {
            if (v.getForSale())
                cout << v;
        }
    }
    return true;
}