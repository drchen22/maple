#include <cmath>
#include <iostream>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "editor/editor.hpp"
#include "runtime/shader.hpp"
#include "runtime/path.h"
#include "runtime/stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);


int main() {

    std::cout << "Hello, World!" << std::endl;

    // Initialize GLFW
    // ---------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(1024, 800, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // set up imgui
    // -------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.Fonts->AddFontFromFileTTF("./assets/fonts/mona_neon.ttf", 24.0f);

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(6.0f);

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader(Path("./shaders/vertex.vs").c_str(), "./shaders/fragment.fs");
    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // 位置              
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        -0.5f,  -0.5f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    float texCoords[] = {
    0.0f, 0.0f, // 左下角
    1.0f, 0.0f, // 右下角
    0.5f, 1.0f // 上中
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
    // and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //generate texture
    //--------------------
    stbi_set_flip_vertically_on_load(true);

    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // 设置texture环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    int width, height, nrChannels;
    unsigned char* data = stbi_load("./assets/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    
    }else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 设置texture环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载并生成纹理
    data = stbi_load("./assets/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    
    }else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // Start the Dear ImGui frame
        // ---------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // imgui window
        float mixValue;
        maple::RenderUI(mixValue);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        float time_value = glfwGetTime();
        float greenValue = sin(time_value) / 2.0f + 0.5f;
        float redValue = sin(time_value + 3.0f) / 2.0f + 0.5f;
        float buleValue = sin(time_value + 6.0f) / 2.0f + 0.5f;
        // int vertexColorLocation =
        //     glGetUniformLocation(shaderProgram, "aColor");
        // glUniform3f(vertexColorLocation, redValue, greenValue, buleValue);
        ourShader.setFloat("mixValue", mixValue);
        ourShader.setVec3f("aColor", greenValue, redValue, buleValue);
        ourShader.use();
        

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);   
        glActiveTexture(GL_TEXTURE1);

        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's
                                // no need to bind it every time, but we'll do
                                // so to keep things a bit more organized
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}