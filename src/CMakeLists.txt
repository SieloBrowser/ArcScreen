cmake_minimum_required(VERSION 3.6)
project(arcscreen-plugin)

# user config config file
include("${CMAKE_SOURCE_DIR}/user-config.cmake")

include_directories(${SIELO_DIR}/Core)
include_directories(${CMAKE_SOURCE_DIR}/includes)

link_directories(${SIELO_LIBS_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(
    GLOB_RECURSE
    SOURCE_FILES
    includes/*.hpp
    sources/*.cpp
    skin/*
)

file(
	GLOB_RECURSE
	QRC_FILES
	*.qrc
)

find_package(Qt5Widgets 5.11.2 REQUIRED)
find_package(Qt5WebEngine 5.11.2 REQUIRED)
find_package(Qt5Sql 5.11.2 REQUIRED)
find_package(Qt5WebEngineWidgets 5.11.2 REQUIRED)

set(SIELO_LIBS Core Qt5::Widgets Qt5::WebEngine Qt5::Sql Qt5::WebEngineWidgets)

add_library(arcscreen-plugin MODULE ${SOURCE_FILES} ${QRC_FILES})

target_link_libraries(arcscreen-plugin PRIVATE ${SIELO_LIBS})