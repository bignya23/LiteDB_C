cmake_minimum_required(VERSION 3.29)
project(LiteDB_C C)

set(CMAKE_C_STANDARD 11)

add_executable(databasesql src/bufffer.c
        src/headers/bufffer.h
        src/helpers/helper_fn.h)
