cmake_minimum_required(VERSION 3.12)
project(socket)

set(CMAKE_CXX_STANDARD 17)
link_libraries(curses)
add_executable(socket main.cpp unix/server.cpp unix/client.cpp unix/graphics.cpp)
