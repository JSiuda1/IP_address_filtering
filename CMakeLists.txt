cmake_minimum_required(VERSION 3.26.3)

project("IP_address_filtering")

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)
add_executable(${PROJECT_NAME} main.c ${SRC_FILES})

add_executable(${PROJECT_NAME}_debug main.c ${SRC_FILES})
target_compile_definitions(${PROJECT_NAME}_debug PUBLIC "DEBUG")

include_directories(${PROJECT_SOURCE_DIR}/include/)
