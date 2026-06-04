#include "user_service.hpp"

void printUsersShort(const Database<User> &usersDB)
{
    cout << left << setw(6) << "[ID]"
         << left << setw(15) << "[Firstname]"
         << left << setw(15) << "[Lastname]"
         << left << setw(10) << "[Income]"
         << left << setw(10) << "[Money]"
         << left << setw(10) << "[Role]" << '\n'
         << string(70, '-') << "\n";
    for (auto &u : usersDB.getData())
    {
        u.getInfo();
    }
}

void printUserCard(const User &user, const Database<Vehicle> &vdb, const Database<RealEstate> &redb)
{
    cout << left << setw(6) << "[ID]"
         << left << setw(15) << "[Firstname]"
         << left << setw(15) << "[Lastname]"
         << left << setw(17) << "[Username]"
         << left << setw(20) << "[Password]"
         << left << setw(7) << "[Age]"
         << left << setw(10) << "[Income]"
         << left << setw(10) << "[Money]"
         << left << setw(10) << "[Role]" << '\n'
         << string(110, '=') << "\n";

    cout << left << setw(6) << user.getId()
         << left << setw(15) << user.getFirstname()
         << left << setw(15) << user.getLastname()
         << left << setw(17) << user.getUsername()
         << left << setw(20) << user.getPassword()
         << left << setw(7) << user.getAge()
         << left << setw(10) << user.getIncome()
         << left << setw(10) << user.getMoney()
         << left << setw(10) << roleToStr(user.getRole()) << '\n'
         << string(110, '.') << "\n\n"
         << "🚘 Vehicles:\n";

    if (user.getVehicles().empty())
        cout << "\n\t∅ Does not own vehicle!\n\n";
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Make]"
             << left << setw(15) << "[Model]"
             << left << setw(10) << "[Fuel]"
             << left << setw(7) << "[Price]"
             << left << setw(9) << "[For Sale]" << '\n'
             << string(63, '=') << '\n';
        for (const auto &v : user.getVehicles())
        {
            auto vptr = vdb.find([&v](const auto &vobj)
                                 { return vobj.getId() == v; });
            if (vptr)
                cout << *vptr;
            else
                cerr << "\t🤷 Missing data for Vehicle [ID]: " << v << '\n';
        }
    }

    cout << "🏠 Real Estate:\n";

    if (user.getRealEstates().empty())
        cout << "\n\t∅ Does not own real estate!\n\n";
    else
    {
        cout << left << setw(6) << "[ID]"
             << left << setw(15) << "[Type]"
             << left << setw(50) << "[Address]"
             << left << setw(10) << "[Size]"
             << left << setw(7) << "[Price]"
             << left << setw(9) << "[For Sale]" << '\n'
             << string(98, '=') << '\n';
        for (const auto &re : user.getRealEstates())
        {
            auto reptr = redb.find([&re](const auto &reobj)
                                   { return reobj.getId() == re; });
            if (reptr)
                cout << *reptr;
            else
                cerr << "\t🤷 Missing data for Real Estate [ID]: " << re << '\n';
        }
    }
    cout << string(108, '=') << "\n\n";
}

void completeMonth(Database<User> &udb)
{
    for (auto &u : udb.getData())
    {
        int newBalance = u.getMoney() + u.getIncome();
        u.setMoney(newBalance);
    }
    if (!udb.save())
        cout << "\n\t[Failed] Completing month!\n";
    else
        cout << "\n\t[Success] Completing month!\n";
}

