#include<iostream>
#include<array>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
   
#include"renderer.hpp"
#include"vertexBuffer.hpp"
#include"indexBuffer.hpp"
#include"vertexBufferLayout.hpp"
#include"vertexArray.hpp"
#include"shader.hpp"
#include"texture.hpp"

#include"tests/testClearColor.hpp"

int main(void)
{    
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return -1;
    }

    const int SCREEN_WIDTH  = 960;
    const int SCREEN_HEIGHT = 540;

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initilize glew \n";
        return -1;
    }    


    std::cout << "GL version: " << glGetString(GL_VERSION) << "\n";

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
   
    Renderer renderer;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
 
    
    test::TestClearColor test;

    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();

       

        test.onUpdate(0.0f);
        test.onRender();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        test.onImGuiRender();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();       
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
   
    glfwTerminate();
    return 0;
}