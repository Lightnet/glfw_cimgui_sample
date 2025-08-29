#define CIMGUI_USE_GLFW
#define CIMGUI_USE_OPENGL3

// #define CIMGUI_DEFINE_ENUMS_AND_STRUCTS

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cimgui.h>
#include <cimgui_impl.h>
// #include <imgui.h>

int main(void) {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only

    // Create a window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "cimgui GLFW Test", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize ImGui
    // ImGui_CreateContext();
    igCreateContext(NULL);
    ImGuiIO* io = igGetIO_Nil();

    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    // Setup Dear ImGui style
    igStyleColorsDark(NULL);

    // Setup Platform/Renderer backends
    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init("#version 130"); // Or your GLSL version


    // ImGuiIO* io = ImGui_GetIO();
    // io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard navigation
    // ImGui_StyleColorsDark(NULL); // Set dark theme

    // Initialize ImGui GLFW backend
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Initialize ImGui OpenGL backend
    if (!ImGui_ImplOpenGL3_Init("#version 130")) {
        ImGui_ImplGlfw_Shutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    ImVec2 buttonSize;
    buttonSize.x = 0;
    buttonSize.y = 0;

    // Main loop
    bool show_demo_window = true;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        igNewFrame();

        // Show ImGui demo window
        if (show_demo_window) {
            igShowDemoWindow(&show_demo_window);
        }

        igBegin("Hello, cimgui!", NULL, 0);
        igText("This is a test window using cimgui with GLFW!");
        if (igButton("Toggle Demo Window", buttonSize)) {
            show_demo_window = !show_demo_window;
        }

        igEnd();

        // Simple example window
        // ImGui_Begin("Hello, cimgui!", NULL, 0);
        // ImGui_Text("This is a test window using cimgui with GLFW!");
        // if (ImGui_Button("Toggle Demo Window")) {
        //     show_demo_window = !show_demo_window;
        // }
        // ImGui_End();

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui
        // ImGui_Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui_GetDrawData());
        igRender();
        ImGui_ImplOpenGL3_RenderDrawData(igGetDrawData());
        

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    // ImGui_DestroyContext(NULL);
    igDestroyContext(NULL);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}