cmake_minimum_required(VERSION 4.0.2)
project(fsoft2026_1DD_X)

set(CMAKE_CXX_STANDARD 14)


include_directories(Project/MedManager/headers)



add_executable(fsoft2026_1DD_X
        Project/MedManager/main.cpp
)