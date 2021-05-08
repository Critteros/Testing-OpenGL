cmake_minimum_required(VERSION 3.10)


#Project initial-setup
project("OpenGL-test" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(deps-source-dir "${PROJECT_SOURCE_DIR}/vendor")


# Finding all source files for this project
file(GLOB sources "src/*.cpp" "src/*.h" "src/*.c")
add_executable(${PROJECT_NAME} ${sources})


#########################################################################
# Load Dependecies                                                      #
#########################################################################
set(project-deps-list)

# Glad
#########################################################################
add_subdirectory("${deps-source-dir}/glad")
list(APPEND project-deps-list glad)
#set_target_properties(glad PROPERTIES FOLDER "external-library")
#########################################################################

# GLFW 
#########################################################################
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
set(GLFW_UNINSTALL      OFF CACHE BOOL "" FORCE)
set(GLFW_VULKAN_STATIC  OFF CACHE BOOL "" FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/GLFW")
list(APPEND project-deps-list glfw)
#########################################################################

# fmt
#########################################################################
set(FMT_DOC OFF CACHE BOOL "Generate the doc target." FORCE)
set(FMT_INSTALL OFF CACHE BOOL "Generate the install target." FORCE)
set(FMT_TEST OFF CACHE BOOL "Generate the test target." FORCE)
set(FMT_FUZZ OFF CACHE BOOL "Generate the fuzz target." FORCE)
set(FMT_CUDA_TEST OFF CACHE BOOL "Generate the cuda-test target." FORCE)
set(FMT_OS OFF CACHE BOOL "Include core requiring OS (Windows/Posix) " FORCE)

add_subdirectory("${PROJECT_SOURCE_DIR}/vendor/fmt")
list(APPEND project-deps-list fmt)
#########################################################################


# Add properties to dependencies
#########################################################################

foreach(target ${project-deps-list})
    set_target_properties(${target}
    PROPERTIES 
        FOLDER "external-library"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        )
endforeach(target ${project-deps-list})

#########################################################################
#########################################################################

#Linking dependencies
add_library(project-deps INTERFACE)
foreach(target ${project-deps-list})
    target_link_libraries(project-deps INTERFACE ${target})
endforeach()
target_link_libraries(${PROJECT_NAME} PRIVATE project-deps)


#Advanced setup
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    )


#Preprocessor Defines
add_compile_definitions(GLFW_INCLUDE_NONE)


