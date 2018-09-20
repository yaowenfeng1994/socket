cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(socket)

set(CMAKE_CXX_STANDARD 17)

include_directories(unix)

# unix
link_libraries(curses)
#add_executable(socket main.cpp unix/server.cpp unix/client.cpp unix/graphics.cpp
#        unix/select_poll/server.cpp unix/select_poll/client.cpp)
#add_executable(socket main.cpp unix/select_poll/server.cpp unix/select_poll/client.cpp)
add_executable(socket main.cpp unix/syn_attack.cpp)


# window
#link_libraries(wsock32)
#add_executable(socket2 main.cpp window/server.cpp window/client.cpp)
