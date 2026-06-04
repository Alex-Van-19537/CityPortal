#include "real_estate_service.hpp"

void getAllRE(const Database<RealEstate> &redb)
{
    if (redb.empty())
    {
        cerr << "\n\t∅ There are no vehicles!\n\n";
    }
    cout << left << setw(6) << "[ID]"
         << left << setw(15) << "[Type]"
         << left << setw(50) << "[Address]"
         << left << setw(10) << "[Size]"
         << left << setw(7) << "[Price]"
         << left << setw(9) << "[For Sale]" << '\n'
         << string(98, '=') << '\n';
    for (auto &re : redb.getData())
    {
        cout << re;
    }
}

bool getRealEstateForSale(const Database<RealEstate> &redb)
{
    if (!redb.find([](const RealEstate &re)
                   { return re.getForSale(); }))
    {
        cout << "\n\t∅ There are no real estate for sale right now!!\n\n";
        return false;
    }
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Type]"
             << left << setw(50) << "[Address]"
             << left << setw(10) << "[Size]"
             << left << setw(7) << "[Price]"
             << left << setw(9) << "[For Sale]" << '\n'
             << string(98, '=') << '\n';
        for (const auto &re : redb.getData())
        {
            if (re.getForSale())
                cout << re;
        }
    }
    return true;
}