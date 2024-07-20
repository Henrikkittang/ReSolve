#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<array>
   
#include"renderer.hpp"
#include"vertexBuffer.hpp"
#include"indexBuffer.hpp"
#include"vertexBufferLayout.hpp"
#include"vertexArray.hpp"
#include"shader.hpp"
#include"texture.hpp"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>


int main(void)
{    
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize glfw" << std::endl;
        return -1;
    }

    const int SCREEN_WIDTH  = 640;
    const int SCREEN_HEIGHT = 480;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initilize glew \n";
        return -1;
    }    

   

    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f,
        200.0f, 100.0f, 1.0f, 0.0f,
        200.0f, 200.0f, 1.0f, 1.0f,
        100.0f, 200.0f, 0.0f, 1.0f
    };

    uint32_t indecies[] = {
        0, 1, 2,
        2, 3, 0
    };

    std::cout << "GL version: " << glGetString(GL_VERSION) << "\n";

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);

    VertexArray va;
    va.addBuffer(vb, layout);    

    IndexBuffer ib(indecies, 6); 

    Shader shader("./resources/shaders/basic.shader");
    shader.bind();
    
    shader.setUniform4f("uColor", 0.5f, 0.1f, 0.1f, 1.0f);

    glm::mat4 proj  = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));

    glm::mat4 mvp = proj * view * model;
    shader.setUniformMat4f("uMVP", mvp);

    Texture texture("./resources/textures/google.png");
    texture.bind();
    shader.setUniform1i("uTexture", 0);

    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    Renderer renderer;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontDefault();
    io.Fonts->Build();

    ImGui_ImplOpenGL3_Init("#version 330");

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui::StyleColorsDark();
 
    glm::vec3 translation(200.0f, 200.0f, 0.0f);
    
    float r = 0.0f;
    float inc = 0.0001;

 

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);

        glm::mat4 mvp = proj * view * model;

        shader.bind();
        shader.setUniform4f("uColor", r, 0.1f, 0.1f, 1.0f);
        shader.setUniformMat4f("uMVP", mvp);


        renderer.draw(va, ib, shader);

        if(r > 1.0f || r < 0.0f)
            inc = -inc;
        r += inc;

        {
            ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 640.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            // ImGui::End();
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();       
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
   
    glfwTerminate();
    return 0;
}