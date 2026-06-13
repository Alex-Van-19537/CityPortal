cmake_minimum_required(VERSION 3.10)
project(CityPortal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT>
        $<$<CONFIG:Debug>:/MTd>
        $<$<CONFIG:Release>:/MT>
    )
endif()

include_directories(include)

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
