cmake_minimum_required(VERSION 3.29)
project(DSA_Project2)

set(CMAKE_CXX_STANDARD 20)

include_directories(rb_tree measurement csv_parsing)

add_executable(DSA_Project2 main.cpp
        backend/b_tree/b_tree.cpp
        backend/b_tree/b_tree.h
        backend/red-black.cpp
        backend/red-black.h
        backend/csv-importer.cpp
        backend/csv-importer.h
        backend/measurement.h
        backend/measurement.cpp
)
