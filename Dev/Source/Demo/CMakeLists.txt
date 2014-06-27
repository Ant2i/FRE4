cmake_minimum_required(VERSION 2.8.8)

set(CMAKE_PREFIX_PATH $ENV{QTDIR})
#set(CMAKE_LIBRARY_PATH "C:\\Program Files (x86)\\Windows Kits\\8.0\\Lib\\win8\\um\\x64")

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
find_package(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)

file(GLOB HEADER_FILES *.h)
file(GLOB SOURCE_FILES *.cpp)

include_directories(${FRE_DEV_DIRS})

add_executable(Demo ${HEADER_FILES} ${SOURCE_FILES})

qt5_use_modules(Demo Widgets)

target_link_libraries(Demo ${ENGINE_NAME})

