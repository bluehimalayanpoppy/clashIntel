cmake_minimum_required(VERSION 3.15)
project(clashIntel CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(clashintel
    src/main.cpp
    src/Battle.cpp
    src/BattleParser.cpp
)

target_link_libraries(clashintel PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)

target_include_directories(clashintel PRIVATE include)