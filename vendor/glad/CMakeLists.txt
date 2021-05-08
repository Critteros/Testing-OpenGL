cmake_minimum_required(VERSION 3.10)

#Project setup
project("glad" LANGUAGES C CXX)


set(glad_SOURCES "src/glad.c")
set(glad_HEADERS "include/glad/glad.h" "include/KHR/khrplatform.h")

add_library(${PROJECT_NAME} STATIC ${glad_SOURCES} ${glad_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC "${glad_SOURCE_DIR}/include")