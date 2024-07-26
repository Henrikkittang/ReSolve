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


    std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << "\n";
    std::cout << "GL version: " << glGetString(GL_VERSION) << "\n";

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );
   
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();

    
    
    Shader shader{ "./resources/shaders/basic.shader" };    
    shader.bind();
    shader.setUniform4f("uColor", 0.1f, 0.3f, 0.8f, 1.0);

    Renderer renderer;


    glm::vec2 p1(0.3f, 0.3f);

    while (!glfwWindowShouldClose(window))
    {
        renderer.clear();


        std::vector<float> positions = {
            0.1f, 0.1f,  
            0.2f, 0.1f, 
            0.2f, 0.2f, 
            0.1f, 0.2f, 

            p1.x, p1.y,  
            0.4f, 0.3f, 
            0.4f, 0.4f, 
            0.3f, 0.4f, 
        };

        VertexBuffer vb(positions.data(), positions.size() * sizeof(float) );

        

        size_t vertex_count = positions.size() / 2; // 2 coordinates per vertex
        size_t quad_count = vertex_count / 4; // 4 vertices per quad
        size_t count = quad_count * 6; // 6 indices per quad

        std::vector<uint32_t> indices(count);


        for(size_t i = 0, vertex_index = 0; i < count; i += 6, vertex_index += 4)
        {
            indices[i + 0] = vertex_index + 0;
            indices[i + 1] = vertex_index + 1;
            indices[i + 2] = vertex_index + 2;
            indices[i + 3] = vertex_index + 2;
            indices[i + 4] = vertex_index + 3;
            indices[i + 5] = vertex_index + 0;
        }

        IndexBuffer ib(indices.data(), count);

        VertexBufferLayout layout;
        layout.push<float>(2);


        VertexArray va;
        va.addBuffer(vb, layout);


        renderer.draw(va, ib, shader);
       
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    
        {
            ImGui::SliderFloat2("Position 1", &p1.x, -1.0f, 1.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }


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