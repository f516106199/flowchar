cmake_minimum_required(VERSION 3.15)

project(flowchar)

add_executable(flowchar src/box.cc src/charEmitter.cc src/main.cc src/token.cc src/tree.cc src/CodePaser.cc)

target_include_directories(flowchar PRIVATE ${PROJECT_SOURCE_DIR}/include)


