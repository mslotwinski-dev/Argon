cmake_minimum_required(VERSION 3.10)

project(Argon)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(src)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    main.cpp 
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
set(NUMC_ROOT "E:/GitHub/Entropy Logs/NumC")
add_subdirectory(${NUMC_ROOT} ${CMAKE_BINARY_DIR}/numc_build)
target_link_libraries(${PROJECT_NAME} PRIVATE numc)

