cmake_minimum_required(VERSION 3.10)
project(CityPortal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Export compile_commands.json so VS Code can index all symbols and headers
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

add_executable(CityPortal
    main.cpp
    src/entry.cpp
    src/user.cpp
    src/user_service.cpp
    src/vehicle.cpp
    src/vehicle_service.cpp
    src/real_estate.cpp
    src/real_estate_service.cpp
    src/menu.cpp
    src/app.cpp
)

# 2. Modern target-scoped include directory (better than global include_directories)
target_include_directories(CityPortal PRIVATE include)