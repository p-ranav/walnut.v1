cmake_minimum_required(VERSION 3.6)
project(CARBON)

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

# AST library
ADD_SUBLIBRARY(AST src/ast)
set_target_properties(AST PROPERTIES OUTPUT_NAME ast) # ast.lib
set_target_properties(AST PROPERTIES LINKER_LANGUAGE CXX)

# Lexer library
ADD_SUBLIBRARY(LEXER src/lexer)
set_target_properties(LEXER PROPERTIES OUTPUT_NAME lexer) # lexer.lib
TARGET_LINK_LIBRARIES(LEXER UTF8 AST)

# Parser library
ADD_SUBLIBRARY(PARSER src/parser)
set_target_properties(PARSER PROPERTIES OUTPUT_NAME parser) # parser.lib
TARGET_LINK_LIBRARIES(PARSER LEXER AST) 

# MODEL library
ADD_SUBLIBRARY(MODEL src/model)
set_target_properties(MODEL PROPERTIES OUTPUT_NAME model) # model.lib
set_target_properties(MODEL PROPERTIES LINKER_LANGUAGE CXX)

# EVALUATOR library
ADD_SUBLIBRARY(EVALUATOR src/evaluator)
set_target_properties(EVALUATOR PROPERTIES OUTPUT_NAME evaluator) # evaluator.lib
TARGET_LINK_LIBRARIES(EVALUATOR PARSER MODEL) 

# Main executable
file(GLOB EXECUTABLE_SOURCES 
    "src/main.cpp" 
)
ADD_EXECUTABLE(CARBON ${EXECUTABLE_SOURCES})
set_target_properties(CARBON PROPERTIES OUTPUT_NAME carbon)

#Link any of the created libraries
TARGET_LINK_LIBRARIES(CARBON UTF8 LEXER PARSER EVALUATOR MODEL)

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CARBON)
set_property(TARGET CARBON PROPERTY CXX_STANDARD 11)

# Tests
file(GLOB TESTS_SOURCES 
    "tests/*.cpp" 
    "tests/*.hpp"
)
INCLUDE_DIRECTORIES("tests")
ADD_EXECUTABLE(TESTS ${TESTS_SOURCES})
set_target_properties(TESTS PROPERTIES OUTPUT_NAME tests) # tests.exe
TARGET_LINK_LIBRARIES(TESTS UTF8 LEXER PARSER EVALUATOR)

# make check - runs unit tests
if (UNIX)
add_custom_target(check COMMAND ./tests)
endif(UNIX)