cmake_minimum_required(VERSION 3.0)
project (RivalOpenCV)
find_package (OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(SOURCES 
    src/main.cpp
    include/ball.cpp
    include/tangkap.cpp
)
add_executable (RivalOpenCV ${SOURCES})
target_link_libraries (RivalOpenCV ${OpenCV_LIBS})

