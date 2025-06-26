cmake_minimum_required(VERSION 3.10)

project(list_threads VERSION 1.0)

add_executable(${PROJECT_NAME} main.cpp list.h list.cpp)

if(UNIX)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
endif(UNIX)
