cmake_minimum_required(VERSION 3.14)
project(leetcode LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_CXX_FLAGS_DEBUG_INIT "-std=c++14 -g -fno-omit-frame-pointer")
# set(CMAKE_CXX_FLAGS_RELEASE_INIT "-std=c++14 -g -O2")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_subdirectory(easy/src)

# CTest related
enable_testing()
add_subdirectory(easy/tests)