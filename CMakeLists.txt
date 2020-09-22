cmake_minimum_required (VERSION 2.8.11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(nlohmann_json 3.9.1 REQUIRED)

project (exchange)

include_directories(include)
add_subdirectory(src)