#include"application.hpp"

#include<iostream>
#include<stack>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>

#include"util.hpp"
#include"scene.hpp"
#include"event.hpp"
#include"random.hpp"

Application::Application(uint32_t screenWidth, uint32_t screenHeight, const std::string& title)
{
    Random::initialize();

    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw \n";
    }

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create glfw window \n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initilize glew \n";
    }    

    m_window = RenderWindow(window);
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
}


Application::~Application()
{
    // glfwDestroyWindow(m_window);  
    
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
    ImGui_ImplGlfw_InitForOpenGL( m_window.getWindow() , true);
    ImGui::StyleColorsDark();
}


void Application::run()
{
    while( !s_scenes.empty() )
    {
        Scene* scene = s_scenes.top();
        s_scenes.pop();

        scene->init();
        runScene( scene );
    }
}


void Application::addScene(Scene* scene)
{
    // This function may be better written if the scene type is a templated argument
    // This way the ownership would be better defined. Another solution is a unique_ptr
    s_scenes.push( scene );
}

// Private functions

void Application::runScene(Scene* scene)
{
    while( !m_window.windowShouldClose() )
    {
        Event event;
        while( EventManager::pollEvent(event) )
        {
            if( event == Event::END_CURRENT_SCENE )
                return;
        }

        m_window.clear();
        
        if( m_isImguiActive )
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }
        
        scene->onUpdate(m_window);
        scene->onRender(m_window);
        scene->onImGuiRender();

        if( m_isImguiActive )
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        
        m_window.update();
         
    }
}
