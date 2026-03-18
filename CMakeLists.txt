cmake_minimum_required(VERSION 3.29)
project(DSA_Project2)

set(CMAKE_CXX_STANDARD 20)

include_directories(rb_tree measurement csv_parsing)

add_executable(DSA_Project2 main.cpp
        rb_tree/red-black.cpp
        rb_tree/red-black.h
        csv_parsing/csv-importer.cpp
        csv_parsing/csv-importer.h
        measurement/measurement.h
        measurement/measurement.cpp
)
