cmake_minimum_required(VERSION 3.10.2)
project(code)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g")
include_directories(
        ${PROJECT_SOURCE_DIR}/generated/
        ${PROJECT_SOURCE_DIR}/third_party/
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src
        ${PROJECT_SOURCE_DIR}/src/
        ${PROJECT_SOURCE_DIR}/src/Integer
        ${PROJECT_SOURCE_DIR}/src/Polynomial
        ${PROJECT_SOURCE_DIR}/src/Dynamic_Type
        ${PROJECT_SOURCE_DIR}/src/Name_Space
)
set(src_dir
        ${PROJECT_SOURCE_DIR}/generated/Python3Lexer.cpp
        ${PROJECT_SOURCE_DIR}/generated/Python3Parser.cpp
        ${PROJECT_SOURCE_DIR}/generated/Python3Listener.cpp
        ${PROJECT_SOURCE_DIR}/generated/Python3BaseListener.cpp
        src/Evalvisitor.h src/Evalvisitor.cpp
        src/Integer/Integer.cpp src/Integer/Integer.h src/Polynomial/Polynomial.cpp src/Polynomial/Polynomial.h src/Dynamic_Type/Dynamic_Type.cpp src/Dynamic_Type/Dynamic_Type.h src/Name_Space/Name_Space.cpp src/Name_Space/Name_Space.h)
file(GLOB antlr4-cpp-src
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/atn/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/dfa/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/misc/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/support/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/tree/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/tree/pattern/*.cpp
        ${PROJECT_SOURCE_DIR}/third_party/runtime/src/tree/xpath/*.cpp
        )
add_library (antlr4-cpp-runtime ${antlr4-cpp-src})
add_executable(code ${src_dir} src/main.cpp)
target_link_libraries(code antlr4-cpp-runtime)
