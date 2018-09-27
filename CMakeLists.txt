cmake_minimum_required(VERSION 3.6)
project(CARBON)

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
  INCLUDE_DIRECTORIES("src/${LIBRARY_NAME}")

ENDMACRO(ADD_SUBLIBRARY)

# Disable deprecation for windows
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

ADD_SUBLIBRARY(UTILS src/utils)
set_target_properties(UTILS PROPERTIES OUTPUT_NAME utils) # utils.lib
set_property(TARGET UTILS PROPERTY C_STANDARD 90)

ADD_SUBLIBRARY(LEXER src/lexer)
set_target_properties(LEXER PROPERTIES OUTPUT_NAME lexer) # lexer.lib
set_property(TARGET LEXER PROPERTY C_STANDARD 90)

file(GLOB EXECUTABLE_SOURCES 
    "src/main.c" 
)
ADD_EXECUTABLE(CARBON ${EXECUTABLE_SOURCES})
set_target_properties(CARBON PROPERTIES OUTPUT_NAME carbon) # carbon.exe
set_property(TARGET CARBON PROPERTY C_STANDARD 90)

#Link any of the created libraries
TARGET_LINK_LIBRARIES(CARBON UTILS LEXER)

# Set CARBON as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CARBON)
