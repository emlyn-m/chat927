cmake_minimum_required(VERSION 3.10)
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# set the project name
project(Chat927)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

# add the executable
add_executable(Chat927 main.cpp instagram.cpp)
target_link_libraries(Chat927 PRIVATE m)
target_link_libraries(Chat927 PRIVATE cpr::cpr)

