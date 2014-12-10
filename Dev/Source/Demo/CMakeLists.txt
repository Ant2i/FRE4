CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)


SET(QT5_PATH "/Users/Anton/Qt/5.3/clang_64/" CACHE PATH "Path to Qt5")
SET(QT5_MODULE_PATH ${QT5_PATH}/lib/cmake)
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT5_MODULE_PATH})

#SET(CMAKE_PREFIX_PATH "/Users/Anton/Qt/5.3")
#SET(CMAKE_PREFIX_PATH $ENV{QTDIR})

# Tell CMake to run moc when necessary:
SET(CMAKE_AUTOMOC ON)
# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Widgets finds its own dependencies.
FIND_PACKAGE(Qt5Core REQUIRED)
#find_package(Qt5Widgets REQUIRED)

FILE(GLOB HEADER_FILES *.h)
FILE(GLOB SOURCE_FILES *.cpp)

INCLUDE_DIRECTORIES(${FRE_DEV_DIRS})

ADD_EXECUTABLE(Demo ${HEADER_FILES} ${SOURCE_FILES})

qt5_use_modules(Demo Widgets)

TARGET_LINK_LIBRARIES(Demo ${ENGINE_NAME})

