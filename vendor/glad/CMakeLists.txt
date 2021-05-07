cmake_minimum_required(VERSION 3.10)

#Project setup
project("glad" LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)


set(glad_SOURCES "src/glad.c")
set(glad_HEADERS "include/glad/glad.h" "include/KHR/khrplatform.h")

include_directories("include")
#target_link_directories(${PROJECT_NAME} PRIVATE "include")
add_library(${PROJECT_NAME} STATIC ${glad_SOURCES} ${glad_HEADERS})
