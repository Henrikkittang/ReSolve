#include"application.hpp"

#include<iostream>
#include<stack>
#include<thread>


#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>

#include"core/scene.hpp"
#include"core/event.hpp"
#include"util/random.hpp"
#include"util/util.hpp"


Application::Application(uint32_t screenWidth, uint32_t screenHeight, const std::string& title)
{
    Random::initialize();
    Noise::initilize();

    if (!glfwInit())
    {
        std::cout << "Failed to initialize glfw \n";
        exit(0);
    }

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create glfw window \n";
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(0);
    }

    m_window = RenderWindow(window);
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
}


Application::~Application()
{
    // glfwDestroyWindow(m_window.getWindow());

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
    auto names = m_sceneManager.getNames();
    std::string currentname = names[0];
    m_sceneManager.setCurrentScene(currentname);

    while( !m_window.windowShouldClose() )
    {
        Event event;
        while( EventManager::pollEvent(event) )
        {
            if( event == Event::END_CURRENT_SCENE )  // This is possibly problematic with glfw
                return;
                // glfwSetWindowShouldClose(m_window.getWindow(), true);
        }

        m_window.clear();
        
        if( m_isImguiActive )
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        for(const std::string& name : names)
        {
            if(ImGui::RadioButton(name.c_str(), currentname == name))
            {
                m_sceneManager.setCurrentScene(name);
                currentname = name;
            }
        }

        Scene* scene = m_sceneManager.getCurrentScene();
        if(scene != nullptr)
        {
            scene->onUpdate();
            scene->onRender();
            scene->onImGuiRender();
        }
                

        if( m_isImguiActive )
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        
        m_window.update();
    }
}



