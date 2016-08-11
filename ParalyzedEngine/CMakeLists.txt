cmake_minimum_required (VERSION 2.6)
project (ParalyzedEngine)
 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(CMAKE_BUILD_TYPE Release)

include_directories(${GLIB_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(  ${OPENSSL_LIBRARIES} ${GL_LIBRARY} ${GLIB_LIBRARIES}  GLU   )

add_library(ParalyzedEngine STATIC ParalyzedEngine.c ParalyzedEngineWindow.c ParalyzedEngineSpriteRenderer.c JSON/JSONParser.cpp PEDictionary.cpp Network/WebClient.c Shaders/ShaderProgram.c)



