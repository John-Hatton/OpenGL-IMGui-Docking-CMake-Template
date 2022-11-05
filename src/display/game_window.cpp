#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "display/game_window.hpp"
#include "shaders/shader.hpp"
#include <iostream>

// Template stuff
Shader s;
unsigned int VAO;
unsigned int VBO;
unsigned int EBO;


// Forward Declarations

static void openCVDisplay();

// Called whenever the window or framebuffer's size is changed
void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// 1. The first thing that is run when starting the window
void GameWindow::Initialize() {
    // Set GLFW stuff before window is created
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

// 2. Run after the window has been created, as well as the OpenGL context
void GameWindow::LoadContent() {
    // Set callback
    glfwSetFramebufferSizeCallback(this->windowHandle, FramebufferSizeCallback);

    // Initialize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // #InverseDerivative
    // Configuration from Docking Branch

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;


    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->windowHandle, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    std::cout << "INFO::IMGUI::SUCCESSFULLY_INITIALIZED" << std::endl;

    // Load the template shader
    s = Shader::LoadShader("resources/shaders/testing.vs", "resources/shaders/testing.fs");

    // Vertices needed for a square
    float vertices[] = {
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    // Indices for rendering the above square
    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Create Vertex Array object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // And bind it

    // Create Vertex Buffer object
    glGenBuffers(1, &VBO);
    // And bind it (this also includes it into the VAO)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Fill the VBO with vertex data, simply positions
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout = 0 should contain these positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // Enable that shit

    // Create index buffer
    glGenBuffers(1, &EBO);
    // And bind it (also included in VAO)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Fill with indices!
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void GameWindow::Update() {
    // Performs hot-reload of shader. Only reloads whenever it has been modified - so not every frame.
    s.ReloadFromFile();
}

void GameWindow::Render() {
    // Bind the VAO
    glBindVertexArray(VAO);

    // Make sure we're using the correct shader program.
    // Must be done per-frame, since the shader program id might change when hot-reloading
    glUseProgram(s.programID);

    // Create new imgui frames
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Clear the window
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the square
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Draw imgui
    //ImGui::ShowDemoWindow();
    ImPlot::ShowDemoWindow();
    //ShowExampleAppDockSpace();
    // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    openCVDisplay();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    /**
     * Necessary code below for Docking branch to work
     * #InverseDerivative
     */

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    // Swap double buffers and poll OS-events
    glfwSwapBuffers(this->windowHandle);
    glfwPollEvents();
}

void GameWindow::Unload() {
    // Destroy imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImPlot::DestroyContext();
}

static void displayLena(int columns, int rows, GLuint texture)
{
    ImGui::Begin("(OpenCV) Lena");
    ImGui::Image( reinterpret_cast<void*>( static_cast<intptr_t>( texture ) ), ImVec2( columns, rows ) );
    ImGui::End();
}


static void openCVDisplay()
{

    // OpenCV Stuff
    cv::Mat image = cv::imread( "C:\\dev\\Saves\\Cxx\\NetCam\\source\\ImGui_Sample\\images\\Lena.png", cv::IMREAD_COLOR );

    cv::cvtColor( image, image, cv::COLOR_BGR2RGBA );


    GLuint texture;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data );


    displayLena(image.cols, image.rows, texture);


}