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

set(GLFW_BUILD_DOCS OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_INSTALL OFF)
set(GLFW_UNINSTALL OFF)

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})


#Add glad
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/glad")
target_link_libraries(${PROJECT_NAME} glad)
target_include_directories(${PROJECT_NAME} PRIVATE "vendor/glad/include")

#Add fmt
add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fmt")
target_link_libraries(${PROJECT_NAME} fmt)
#########################################################################






#Advanced setup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(GLOBAL PROPERTY USE_FOLDERS OFF CACHE "" FORCE)


