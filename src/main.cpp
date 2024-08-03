#include<iostream>
#include<array>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
   
#include"renderWindow.hpp"
#include"vertexBuffer.hpp"
#include"indexBuffer.hpp"
#include"vertexBufferLayout.hpp"
#include"vertexArray.hpp"
#include"shader.hpp"
#include"texture.hpp"

#include"tests/testClearColor.hpp"
#include"tests/testFractal.hpp"


int main(void)
{    
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw \n";
    }

    RenderWindow window(960, 540);

    
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui_ImplGlfw_InitForOpenGL( window.getWindow() , true);
    ImGui::StyleColorsDark();

    test::TestFractal test{};
    
    while ( !window.windowShouldClose() )
    {
        window.clear();
        
        test.onUpdate(window, 0);
        test.onRender(window, 0);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        test.onImGuiRender();
    
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.update();
    }



    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
   
    return 0;
}