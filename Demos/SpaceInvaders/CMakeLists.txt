cmake_minimum_required (VERSION 2.6)
project (SpaceInvaders)
 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
find_package(PkgConfig REQUIRED)

set(CMAKE_BUILD_TYPE Release)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../ParalyzedEngine/)
LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../ParalyzedEngine/build/)
add_executable(SpaceInvaders main.cpp)
TARGET_LINK_LIBRARIES(SpaceInvaders ParalyzedEngine X11 GL GLU )





