cmake_minimum_required(VERSION 3.5)
project(liteplayer)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/nanovg)

set(SOURCES
    src/Window.cpp
    src/main.cpp
)

if(WIN32)
    add_executable(liteplayer WIN32 ${SOURCES})
    target_link_options(liteplayer PRIVATE /ENTRY:mainCRTStartup)
else()
    add_executable(liteplayer ${SOURCES})
endif()

target_link_libraries(liteplayer PRIVATE glad glfw nanovg)
