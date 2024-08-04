#include"scene.hpp"

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>

void Scene::run(GLFWwindow* wn)
{
    while( !glfwWindowShouldClose( wn ) )
    {
        glClear(GL_COLOR_BUFFER_BIT);  
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        onUpdate(wn);
        onRender(wn);
        onImGuiRender();
    
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(wn);
        glfwPollEvents();     
    }
}

void Scene::onImGuiRender()
{}