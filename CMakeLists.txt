cmake_minimum_required(VERSION 3.25)

project(creo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB FRONTEND_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(FILTER FRONTEND_SOURCES EXCLUDE REGEX "/main\\.cpp$")

add_library(creo_frontend ${FRONTEND_SOURCES})
target_include_directories(creo_frontend
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(creo
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)
target_link_libraries(creo PRIVATE creo_frontend)
