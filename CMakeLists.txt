cmake_minimum_required(VERSION 3.19)
project(ping_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)
find_package(Boost)

qt_standard_project_setup()

qt_add_executable(start
    main.cpp
    config.h config.cpp

    target.h
    client.h client.cpp
)

target_link_libraries(start
    PRIVATE
        Qt::Core
        Boost::boost
)

include(GNUInstallDirs)

install(TARGETS start
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
