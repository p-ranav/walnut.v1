cmake_minimum_required(VERSION 3.6)
project(WALNUT)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Disable deprecation for windows
if (WIN32)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# LEXER library
file(GLOB LEXER_SOURCES 
  "src/lexer/*.cpp" 
  "src/lexer/*.hpp"
  "src/lexer/token/*.hpp"
  "src/lexer/token/*.cpp"
  "src/lexer/utils/*.hpp"
  "src/lexer/utils/*.cpp"
  )
ADD_LIBRARY(LEXER STATIC ${LEXER_SOURCES})
INCLUDE_DIRECTORIES("src/lexer" "src/lexer/token" "src/lexer/utils")
set_target_properties(LEXER PROPERTIES OUTPUT_NAME lexer) # lexer.lib
TARGET_LINK_LIBRARIES(LEXER)

# PARSER library
file(GLOB PARSER_SOURCES 
  "src/parser/*.cpp" 
  "src/parser/*.hpp"
  "src/parser/ast/*.hpp"
  )
ADD_LIBRARY(PARSER STATIC ${PARSER_SOURCES})
INCLUDE_DIRECTORIES("src/parser" "src/parser/ast")
set_target_properties(PARSER PROPERTIES OUTPUT_NAME parser) # parser.lib
TARGET_LINK_LIBRARIES(PARSER LEXER) 

# EVALUATOR library
file(GLOB EVALUATOR_SOURCES 
  "src/evaluator/*.cpp" 
  "src/evaluator/*.hpp"
  "src/evaluator/builtin/*.cpp"
  "src/evaluator/object/*.cpp"
  "src/evaluator/object/*.hpp")
ADD_LIBRARY(EVALUATOR STATIC ${EVALUATOR_SOURCES})
INCLUDE_DIRECTORIES("src/evaluator" "src/evaluator/object")
set_target_properties(EVALUATOR PROPERTIES OUTPUT_NAME evaluator) # evaluator.lib
TARGET_LINK_LIBRARIES(EVALUATOR PARSER)
set_property(TARGET EVALUATOR PROPERTY CXX_STANDARD 17)
if (UNIX)
TARGET_LINK_LIBRARIES(EVALUATOR PARSER stdc++fs)
endif()

# Main executable
file(GLOB EXECUTABLE_SOURCES 
    "src/main.cpp" 
)
ADD_EXECUTABLE(WALNUT ${EXECUTABLE_SOURCES})
set_target_properties(WALNUT PROPERTIES OUTPUT_NAME walnut)

#Link any of the created libraries
TARGET_LINK_LIBRARIES(WALNUT LEXER PARSER EVALUATOR)

# Set ${PROJECT_NAME} as the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT WALNUT)
set_property(TARGET WALNUT PROPERTY CXX_STANDARD 17)

# Tests
file(GLOB TESTS_SOURCES 
    "tests/*.cpp" 
    "tests/*.hpp"
)
INCLUDE_DIRECTORIES("tests")
ADD_EXECUTABLE(TESTS ${TESTS_SOURCES})
set_target_properties(TESTS PROPERTIES OUTPUT_NAME tests) # tests.exe
TARGET_LINK_LIBRARIES(TESTS LEXER PARSER EVALUATOR)

# make check - runs unit tests
if (UNIX)
add_custom_target(check COMMAND ./tests)
endif(UNIX)