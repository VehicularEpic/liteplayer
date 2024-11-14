cmake_minimum_required(VERSION 3.5)
project(liteplayer)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/nanovg)

if(WIN32)
    add_executable(liteplayer WIN32 main.cpp)
    target_link_options(liteplayer PRIVATE /ENTRY:mainCRTStartup)
else()
    add_executable(liteplayer main.cpp)
endif()

target_link_libraries(liteplayer PRIVATE glad glfw nanovg)
