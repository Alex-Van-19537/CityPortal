cmake_minimum_required(VERSION 3.10)
project(CityPortal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main
main.cpp
src/entry.cpp
src/user.cpp
src/vehicle.cpp
src/real_estate.cpp
)
