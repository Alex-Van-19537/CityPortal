#include "menu.hpp"

const string LOGIN_MENU = "1. Log In\n0. Exit\n";
const string MAIN_CITIZEN_MENU = "1. View My Profile\n2. Manage Vehicles\n3. Manage Real Estate\n0. Log Out\n";
const string VEHICLE_CITIZEN_MENU = "1. Get Vehicles for sale\n2. Put Vehicle for sale\n3. Delist Vehicle from sale\n4. Buy Vehicle\n0. Back\n";
const string RE_CITIZEN_MENU = "1. Get Real Estate for sale\n2. Put Real Estate for sale\n3. Delist Real Estate from sale\n4. Buy Real Estate\n0. Back\n";
const string MAIN_ADMIN_MENU = "1. Manage Users\n2. Manage Vehicles\n3. Manage Real Estate\n0. Log Out\n";
const string USERS_ADMIN_MENU = "1. List users\n2. Add user\n3. Change user income\n4. Change user balance\n5. Delete user\n6. Complete Month\n0. Back\n";
const string VEHICLES_ADMIN_MENU = "1. List Vehicles\n2. Add Vehicle\n3. Delete vehicle\n0. Back\n";
const string RE_ADMIN_MENU = "1. List Real Estate\n2. Add Real Estate\n3. Delete Real Estate\n0. Back\n";

int getValidInt()
{
    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        choice = -1;
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

char getValidChar()
{
    char choice;
    if (!(cin >> choice))
    {
        cin.clear();
        choice = '\0';
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

bool assuringPrompt()
{
    char choice = ' ';
    int cnt = 0;
    while (choice != 'n' && choice != 'y' && cnt != 3)
    {
        cout << "Are you sure you want to proceed whit this operation [y/n]: ";
        choice = getValidChar();
        choice = std::tolower(choice);
        cnt++;
    }
    if (choice == 'y')
        return true;
    cout << "Operation aborted!\n";
    return false;
}

void login(Database<User> &usersDB, User *&currentUser)
{
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (User *tmp = usersDB.find([&username](const User &u)
                                 { return u.getUsername() == username; }))
    {
        if (tmp->getPassword() == password)
        {
            currentUser = tmp;
            cout << "🥹  Welcome back, " << currentUser->getUsername() << "!\n";
        }
        else
            cerr << "\n\t⛔ Wrong username or password!\n";
    }
    else
        cerr << "\n\t⛔ Wrong username or password!\n";
}

bool enterLogInMenu(User *&currentUser, Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== City Portal Application ======================\n\n";
        cout << LOGIN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();

        switch (choice)
        {
        case 1:
        {
            login(usersDB, currentUser);
            return true;
        }
        case 11:
            currentUser = usersDB.find([](const auto &u)
                                       { return u.getId() == 1; });
            cout << "🥹  Welcome back, " << currentUser->getUsername() << "!\n";
            return true;
        case 0:
            cout << "😵 Shutting down...\n";
            return false;

        default:
            cerr << "⛔ Invalid command!\n";
            choice = -1;
        }
    } while (choice != 0);
    return false;
}

void enterAdminMenu(Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Admin Menu ======================\n\n";
        cout << MAIN_ADMIN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();

        switch (choice)
        {
        case 1:
        {
            enterAdminManageUsersMenu(usersDB, vehiclesDB, real_estateDB);
            break;
        }
        case 2:
        {
            enterAdminManageVehiclesMenu(usersDB, vehiclesDB, real_estateDB);
            break;
        }
        case 3:
        {
            enterAdminManageRealEstateMenu(usersDB, vehiclesDB, real_estateDB);
            break;
        }
        case 0:
            break;
        default:
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
        }
    } while (choice != 0);
}

void enterAdminManageUsersMenu(Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Manage Users ======================\n\n";
        cout << USERS_ADMIN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();
        switch (choice)
        {
        case 1:
            cout << "\n====================== Users ======================\n\n";
            for (const auto &u : usersDB.getData())
                printUserCard(u, vehiclesDB, real_estateDB);
            break;
        case 2:
        {
            string firstname, lastname, username, password;
            int age = -1, cnt = 0;
            cout << "Firstname: ";
            getline(cin >> ws, firstname);
            cout << "Lastname: ";
            getline(cin >> ws, lastname);
            cout << "Username: ";
            getline(cin >> ws, username);
            cout << "Password: ";
            getline(cin >> ws, password);
            while (age < 0 && age > 120 && cnt <= 3)
            {
                cout << "Age (0 - 120): ";
                age = getValidInt();
                cnt++;
            }
            if (age < 0 || age > 120)
            {
                cout << "Operation aborted!\n";
                break;
            }

            usersDB.add(User(usersDB.getNextId(), firstname, lastname, username, password, age));
            cout << "✅ [Success]: User added with ID: " << usersDB.getNextId() - 1 << "!\n";
            break;
        }

        case 3:
        {
            int uId;
            printUsersShort(usersDB);
            cout << "User to be modified [ID]: ";
            uId = getValidInt();
            User *user = usersDB.find([uId](const User &u)
                                      { return u.getId() == uId; });
            if (!user)
            {
                cerr << "⛔ There is not user with ID: " << uId << '\n';
                break;
            }
            int newIncome;
            cout << "Change income to: ";
            newIncome = getValidInt();
            if (newIncome < 0)
            {
                cerr << "\n\t⛔ Citizens cannot have negative income!\n";
                break;
            }
            user->setIncome(newIncome);
            usersDB.save();
            break;
        }

        case 4:
        {
            int uId;
            printUsersShort(usersDB);
            cout << "User to be modified [ID]: ";
            uId = getValidInt();
            User *user = usersDB.find([uId](const User &u)
                                      { return u.getId() == uId; });
            if (!user)
            {
                cerr << "⛔ There is not user with ID: " << uId << '\n';
                break;
            }
            int newMoney;
            cout << "Change money to: ";
            newMoney = getValidInt();
            if (newMoney < 0)
            {
                if (!assuringPrompt())
                    break;
            }
            user->setMoney(newMoney);
            usersDB.save();
            break;
        }

        case 5:
        {
            int deleteId;
            printUsersShort(usersDB);
            cout << "User to be deleted [ID]: ";
            deleteId = getValidInt();
            if (!assuringPrompt())
                break;
            if (usersDB.remove(deleteId))
                cout << "✅ [Success]: User with ID " << deleteId << " was deleted!\n";
            else
                cout << "❌ [Error]: User with ID " << deleteId << " not found.\n";
            break;
        }
        case 6:
        {
            completeMonth(usersDB);
            break;
        }
        case 0:
            break;
        default:
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
        }
    } while (choice != 0);
}

