cmake_minimum_required(VERSION 3.10)  
  
project(MySERVER)  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  
  

add_executable(myserver server.cpp)
add_executable(myclient client.cpp)