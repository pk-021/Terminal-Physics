cmake_minimum_required(VERSION 3.10)
project(TerminalGame)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Shape.cpp
    src/utils.cpp
    src/Window.cpp
    src/GameLoop.cpp
    src/Object.cpp
    src/TVector.cpp
    # src/gameElements.cpp
)

# Create the executable
add_executable(TerminalGame ${SOURCES})

# FetchContent module is available since CMake 3.11
# include(FetchContent)

# Download and configure Google Test
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
# )

# For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Fetch the content
# FetchContent_MakeAvailable(googletest)

# Add test executable
# set(TEST_SOURCES
#   src/shape.cpp
#   src/utils.cpp
#   src/Window.cpp
#   src/gameLoop.cpp
#   src/gameElements.cpp
#   tests/test_shape.cpp
# )

# Create the test executable
# add_executable(ctest ${TEST_SOURCES})

# Link Google Test and your project libraries
# target_link_libraries(ctest gtest_main)

# Link the project library if there are any common libraries (assuming TerminalGame as a library)
# target_link_libraries(tests TerminalGame)

# Enable testing
# enable_testing()

# Discover and run tests
# include(GoogleTest)
# gtest_discover_tests(ctest)
