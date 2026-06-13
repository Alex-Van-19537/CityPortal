#include "menu.hpp"
#include <filesystem>

#ifdef __linux__
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

namespace fs = std::filesystem;

class App {
    public:
    App();
    ~App();

    bool init();
    void run();

    private:
    fs::path getExecutableDir();

    Database<User> usersDB;
    Database<Vehicle> vehiclesDB;
    Database<RealEstate> real_estateDB;

    User* currentUser;
    bool isRunning;
};