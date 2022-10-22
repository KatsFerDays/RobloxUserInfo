cmake_minimum_required(VERSION 3.24.0)
set(CMAKE_CXX_STANDARD 20)
project(RobloxUserInfo)

include(${CMAKE_SOURCE_DIR}/conan/conan_paths.cmake)

find_package(nlohmann_json 3.11.2 REQUIRED)
find_package(cpr 1.9.0 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json cpr::cpr)