cmake_minimum_required(VERSION 3.10)
project(simakov_game)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

find_package(BearLibTerminal REQUIRED)
include_directories(SYSTEM ${BLT_INCLUDE_DIRS})

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)


add_executable(simakov_game ${HEADERS} ${SOURCES})

include_directories(${PROJECT_HEADERS_DIR})

target_link_libraries(${PROJECT_NAME} ${BLT_LIBRARIES})

file(COPY ${BLT_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add linting before compilation
include(CppLint)
ADD_STYLE_CHECK_TARGET(lint ${PROJECT_NAME} ${PROJECT_HEADERS_DIR} ${PROJECT_SOURCES_DIR})
add_dependencies(${PROJECT_NAME} lint)
