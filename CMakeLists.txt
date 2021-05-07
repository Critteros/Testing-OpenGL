cmake_minimum_required(VERSION 3.10)


#Project initial-setup
project("OpenGL-test" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


file(GLOB sources "src/*.cpp" "src/*.h" "src/*.c")
add_executable(${PROJECT_NAME} ${sources})

#Load Dependecies
#########################################################################

#Add glad
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glad")
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/glad/include")
set_target_properties(glad PROPERTIES FOLDER "external-library")



#Add GLFW

#GLFW switches
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target" FORCE)
set(GLFW_UNINSTALL OFF CACHE BOOL "Generate installation target" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "Assume the Vulkan loader is linked with the application" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/GLFW")
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
set_target_properties(glfw PROPERTIES FOLDER "external-library")


#Add fmt
#fmt switches
set(FMT_DOC OFF CACHE BOOL "Generate the doc target." FORCE)
set(FMT_INSTALL OFF CACHE BOOL "Generate the install target." FORCE)
set(FMT_TEST OFF CACHE BOOL "Generate the test target." FORCE)
set(FMT_FUZZ OFF CACHE BOOL "Generate the fuzz target." FORCE)
set(FMT_CUDA_TEST OFF CACHE BOOL "Generate the cuda-test target." FORCE)
set(FMT_OS OFF CACHE BOOL "Include core requiring OS (Windows/Posix) " FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fmt")
target_link_libraries(${PROJECT_NAME} fmt)
set_target_properties(fmt PROPERTIES FOLDER "external-library")

#########################################################################






#Advanced setup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
#set_property(GLOBAL PROPERTY USE_FOLDERS OFF CACHE "" FORCE)


