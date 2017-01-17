cmake_minimum_required (VERSION 2.6)
project (ParalyzedEngine)
 #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(CMAKE_BUILD_TYPE Release)

SET(SOIL_NAMES SOIL Soil soil)
FIND_LIBRARY(SOIL_LIBRARY NAMES ${SOIL_NAMES}  REQUIRED)
MARK_AS_ADVANCED( SOIL_LIBRARY SOIL_INCLUDE_DIR )
SET(SOIL_INCLUDE_DIRS "${SOIL_INCLUDE_DIR}")
SET(SOIL_LIBRARIES "${SOIL_LIBRARY}")

find_package(Freetype REQUIRED)
find_package(Lua REQUIRED)

include_directories(${GLIB_INCLUDE_DIR} ${LUA_INCLUDE_DIRS} ${FREETYPE_INCLUDE_DIRS} ${GLIBCONFIG_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(ParalyzedEngine STATIC ParalyzedEngine.c Window.c SpriteRenderer.c  Network/WebClient.c Network/TCPClient.c Shaders/ShaderProgram.c  Texture.c TextRenderer.c PEDictionary.cpp JSON/JSONParser.cpp Map/Map.cpp Model.cpp Memory/PEalloc/PEalloc.cpp GameObjects/PEProp.cpp)

target_link_libraries(ParalyzedEngine  ${FREETYPE_LIBRARY} ${LUA_LIBRARY} ${SOIL_LIBRARY} ${OPENSSL_LIBRARIES} ${GL_LIBRARY} ${GLIB_LIBRARIES}    X11 GL GLU  )


