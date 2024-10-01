cmake_minimum_required(VERSION 3.10)

#Set the compiling mode flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-03 -DNDEBUG -s")

# Set the project name
project(rootthreads)

include_directories(include)

add_executable(rootthreads src/main.c
        include/data.h
        src/data.c
        src/root.c
        include/root.h)

target_link_libraries(rootthreads m)
