#include "real_estate_service.hpp"

bool getRealEstateForSale(const Database<RealEstate> &redb)
{
    if (!redb.find([](const RealEstate &re)
                   { return re.getForSale(); })){
        cout << "\n\t∅ There are no real estate for sale right now!!\n\n";
        return false;
    }
    else
    {
        for (const auto &re : redb.getData())
        {
            if (re.getForSale())
                cout << re;
        }
    }
    return true;
}