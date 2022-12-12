cmake_minimum_required(VERSION 3.23)
project(webserver)

add_compile_definitions(ASIO_STANDALONE)
set(CMAKE_CXX_STANDARD 20)
set(ASIO_DIR asio)
include_directories(${ASIO_DIR})

link_libraries(ws2_32 wsock32)

add_executable(webserver main.cpp httprequest.cpp httpresponse.cpp Connection.cpp Connection.h server.cpp server.h response.cpp)
