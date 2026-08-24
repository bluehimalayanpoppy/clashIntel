cmake_minimum_required(VERSION 3.16)

project(clashIntel)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(clashintel
    src/main.cpp
    src/MainWindow.cpp

    src/Battle.cpp
    src/BattleParser.cpp

    src/Player.cpp
    src/PlayerParser.cpp
    src/CsvExporter.cpp
    src/CsvReader.cpp

    src/Card.cpp
    src/CardParser.cpp
    src/Analyzer.cpp
)

target_include_directories(clashintel PRIVATE include)

target_link_libraries(clashintel PRIVATE
    CURL::libcurl
    Qt6::Widgets
    nlohmann_json::nlohmann_json
)

add_executable(CardParserTest
    tests/CardParserTest.cpp
    src/CardParser.cpp
)

target_include_directories(CardParserTest PRIVATE include)

target_link_libraries(CardParserTest PRIVATE
    nlohmann_json::nlohmann_json
)

add_executable(AnalyzerTest
    tests/AnalyzerTest.cpp
    src/Analyzer.cpp
    src/Battle.cpp
    src/BattleParser.cpp
    src/Card.cpp
    src/CsvReader.cpp
    src/CardParser.cpp
)

target_include_directories(AnalyzerTest PRIVATE include)

target_link_libraries(AnalyzerTest PRIVATE
    CURL::libcurl
    nlohmann_json::nlohmann_json
)