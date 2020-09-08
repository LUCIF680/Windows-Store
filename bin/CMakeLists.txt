cmake_minimum_required(VERSION 3.5)

project(Appx LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS REQUIRED
    Widgets MultimediaWidgets)

set(HEADER
    util.hpp
    videoplayer.hpp
    connection.hpp
    application.hpp
    session.hpp
    easycpp/aes.hpp)
SET(FORM
    dialog.ui
    home_page.ui
    login.ui)
add_executable(Appx
  main.cpp
  ${HEADER}
  ${FORM}
)
target_include_directories(Appx PRIVATE easycpp)
target_link_libraries(Appx PRIVATE
    Qt5::Widgets Qt5Network
    Qt5::MultimediaWidgets
    pthread  mysqlcppconn bcrypt ssl crypto )
