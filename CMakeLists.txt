cmake_minimum_required(VERSION 3.23)
project(boost_fmt)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
find_package(Boost REQUIRED system)

add_subdirectory(test)
