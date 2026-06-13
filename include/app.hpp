#include "menu.hpp"

class App {
    public:
    App();
    ~App();

    bool init();
    void run();

    private:
    const string usersFile = "data/users.csv";
    const string vehiclesFile = "data/vehicles.csv";
    const string real_estateFile = "data/real_estate.csv";

    Database<User> usersDB;
    Database<Vehicle> vehiclesDB;
    Database<RealEstate> real_estateDB;

    User* currentUser;
    bool isRunning;
};