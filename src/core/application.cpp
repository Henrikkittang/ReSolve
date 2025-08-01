#include"application.hpp"

#include<stack>
#include<thread>

#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include<imgui/imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>


#include"core/scene.hpp"
#include"core/event.hpp"
#include"util/random.hpp"
#include"util/log.hpp"


Application::Application(uint32_t screenWidth, uint32_t screenHeight, const std::string& title)
{
    Random::initialize();
    Noise::initilize();
    Logger::initilize("");

    if (!glfwInit())
        LOG_FATAL("Failed to initialize GLFW");


    // Request OpenGL 4.6 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Optional: forward-compatible context (for macOS and strict compliance)
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        LOG_FATAL("Failed to create GLFW window ");
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwDestroyWindow(window);
        glfwTerminate();
        LOG_FATAL("Failed to initialize GLAD");
    }

    m_window = RenderWindow(window);
    m_window.setVSync(false);

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

#ifdef RS_DEBUG
    enableOpenGLDebugOutput();
#endif
    LOG_INFO("OpenGL Version: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
    LOG_INFO("GL Renderer: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
    LOG_INFO("GL Vendor: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VENDOR))));

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
    ImGui_ImplGlfw_InitForOpenGL( m_window.getNativeHandle() , true);
    ImGui::StyleColorsDark();
}


void Application::run()
{
    auto names = m_sceneManager.getNames();
    std::string currentname = names[0];
    m_sceneManager.setCurrentScene(currentname);

    // ! Kinda bad, means that all systems depend on wether window should close or not
    // ! Add a m_running memeber and add window should close as a possible way of finishing app
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



