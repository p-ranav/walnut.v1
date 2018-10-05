cmake_minimum_required(VERSION 3.6)
project(CARBON)

if (UNIX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c89 -pedantic")
endif(UNIX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

MACRO(ADD_SUBLIBRARY LIBRARY_NAME RELATIVE_PATH)
  #Compute required sources
  file(GLOB SUBLIBRARY_SOURCES 
    "${RELATIVE_PATH}/*.c" 
    "${RELATIVE_PATH}/*.h")

  #Create library
  ADD_LIBRARY(${LIBRARY_NAME} STATIC ${SUBLIBRARY_SOURCES})

  #add this library's header folder to the global include set
  INCLUDE_DIRECTORIES("${RELATIVE_PATH}")

ENDMACRO(ADD_SUBLIBRARY)

# Disable deprecation for windows
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

ADD_SUBLIBRARY(UTILS src/utils)
set_target_properties(UTILS PROPERTIES OUTPUT_NAME utils) # utils.lib

ADD_SUBLIBRARY(LEXER src/lexer)
set_target_properties(LEXER PROPERTIES OUTPUT_NAME lexer) # lexer.lib

TARGET_LINK_LIBRARIES(LEXER UTILS)

ADD_SUBLIBRARY(PARSER src/parser)
set_target_properties(PARSER PROPERTIES OUTPUT_NAME parser) # parser.lib

TARGET_LINK_LIBRARIES(PARSER LEXER UTILS)

file(GLOB EXECUTABLE_SOURCES 
    "src/main.c" 
)
ADD_EXECUTABLE(CARBON ${EXECUTABLE_SOURCES})
set_target_properties(CARBON PROPERTIES OUTPUT_NAME carbon) # carbon.exe

#Link any of the created libraries
TARGET_LINK_LIBRARIES(CARBON UTILS LEXER PARSER)

# Set CARBON as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CARBON)
