cmake_minimum_required(VERSION 3.23)
project(DA_PROJ2)

set(CMAKE_CXX_STANDARD 14)


add_executable(DA_PROJ2 main.cpp ReadFiles.cpp ReadFiles.h VertexEdge.cpp VertexEdge.h Graph.h Graph.cpp ManageNetwork.h ManageNetwork.cpp MutablePriorityQueue.h menu.h menu.cpp)

