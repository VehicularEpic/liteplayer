cmake_minimum_required(VERSION 3.5)
project(liteplayer)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/nanovg)

if(WIN32)
    add_executable(liteplayer WIN32 main.cpp)
else()
    add_executable(liteplayer main.cpp)
endif()

target_link_libraries(liteplayer PRIVATE glfw nanovg)
