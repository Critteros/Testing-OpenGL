cmake_minimum_required(VERSION 3.10)


#Project initial-setup
project("OpenGL-test" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


file(GLOB sources "src/*.cpp" "src/*.h" "src/*.c")
add_executable(${PROJECT_NAME} ${sources})

#Load Dependecies
#########################################################################
#Linking to GLFW
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/GLFW")

set(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
set(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
set(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
set(GLFW_INSTALL "Generate installation target" OFF)
set(GLFW_VULKAN_STATIC "Assume the Vulkan loader is linked with the application" OFF)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
set_target_properties(glfw PROPERTIES FOLDER "external-library")


#Add glad
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glad")
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/glad/include")
set_target_properties(glad PROPERTIES FOLDER "external-library")

#Add fmt
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fmt")

set(FMT_DOC "Generate the doc target." OFF)
set(FMT_INSTALL "Generate the install target." OFF)
set(FMT_TEST "Generate the test target." OFF)
set(FMT_FUZZ "Generate the fuzz target." OFF)
set(FMT_CUDA_TEST "Generate the cuda-test target." OFF)
set(FMT_OS "Include core requiring OS (Windows/Posix) " ON)

target_link_libraries(${PROJECT_NAME} fmt)
set_target_properties(fmt PROPERTIES FOLDER "external-library")
#########################################################################






#Advanced setup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
#set_property(GLOBAL PROPERTY USE_FOLDERS OFF CACHE "" FORCE)


