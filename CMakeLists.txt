cmake_minimum_required(VERSION 3.21)
project(BasicPlatformer)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR E:/Files/Prog/cpp/libs/SDL2-2.0.20/include)
set(SDL2_LIB_DIR E:/Files/Prog/cpp/libs/SDL2-2.0.20/lib/x64)

set(SDL2_IMAGE_INCLUDE_DIR E:/Files/Prog/cpp/libs/SDL2_image-2.0.5/include)
set(SDL2_IMAGE_LIB_DIR E:/Files/Prog/cpp/libs/SDL2_image-2.0.5/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(BasicPlatformer main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_image )
