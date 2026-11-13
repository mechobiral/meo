cmake_minimum_required(VERSION 3.16)

project(meo LANGUAGES CXX)

add_executable(meo
  src/main.cpp
  src/cli/ArgParser.cpp
  src/common/Metadata.cpp
  src/core/Lexer.cpp
  src/core/Parser.cpp
  src/core/Token.cpp
)

target_include_directories(meo PRIVATE include)
target_compile_features(meo PRIVATE cxx_std_20)