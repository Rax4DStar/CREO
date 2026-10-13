cmake_minimum_required(VERSION 3.25)

project(creo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB FRONTEND_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(FILTER FRONTEND_SOURCES EXCLUDE REGEX "/main\\.cpp$")

add_library(gsisi_frontend ${FRONTEND_SOURCES})
target_include_directories(gsisi_frontend
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

add_executable(si_compiler
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)
target_link_libraries(si_compiler PRIVATE gsisi_frontend)