void buyRealEstate(User *currentUser, Database<User> &usersDB, Database<RealEstate> &real_estateDB)
{
    int reId;
    cout << "Real Estate to buy[ID]: ";
    cin >> reId;
    RealEstate *reptr = real_estateDB.find([reId](const RealEstate &re)
                                           { return reId == re.getId(); });
    if (!reptr)
    {
        cout << "[Fail] There is not Real Estate with ID [" << reId << "] for sale!\n";
        return;
    }
    else if (!reptr->getForSale())
    {
        cout << "[Fali] There is not Real Estate with ID [" << reId << "] for sale!\n";
        return;
    }
    else if (reptr->getPrice() > currentUser->getMoney())
    {
        cout << "[Fail] You don't have enough money to buy this Real Estate!\n";
        return;
    }
    else
    {
        User *uptr = usersDB.find([reId](const User &u)
                                  { 
            for(const auto &re:u.getRealEstates()){
                if(re == reId) 
                    return true;
            }
            return false; });
        if (uptr)
        {
            if (uptr->getId() == currentUser->getId())
            {
                cout << "[Fail] You are the owner of this Real Estate!\n";
                return;
            }
            uptr->setMoney(uptr->getMoney() + reptr->getPrice());
            vector<int> newRealEstateS = uptr->getRealEstates();
            newRealEstateS.erase(remove_if(newRealEstateS.begin(), newRealEstateS.end(), [reId](const int re)
                                           { return re == reId; }),
                                 newRealEstateS.end());
            uptr->setRealEstates(newRealEstateS);
        }
        currentUser->setMoney(currentUser->getMoney() - reptr->getPrice());
        vector<int> newRealEstateB = currentUser->getRealEstates();
        newRealEstateB.push_back(reId);
        currentUser->setRealEstates(newRealEstateB);
        reptr->setForSale(false);
        if (!usersDB.save() || !real_estateDB.save())
            cout << "[Fail] Transaction failed and Real Estate with ID [" << reId << "] remains for sale!\n";
        cout << "[Success] Transaction is successful and Real Estate with ID [" << reId << "] is yours!\n";
    }
}

void buyVehicle(User *currentUser, Database<User> &usersDB, Database<Vehicle> &vehiclesDB)
{
    int vehicleId;
    cout << "Vehicle to buy[ID]: ";
    cin >> vehicleId;
    Vehicle *vptr = vehiclesDB.find([vehicleId](const Vehicle &v)
                                    { return vehicleId == v.getId(); });
    if (!vptr)
    {
        cout << "There is not Vehicle with ID [" << vehicleId << "] for sale!\n";
        return;
    }
    else if (!vptr->getForSale())
    {
        cout << "There is not Vehicle with ID [" << vehicleId << "] for sale!\n";
        return;
    }
    else if (vptr->getPrice() > currentUser->getMoney())
    {
        cout << "You don't have enough money to buy this Vehicle!\n";
        return;
    }
    else
    {
        User *uptr = usersDB.find([vehicleId](const User &u)
                                  { 
            for(const auto &v:u.getVehicles()){
                if(v == vehicleId) 
                    return true;
            }
            return false; });
        if (uptr)
        {
            if (uptr->getId() == currentUser->getId())
            {
                cout << "[Fail] You are the owner of this Vehicle!\n";
                return;
            }
            uptr->setMoney(uptr->getMoney() + vptr->getPrice());
            vector<int> newVehiclesS = uptr->getVehicles();
            newVehiclesS.erase(remove_if(newVehiclesS.begin(), newVehiclesS.end(), [vehicleId](const int vId)
                                         { return vId == vehicleId; }),
                               newVehiclesS.end());
            uptr->setVehicles(newVehiclesS);
        }
        currentUser->setMoney(currentUser->getMoney() - vptr->getPrice());
        vector<int> newVehiclesB = currentUser->getVehicles();
        newVehiclesB.push_back(vehicleId);
        currentUser->setVehicles(newVehiclesB);
        vptr->setForSale(false);
        if (!usersDB.save() || !vehiclesDB.save())
            cout << "[Fail] Transaction failed and Vehicle with ID [" << vehicleId << "] remains for sale!\n";
        cout << "[Success] Transaction is successful and Vehicle with ID [" << vehicleId << "] is yours!\n";
    }
}