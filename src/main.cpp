#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>



#include "types.h"


int main(void)
{

    //Initializing GLFW
    if (!glfwInit())
        return -1;

    //Providing OpenGL hint to GLFW
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    //Creating a window
    GLFWwindow* window = glfwCreateWindow(800, 800, "My window", NULL, NULL);

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
    //glViewport(0, 0, 1280, 1280);


    std::cout << "OpenGl Version: ";
    std::cout << glGetString(GL_VERSION) << std::endl;

    //first x second y
    f32 vertexes[] = {
        -0.6f, -0.7f,
        -0.3f, -0.7f,
        -0.6f, -0.5f,

        -0.6f, -0.5f,
        -0.3f, -0.5f,
        -0.3f, -0.7f,

        0.6f, -0.7f,
        0.3f, -0.7f,
        0.6f, -0.5f,

        0.6f, -0.5f,
        0.3f, -0.5f,
        0.3f, -0.7f,


        -0.4f, -0.5f,
        0.4f, -0.5f,
        -0.4f, 0.8f,

        0.4f, 0.8f,
        0.4f, -0.5f,
        -0.4f, 0.8f,


        -0.2f, 0.4f,
        -0.2f, 0.6f,
        0.2f, 0.4f,


         0.2f, 0.6f,
        -0.2f, 0.6f,
         0.2f, 0.4f,

    };




    int number_of_triangles = (sizeof(vertexes) / sizeof(f32)) / 6 * 3;


    unsigned int vertex_buffer, vertex_array, vertex_buffer_2;

    //glGenVertexArrays(1, &vertex_array);
    //glBindVertexArray(vertex_array);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
    glEnableVertexAttribArray(0);





    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "uniform vec4 m_color;\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "   color = m_color;\n"
        "}\n";



    //Compiling Vertex shader
    unsigned int v_sh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_sh, 1, &vertexShaderSource, NULL);
    glCompileShader(v_sh);

    i32 vertex_result;
    glGetShaderiv(v_sh, GL_COMPILE_STATUS, &vertex_result);
    if (vertex_result == GL_FALSE)
    {
        std::cout << "Error occured when compiling vertex shader" << std::endl;
        int m_length;
        glGetShaderiv(v_sh, GL_INFO_LOG_LENGTH, &m_length);
        char* message = (char*)malloc(m_length * sizeof(char));
        glGetShaderInfoLog(v_sh, m_length, &m_length, message);
        std::cout << message << std::endl;
        free(message);
    }

    //Compiling Fragment shader
    unsigned int f_sh = glCreateShader(GL_FRAGMENT_SHADER);
    const char* f_sh_source = fragmentShader.c_str();
    glShaderSource(f_sh, 1, &f_sh_source, nullptr);
    glCompileShader(f_sh);

    i32 fragment_result;
    glGetShaderiv(f_sh, GL_COMPILE_STATUS, &fragment_result);
    if (fragment_result == GL_FALSE)
    {
        std::cout << "Error occured when compiling vertex shader" << std::endl;
        int m_length;
        glGetShaderiv(f_sh, GL_INFO_LOG_LENGTH, &m_length);
        char* message = (char*)malloc(m_length * sizeof(char));
        glGetShaderInfoLog(f_sh, m_length, &m_length, message);
        std::cout << message << std::endl;
        free(message);
    }

    unsigned int program = glCreateProgram();

    glAttachShader(program, v_sh);
    glAttachShader(program, f_sh);
    glLinkProgram(program);
    glValidateProgram(program);

    i32 success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);

    }


    glUseProgram(program);


    int location = glGetUniformLocation(program, "m_color");



    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //Cia³o

        glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 6 * 3);





        glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 3 * 6, 2 * 3);





        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwPollEvents();
        /* Poll for and process events */

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}