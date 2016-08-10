cmake_minimum_required (VERSION 2.6)
project (ParalyzedEngine)
 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
find_package(PkgConfig REQUIRED)

set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(ParalyzedEngine STATIC ParalyzedEngine.c ParalyzedEngineWindow.c)




