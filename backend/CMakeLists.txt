cmake_minimum_required(VERSION 3.29)
project(backend)

set(CMAKE_CXX_STANDARD 20)

include_directories(rb_tree b_tree measurement csv_parsing)

add_executable(backend main.cpp
        rb_tree/red-black.cpp
        rb_tree/red-black.h
        csv_parsing/csv-importer.cpp
        csv_parsing/csv-importer.h
        measurement/measurement.cpp
        measurement/measurement.h
)
