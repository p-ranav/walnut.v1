cmake_minimum_required(VERSION 3.6)
project(CARBON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

MACRO(ADD_SUBLIBRARY LIBRARY_NAME)
  #Compute required sources
  file(GLOB SUBLIBRARY_SOURCES 
    "src/${LIBRARY_NAME}/*.c" 
    "src/${LIBRARY_NAME}/*.h")

  #Create library
  ADD_LIBRARY(${LIBRARY_NAME} STATIC ${SUBLIBRARY_SOURCES})

  #add this library's header folder to the global include set
  INCLUDE_DIRECTORIES("src/${LIBRARY_NAME}")

ENDMACRO(ADD_SUBLIBRARY)

ADD_SUBLIBRARY(LEXER)
set_target_properties(LEXER PROPERTIES OUTPUT_NAME lexer) # lexer.lib
set_property(TARGET LEXER PROPERTY C_STANDARD 90)

file(GLOB EXECUTABLE_SOURCES 
    "src/main.c" 
)
ADD_EXECUTABLE(CARBON ${EXECUTABLE_SOURCES})
set_target_properties(CARBON PROPERTIES OUTPUT_NAME carbon) # carbon.exe
set_property(TARGET CARBON PROPERTY C_STANDARD 90)

#Link any of the created libraries
TARGET_LINK_LIBRARIES(CARBON LEXER)

# Set CARBON as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CARBON)