void enterAdminManageVehiclesMenu(Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Manage Vehicles ======================\n\n";
        cout << VEHICLES_ADMIN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();
        switch (choice)
        {
        case 1:
            cout << "\n====================== Vehicles ======================\n\n";
            cout << left << setw(6) << "[ID]"
                 << left << setw(15) << "[Make]"
                 << left << setw(15) << "[Model]"
                 << left << setw(10) << "[Fuel]"
                 << left << setw(7) << "[Price]"
                 << left << setw(9) << "[For Sale]" << '\n'
                 << string(63, '=') << '\n';
            vehiclesDB.list();
            break;

        case 2:
        {
            string make, model, fuelStr;
            int price;
            cout << "Make: ";
            getline(cin >> ws, make);
            cout << "Model: ";
            getline(cin >> ws, model);
            cout << "Fuel [ Petrol, Diesel, LPG ]: ";
            getline(cin >> ws, fuelStr);
            cout << "Price: ";
            price = getValidInt();

            vehiclesDB.add(Vehicle(vehiclesDB.getNextId(), make, model, strToFuel(fuelStr), price));
            cout << "✅ [Success]: Vehicle added with ID: " << vehiclesDB.getNextId() - 1 << "!\n";
            break;
        }

        case 3:
        {
            int deleteId;
            getAllVehicles(vehiclesDB);
            cout << "Vehicle to be deleted [ID]: ";
            deleteId = getValidInt();
            if (!assuringPrompt())
                break;
            if (vehiclesDB.remove(deleteId))
                cout << "✅ [Success]: Vehicle with ID " << deleteId << " was deleted!\n";
            else
                cout << "❌ [Error]: Vehicle with ID " << deleteId << " not found.\n";
            break;
        }
        case 0:
            break;
        default:
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
            break;
        }
    } while (choice != 0);
}

