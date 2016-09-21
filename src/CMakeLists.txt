cmake_minimum_required(VERSION 3.5)
project(decision_tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cc Data.cc Data.h TreeNode.cc TreeNode.h DecisionTree.cc DecisionTree.h)
add_executable(decision_tree ${SOURCE_FILES})