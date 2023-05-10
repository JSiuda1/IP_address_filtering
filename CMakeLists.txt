cmake_minimum_required(VERSION 3.26.3)

project("IP_address_filtering")

# target_include_directories(${PROJECT_NAME} PRIVATE ${YOUR_DIRECTORY})
add_executable(${PROJECT_NAME} main.c ip_address.c ip_address.h ip_mask.c ip_mask.h)

