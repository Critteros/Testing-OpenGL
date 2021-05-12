#include <iostream>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <fmt/core.h>
#include <fmt/color.h>

#include "types.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800


void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    
    
    switch (severity)
    {
    case(GL_DEBUG_SEVERITY_HIGH):
        fmt::print(fg(fmt::color::crimson),
            "[GL_HIGH]: type = {} \n\t{}\n", type, message);
    break;

    case(GL_DEBUG_SEVERITY_MEDIUM):
        fmt::print(//fg(fmt::color::yellow),
            "[GL_MEDIUM]: type = {} \n\t{}\n", type, message);
    break;

    case(GL_DEBUG_SEVERITY_LOW):
        fmt::print(fg(fmt::color::light_green),
            "[GL_LOW]: type = {} \n\t{}\n", type, message);
    break;

    case(GL_DEBUG_SEVERITY_NOTIFICATION):
        fmt::print(//fg(fmt::color::silver),
            "[GL_INFO]: type = {} \n\t{}\n", type, message);    
    break;
    }
}
    
    



int main(void)
{

    //Initializing GLFW
    if (!glfwInit())
        return -1;

    //Providing OpenGL hint to GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    //Creating a window
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "My window", NULL, NULL);
   

    //If the window could not be created
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Making window current rendering context
    glfwMakeContextCurrent(window);
    //glfwSwapInterval(0);

    //Loading OpenGL mappings
    gladLoadGL();

    //Debug messages
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    //Initial ViewPort size for OpenGL to render in
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);


    std::cout << "OpenGl Version: " << glGetString(GL_VERSION) << std::endl;


    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec4 positions;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = positions;\n"
        "}\0";

    const char* fragmentShaderSource =
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
    u32 v_sh = glCreateShader(GL_VERTEX_SHADER);
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
    u32 f_sh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_sh, 1, &fragmentShaderSource, nullptr);
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

    u32 program = glCreateProgram();

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


    //glUseProgram(program);


    f32 data1[] =
    {
        //Leg1
        -0.6f, -0.7f,
        -0.3f, -0.7f,
        -0.6f, -0.5f,

        -0.6f, -0.5f,
        -0.3f, -0.5f,
        -0.3f, -0.7f,
    };

    f32 data2[] =
    {
        //Leg2
        0.6f, -0.7f,
        0.3f, -0.7f,
        0.6f, -0.5f,

        0.6f, -0.5f,
        0.3f, -0.5f,
        0.3f, -0.7f,
    };

    f32 data3[] =
    {
        //Body
        -0.4f, -0.5f,
         0.4f, -0.5f,
        -0.4f,  0.8f,

         0.4f,  0.8f,
         0.4f, -0.5f,
        -0.4f,  0.8f,
    };

    f32 data4[] =
    {
        //Eye
        -0.2f, 0.4f,
        -0.2f, 0.6f,
         0.2f, 0.4f,


         0.2f, 0.6f,
        -0.2f, 0.6f,
         0.2f, 0.4f,
    };






    u32 vertex_array;
    //Generating Vertex Array
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    
    u32 buffer_1, leg1, leg2, body, eye;
    //Generating buffers
    glGenBuffers(1, &buffer_1);
    glGenBuffers(1, &leg1);
    glGenBuffers(1, &leg2);
    glGenBuffers(1, &body);
    glGenBuffers(1, &eye);



    //Loading to leg1
    glBindBuffer(GL_ARRAY_BUFFER, leg1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data1), data1, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Loading to leg2
    glBindBuffer(GL_ARRAY_BUFFER, leg2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data2), data2, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ////Loading to body
    glBindBuffer(GL_ARRAY_BUFFER, body);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data3), data3, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    ////Loading to eye
    glBindBuffer(GL_ARRAY_BUFFER, eye);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data4), data4, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    



    

    


    int location = glGetUniformLocation(program, "m_color");



 

    

    //Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

       
        //Rendering
        glUseProgram(program);

        glUniform4f(location, 0.863f, 0.078f, 0.235f, 1.0f);
        //Leg1
        glBindBuffer(GL_ARRAY_BUFFER, leg1);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

        //Leg2
        glBindBuffer(GL_ARRAY_BUFFER, leg2);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

        //Body
        glBindBuffer(GL_ARRAY_BUFFER, body);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);


        //Eye
        glBindBuffer(GL_ARRAY_BUFFER, eye);
        glUniform4f(location, 1.0f, 1.0f, 1.0f, 1.0f);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), 0);
        glEnableVertexAttribArray(0);
        glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

      
        glUseProgram(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        glfwPollEvents();
        /* Poll for and process events */

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}