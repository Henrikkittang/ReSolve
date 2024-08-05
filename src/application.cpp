#include"application.hpp"

#include<iostream>
#include<stack>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>

#include"util.hpp"
#include"scene.hpp"

Application::Application()
{
    int width  = 960; 
    int height = 540; // NB! needs to be initlized!

    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw \n";
    }

    m_window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!m_window)
    {
        std::cerr << "Failed to create glfw window \n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(m_window);
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initilize glew \n";
    }    

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
}


Application::~Application()
{
    glfwDestroyWindow(m_window);  
    
    if( m_isImguiActive )
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
    m_isImguiActive = false;

    glfwTerminate();
}


void Application::ImGuiInit()
{
    m_isImguiActive = true;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui_ImplGlfw_InitForOpenGL( m_window , true);
    ImGui::StyleColorsDark();
}


void Application::run()
{
    // This function kinda does a lot of things...
    // Maybe have a function for the stack and memory handling
    // and another with the game loop
    while( !s_scenes.empty() )
    {
        std::unique_ptr<Scene> scene = std::move( s_scenes.top() );
        s_scenes.pop();
    
        while( !glfwWindowShouldClose( m_window ) )
    {
            glClear(GL_COLOR_BUFFER_BIT);  
            
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            scene->onUpdate(m_window);
            scene->onRender(m_window);
            scene->onImGuiRender();
        
            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }


            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(m_window);
            glfwPollEvents();     
        }
    }
}


void Application::emplaceScene(Scene* scene)
{
    s_scenes.emplace( scene );
}

void Application::pushScene(std::unique_ptr<Scene>&& scene)
{
    s_scenes.push( std::move(scene) );
}
