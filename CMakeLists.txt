cmake_minimum_required(VERSION 3.23)
project(Double_Pendulum_Sim)

set(CMAKE_CXX_STANDARD 20)

# Compiler Commands JSON
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

# Set Raylib
find_package(raylib 4.2.0 QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
    )
    FetchContent_GetProperties(raylib)

    if(NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()



# Set Boost Libraries
message(STATUS "generating boost libraries")

find_package(Boost 1.79.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

endif()

add_executable(Double_Pendulum_Sim main.cpp includes/pendulum.h pendulum.cpp)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if(Boost_FOUND)

    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif()