cmake_minimum_required(VERSION 3.22)
project(backend)

set(CMAKE_CXX_STANDARD 20)

include_directories(rb_tree b_tree measurement csv_parsing server_libs)

add_executable(backend main.cpp
        rb_tree/red-black.cpp
        rb_tree/red-black.h
        b_tree/b_tree.h
        b_tree/b_tree.cpp
        csv_parsing/csv-importer.cpp
        csv_parsing/csv-importer.h
        server_libs/httplib.h
)

if (WIN32)
    target_link_libraries(backend ws2_32)

    add_compile_definitions(
            _WIN32_WINNT=0x0A00
            WINVER=0x0A00
    )
endif()