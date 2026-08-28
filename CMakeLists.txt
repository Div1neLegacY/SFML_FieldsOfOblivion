cmake_minimum_required(VERSION 3.28)
project(FieldsOfOblivion LANGUAGES CXX)

# Build Debug symbols
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-O0 -g)
endif()
if(MSVC)
    add_compile_options(/Zi)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# @todo Needed for DLL, but why?
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add DLL library for shared game logic
add_library(game_logic SHARED
    src/GameDll.cpp
)
target_compile_features(game_logic PRIVATE cxx_std_17)
target_link_libraries(game_logic PRIVATE SFML::Graphics)

# When new source files are created, add here
add_executable(main
    src/Main.cpp
    src/Game.cpp
    src/Player.cpp
)
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
