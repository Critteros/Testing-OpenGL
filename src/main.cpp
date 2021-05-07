#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "types.h"


int main(void)
{

    //Initializing GLFW
    if (!glfwInit())
        return -1;

    //Providing OpenGL hint to GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //Creating a window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "My window", NULL, NULL);

    //If the window could not be created
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Making window current rendering context
    glfwMakeContextCurrent(window);

    //Loading OpenGL mappings
    gladLoadGL();

    glViewport(0, 0, 1280, 720);

    //Main loop
    while (!glfwWindowShouldClose(window))
    {


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}