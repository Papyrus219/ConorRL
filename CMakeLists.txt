cmake_minimum_required(VERSION 3.22)
project(ConorRL)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON)

FetchContent_MakeAvailable(SFML nlohmann_json)

file(GLOB_RECURSE SRC src/*cpp)
set(SOURCES ${SRC})

add_executable(ConorRL ${SOURCES})
target_link_libraries(ConorRL PRIVATE SFML::Graphics SFML::Audio nlohmann_json::nlohmann_json)
