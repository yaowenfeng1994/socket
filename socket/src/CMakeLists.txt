cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
#set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


SET(CMAKE_SYSTEM_NAME Linux)
#SET(CROSS_COMPILE "/Users/yaowenfeng/Downloads/opt/FriendlyARM/toolschain/4.4.3/bin/arm-none-linux-gnueabi-g++")
SET(DCMAKE_CXX_COMPILER "/Volumes/arm-x/ARMx-2009q3-67/arm-none-linux-gnueabi/bin/g++")

project(socket)

set(CMAKE_CXX_STANDARD 17)

include_directories(unix/select_poll /Volumes/arm-x/ARMx-2009q3-67/arm-none-linux-gnueabi/include/c++/4.4.1)
# unix
#link_libraries(curses)
#add_executable(socket main.cpp unix/server.cpp unix/client.cpp unix/graphics.cpp
#        unix/select_poll/server.cpp unix/select_poll/client.cpp)
add_executable(socket main.cpp unix/select_poll/server.cpp unix/select_poll/client.cpp)

# window
#link_libraries(wsock32)
#add_executable(socket2 main.cpp window/server.cpp window/client.cpp)
