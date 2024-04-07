cmake_minimum_required(VERSION 3.26)
project(Run C)
set(CMAKE_C_STANDARD 17)
include_directories(include)
add_subdirectory(src)
target_link_libraries(Run PRIVATE
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_ttf
)