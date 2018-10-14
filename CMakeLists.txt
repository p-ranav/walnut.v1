cmake_minimum_required(VERSION 3.6)
set(PROJECT_NAME ULANG)
set(PROJECT_NAME_LOWERCASE ulang)
project(${PROJECT_NAME})

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

MACRO(ADD_SUBLIBRARY LIBRARY_NAME RELATIVE_PATH)
  #Compute required sources
  file(GLOB SUBLIBRARY_SOURCES 
    "${RELATIVE_PATH}/*.cpp" 
    "${RELATIVE_PATH}/*.hpp")

  #Create library
  ADD_LIBRARY(${LIBRARY_NAME} STATIC ${SUBLIBRARY_SOURCES})

  #add this library's header folder to the global include set
  INCLUDE_DIRECTORIES("${RELATIVE_PATH}")

ENDMACRO(ADD_SUBLIBRARY)

# Disable deprecation for windows
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Utilities library
ADD_SUBLIBRARY(UTF8 src/utf8)
set_target_properties(UTF8 PROPERTIES OUTPUT_NAME utf8) # utf8.lib

# Lexer library
ADD_SUBLIBRARY(LEXER src/lexer)
set_target_properties(LEXER PROPERTIES OUTPUT_NAME lexer) # lexer.lib
TARGET_LINK_LIBRARIES(LEXER UTF8)

# Main executable
file(GLOB EXECUTABLE_SOURCES 
    "src/main.cpp" 
)
ADD_EXECUTABLE(${PROJECT_NAME} ${EXECUTABLE_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME_LOWERCASE})

#Link any of the created libraries
TARGET_LINK_LIBRARIES(${PROJECT_NAME} UTF8 LEXER)

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})