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

void Application::ImGuiShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run()
{
    while( !s_scenes.empty() )
    {
        auto scene = std::move( s_scenes.top() );
        s_scenes.pop();
    
        scene->run(m_window);
    }
}


void Application::emplaceScene(Scene* scene)
{
    s_scenes.emplace( scene );
}