void enterAdminManageRealEstateMenu(Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Manage Real Estate ======================\n\n";
        cout << RE_ADMIN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();

        switch (choice)
        {
        case 1:
            cout << "\n====================== Real Estate ======================\n\n";
            cout << left << setw(6) << "[ID]"
                 << left << setw(15) << "[Type]"
                 << left << setw(50) << "[Address]"
                 << left << setw(10) << "[Size]"
                 << left << setw(7) << "[Price]"
                 << left << setw(9) << "[For Sale]" << '\n'
                 << string(98, '=') << '\n';
            real_estateDB.list();
            break;

        case 2:
        {
            string type, address;
            int price, size;
            cout << "Type [Apartment, House, Studio, Maisonette]: ";
            getline(cin >> ws, type);
            cout << "Address: ";
            getline(cin >> ws, address);
            cout << "Size [m2]: ";
            cin >> size;
            cout << "Price: ";
            price = getValidInt();

            real_estateDB.add(RealEstate(real_estateDB.getNextId(), strToEType(type), address, size, price));
            cout << "✅ [Success]: Real Estate added with ID: " << real_estateDB.getNextId() - 1 << "!\n";
            break;
        }

        case 3:
        {
            int deleteId;
            getAllRE(real_estateDB);
            cout << "Real Estate to be deleted [ID]: ";
            deleteId = getValidInt();
            if (!assuringPrompt())
                break;
            if (real_estateDB.remove(deleteId))
                cout << "✅ [Success]: Real Estate with ID " << deleteId << " was deleted!\n";
            else
                cout << "❌ [Error]: Real Estate with ID " << deleteId << " not found.\n";
            break;
        }
        case 0:
            break;
        default:
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
            break;
        }
    } while (choice != 0);
}

void enterCitizenMenu(User *&currentUser, Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Citizen Menu ======================\n\n";
        cout << MAIN_CITIZEN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();

        switch (choice)
        {
        case 1:
        {
            printUserCard(*currentUser, vehiclesDB, real_estateDB);
            break;
        }
        case 2:
        {
            enterCitizenManageVehiclesMenu(currentUser, usersDB, vehiclesDB, real_estateDB);
            break;
        }
        case 3:
        {
            enterCitizenManageRealEstateMenu(currentUser, usersDB, vehiclesDB, real_estateDB);
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
        }
        }
    } while (choice != 0);
}

