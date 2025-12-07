cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Create an option to switch between a system sdl library and a vendored SDL library
option(MYGAME_VENDORED "Use vendored libraries" OFF)

if(MYGAME_VENDORED)
    # This assumes you have added SDL as a submodule in vendored/SDL
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

if(MYGAME_VENDORED)
        # This assumes the SDL source is available in vendored/SDL
        add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
        # This assumes the SDL_image source is available in vendored/SDL_image
        add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)
else()
        # CONFIG REQUIRED COMPONENTS SDL3-shared
        find_package(SDL3_image REQUIRED)
endif()

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

#SET(CMAKE_BUILD_TYPE "Debug")

include_directories(include/)

set(UNITTEST ON)

if(UNITTEST)
find_package(GTest REQUIRED)
add_executable(main
        src/testmain.cpp
        src/unit_test.cpp
        src/ServiceLocator.cpp
        src/Timer.cpp
        src/Entity.cpp
        src/Event.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
        SDL3_image::SDL3_image
        SDL3::SDL3
)
else()

add_executable(main
        src/main.cpp
        src/ServiceLocator.cpp
        src/Timer.cpp
        src/Entity.cpp
        src/Event.cpp
)
target_link_libraries(main
        SDL3_image::SDL3_image
        SDL3::SDL3
)
endif()