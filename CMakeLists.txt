cmake_minimum_required(VERSION 3.19)
project(ping_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost)
find_package(nlohmann_json 3.12.0 REQUIRED)

add_executable(start
    main.cpp
    config.h config.cpp

    target.h
    client.h client.cpp
    timer.h timer.cpp
)

target_link_libraries(start
    PRIVATE
        Boost::boost
        nlohmann_json::nlohmann_json
)

