#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <string>

#include <GLFW/glfw3.h>

int main()
{
    glfwInit();

    GLFWwindow* window =
        glfwCreateWindow(
            900,
            600,
            "Dictionary App",
            nullptr,
            nullptr);

    glfwMakeContextCurrent(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(
        window,
        true);

    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Dictionary");

        static char word[128] = "";

        ImGui::InputText(
            "Word",
            word,
            IM_ARRAYSIZE(word));

        std::string result = "";

        if (ImGui::Button("Search"))
        {
            // search dictionary
            result = word;
            ImGui::TextWrapped(
                "%s",
                result.c_str());
        }

        ImGui::Separator();

        ImGui::Text("Results will appear here");

        ImGui::End();

        ImGui::Render();

        int display_w;
        int display_h;

        glfwGetFramebufferSize(
            window,
            &display_w,
            &display_h);

        glViewport(
            0,
            0,
            display_w,
            display_h);

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}