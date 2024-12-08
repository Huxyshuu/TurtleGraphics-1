cmake_minimum_required(VERSION "3.19.2")

project(turtle-1 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets) # This line requires QtCreator IDE to work. VSCode won't find it unless the Qt6 path is explicitly specified


file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp") # Includes all .cpp files from the src folder into the project
add_executable(
    turtle-1
    ${MY_SOURCES}
    resources.qrc
)

target_link_libraries(turtle-1 PRIVATE Qt6::Widgets)

set_target_properties(turtle-1 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)

include(GNUInstallDirs)