void enterCitizenManageVehiclesMenu(User *&currentUser, Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Manage Vehicles ======================\n\n";
        cout << VEHICLE_CITIZEN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();

        switch (choice)
        {
        case 1:
        {
            getVehiclesForSale(vehiclesDB);
            break;
        }
        case 2:
        {
            int vehicleId;
            if (!currentUser->showVehicles(vehiclesDB))
                break;
            cout << "Vehicle to be listed for sale [ID]: ";
            vehicleId = getValidInt();
            Vehicle *vptr = vehiclesDB.find([vehicleId](const Vehicle &v)
                                            { return vehicleId == v.getId(); });
            if (vptr)
            {
                for (auto &v : currentUser->getVehicles())
                {
                    if (v == vptr->getId())
                    {
                        if (vptr->getForSale())
                        {
                            cout << "❌ [Fail] Vehicle with ID [" << vptr->getId() << "] is already for sale!\n";
                            break;
                        }
                        cout << "Set the price: ";
                        int price;
                        price = getValidInt();
                        if (price < 0)
                        {
                            cerr << "\n\t⛔ Price cannot be negative!\n";
                            break;
                        }
                        if (!assuringPrompt())
                            break;
                        vptr->setPrice(price);
                        vptr->setForSale(true);
                        if (!vehiclesDB.save())
                        {
                            cout << "❌ [Fail] Vehicle with ID [" << vptr->getId() << "] failed to be put for sale!\n";
                            break;
                        }
                        cout << "✅ [Success] Vehicle with ID [" << vptr->getId() << "] is put for sale!\n";
                        break;
                    }
                }
            }
            else
                cout << "❌ [Fail] You don't own vehicle with ID [" << vehicleId << "]!\n";
            break;
        }
        case 3:
        {
            int vehicleId;
            if (!currentUser->showVehicles(vehiclesDB))
                break;
            cout << "Vehicle to be delisted from sale [ID]: ";
            vehicleId = getValidInt();
            Vehicle *vptr = vehiclesDB.find([vehicleId](const Vehicle &v)
                                            { return vehicleId == v.getId(); });
            if (vptr)
            {
                for (auto &v : currentUser->getVehicles())
                {
                    if (v == vptr->getId())
                    {
                        if (!vptr->getForSale())
                        {
                            cout << "❌ [Fail] Vehicle with ID [" << vptr->getId() << "] is not for sale!\n";
                            break;
                        }
                        if (!assuringPrompt())
                            break;
                        vptr->setForSale(false);
                        if (!vehiclesDB.save())
                        {
                            cout << "❌ [Fail] Vehicle with ID [" << vptr->getId() << "] failed to be delisted from sale!\n";
                            break;
                        }
                        cout << "✅ [Success] Vehicle with ID [" << vptr->getId() << "] is delisted from sale!\n";
                        break;
                    }
                }
            }
            else
                cout << "❌ [Fail] You don't own Vehicle with ID [" << vehicleId << "]!\n";
            break;
        }
        case 4:
        {
            if (getVehiclesForSale(vehiclesDB))
                buyVehicle(currentUser, usersDB, vehiclesDB);
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
        }
        }
    } while (choice != 0);
}
void enterCitizenManageRealEstateMenu(User *&currentUser, Database<User> &usersDB, Database<Vehicle> &vehiclesDB, Database<RealEstate> &real_estateDB)
{
    int choice;
    do
    {
        cout << "\n====================== Manage Real Estate ======================\n\n";
        cout << RE_CITIZEN_MENU;
        cout << "\nChoice: ";
        choice = getValidInt();
        usersDB.reload();
        vehiclesDB.reload();
        real_estateDB.reload();

        switch (choice)
        {
        case 1:
        {
            getRealEstateForSale(real_estateDB);
            break;
        }
        case 2:
        {
            int reId;
            if (!currentUser->showRealEstate(real_estateDB))
                break;
            cout << "Real Estate to be listed for sale [ID]: ";
            reId = getValidInt();
            RealEstate *reptr = real_estateDB.find([reId](const RealEstate &re)
                                                   { return reId == re.getId(); });
            if (reptr)
            {
                for (auto &re : currentUser->getRealEstates())
                {
                    if (re == reptr->getId())
                    {
                        if (reptr->getForSale())
                        {
                            cout << "❌ [Fail] Real Estate with ID [" << reptr->getId() << "] is already for sale!\n";
                            break;
                        }
                        cout << "Set the price: ";
                        int price;
                        price = getValidInt();
                        if (price < 0)
                        {
                            cerr << "\n\t⛔ Price cannot be negative!\n";
                            break;
                        }
                        if (!assuringPrompt())
                            break;
                        reptr->setPrice(price);
                        reptr->setForSale(true);
                        if (!real_estateDB.save())
                        {
                            cout << "❌ [Fail] Real Estate with ID [" << reptr->getId() << "] failed to be put for sale!\n";
                            break;
                        }
                        cout << "✅ [Success] Real Estate with ID [" << reptr->getId() << "] is put for sale!\n";
                        break;
                    }
                }
            }
            else
                cout << "❌[Fail] You don't own Real Estate with ID [" << reId << "]!\n";
            break;
        }
        case 3:
        {
            int reId;
            if (!currentUser->showRealEstate(real_estateDB))
                break;
            cout << "Real Estate to be delisted from sale [ID]: ";
            reId = getValidInt();
            RealEstate *reptr = real_estateDB.find([reId](const RealEstate &re)
                                                   { return reId == re.getId(); });
            if (reptr)
            {
                for (auto &re : currentUser->getRealEstates())
                {
                    if (re == reptr->getId())
                    {
                        if (!reptr->getForSale())
                        {
                            cout << "❌ [Fail] Real Estate with ID [" << reptr->getId() << "] is not for sale!\n";
                            break;
                        }
                        if (!assuringPrompt())
                            break;
                        reptr->setForSale(false);
                        if (!real_estateDB.save())
                        {
                            cout << "❌ [Fail] Real Estate with ID [" << reptr->getId() << "] failed to be delisted from sale!\n";
                            break;
                        }
                        cout << "✅ [Success] Real Estate with ID [" << reptr->getId() << "] delisted from sale!\n";
                        break;
                    }
                }
            }
            else
                cout << "❌ [Fail] You don't own Real Estate with ID [" << reId << "]!\n";
            break;
        }
        case 4:
        {
            if (getRealEstateForSale(real_estateDB))
                buyRealEstate(currentUser, usersDB, real_estateDB);
            break;
        }
        case 0:
        {
            break;
        }
        default:
        {
            cerr << "\n\t⛔ Invalid command!\n";
            choice = -1;
        }
        }
    } while (choice != 0);
}
