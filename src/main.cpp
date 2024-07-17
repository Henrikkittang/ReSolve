#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>    

#include <cstdint>

#include<renderer.hpp>
#include<vertexBuffer.hpp>
#include<indexBuffer.hpp>
#include<vertexBufferLayout.hpp>
#include<vertexArray.hpp>
#include<shader.hpp>
#include<renderer.hpp>


int main(void)
{    
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
        std::cout << "Error \n";
    else
        std::cout << "Aight \n";

    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    uint32_t indecies[] = {
        0, 1, 2,
        2, 3, 0
    };

   
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);

    VertexArray va;
    va.addBuffer(vb, layout);    

    IndexBuffer ib(indecies, 6); 
     
    Shader shader("C:/Users/henri/Jottacloud/kode/cpp/opengl/renderer/resources/shaders/basic.shader");
    shader.bind();

    shader.setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();



    float r = 0.0f;
    float increment = 0.0001f;


    Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        shader.bind();
        shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        renderer.draw(va, ib, shader);

        if(r > 1.0f || r < 0.0f)
            increment = -increment;
        
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

       
    }

   
    glfwTerminate();
    return 0;
}