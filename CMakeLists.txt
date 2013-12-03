###############################
# P1Charts configuration file #
###############################

cmake_minimum_required (VERSION 2.6)
project(P1Charts)

set(CMAKE_C_FLAGS "-std=c99") 

include_directories ("${PROJECT_SOURCE_DIR}/storage")
add_subdirectory (storage)
include_directories ("${PROJECT_SOURCE_DIR}/drawing")
add_subdirectory (drawing)

add_executable(p1charts main.c ./drawing/drawing.c ./storage/storage.c)
target_link_libraries (p1charts Drawing)
target_link_libraries (p1charts Storage)
