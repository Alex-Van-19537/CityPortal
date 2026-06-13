#include "app.hpp"

App::App() : isRunning(false), currentUser(nullptr) {}

App::~App() {}

fs::path App::getExecutableDir()
{
#ifdef __linux__
    // 1. Кодът за Linux
    return fs::read_symlink("/proc/self/exe").parent_path();

#elif defined(__APPLE__)
    // 2. Кодът за macOS
    char path[1024];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0)
    {
        return fs::path(path).parent_path();
    }
    return fs::current_path(); // Резервен вариант, ако нещо се обърка

#elif defined(_WIN32)
    // 3. Кодът за Windows
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return fs::path(path).parent_path();

#else
    // 4. За непознати операционни системи връщаме текущата директория
    return fs::current_path();
#endif
}

bool App::init()
{
    fs::path data_dir = getExecutableDir() / "data";
    if (!fs::exists(data_dir))
    {
        if (!fs::create_directory(data_dir))
            return false;
    }
    string usersFile = (data_dir / "users.csv").string();
    string vehiclesFile = (data_dir / "vehicles.csv").string();
    string real_estateFile = (data_dir / "real_estate.csv").string();
    if (!usersDB.load(usersFile) || !vehiclesDB.load(vehiclesFile) || !real_estateDB.load(real_estateFile))
        return false;
    if (usersDB.empty())
    {
        User admin = User(1, "Admin", "", "admin", "admin", 0);
        admin.setRole(Role::ADMIN);
        usersDB.add(admin);
    }
    isRunning = true;
    return true;
}

void App::run()
{
    while (isRunning)
    {
        if (!currentUser)
        {
            if (!enterLogInMenu(currentUser, usersDB, vehiclesDB, real_estateDB))
            {
                isRunning = false;
                continue;
            }
        }

        if (currentUser->getRole() == Role::ADMIN)
        {
            enterAdminMenu(usersDB, vehiclesDB, real_estateDB);
        }

        else if (currentUser->getRole() == Role::CITIZEN)
        {
            enterCitizenMenu(currentUser, usersDB, vehiclesDB, real_estateDB);
        }
        cout << "🥲 See you the next time " << currentUser->getUsername() << "!\n";
        currentUser = nullptr;
    }
}
