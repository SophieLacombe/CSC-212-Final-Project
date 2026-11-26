#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <string>
#include "suffix_array/search.h"
#include "Linear_Search/L_search.h"

#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
    Search suffixSearch("../suffix_array/text.bin", "../suffix_array/suffixes.bin", "../suffix_array/entry_starts.bin");
    L_search linearSearch("../Linear_Search/clean_dictionary.csv");

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
        if (ImGui::BeginTabBar("SearchTabs"))
        {

            if (ImGui::BeginTabItem("Suffix Search"))
            {
                static char suffixWord[128] = "";
                static std::vector<Entry> suffixResults;

                ImGui::InputText(
                    "##SuffixWord",
                    suffixWord,
                    IM_ARRAYSIZE(suffixWord));

                if (ImGui::Button("Search Suffix"))
                {
                    suffixResults =
                        suffixSearch.formatResults(
                            suffixSearch.find(suffixWord));
                }

                ImGui::Separator();

                if (suffixResults.empty())
                {
                    ImGui::Text("Results will appear here");
                }
                else
                {
                    for (const Entry& entry : suffixResults)
                    {
                        ImGui::Text("%s", entry.word.c_str());

                        ImGui::Indent();
                        ImGui::TextWrapped(
                            "%s",
                            entry.definition.c_str());
                        ImGui::Unindent();

                        ImGui::Separator();
                    }
                }

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Linear Search"))
            {
                static char linearWord[128] = "";
                static std::vector<LinearEntry> linearResults;

                ImGui::InputText(
                    "##LinearWord",
                    linearWord,
                    IM_ARRAYSIZE(linearWord));

                if (ImGui::Button("Search Linear"))
                {
                    linearResults = linearSearch.format_results(linearSearch.find(linearWord));
            
                }

                ImGui::Separator();

                if (linearResults.empty())
                {
                    ImGui::Text("Results will appear here");
                }
                else
                {
                    for (const LinearEntry& entry : linearResults)
                    {
                        ImGui::Text("%s", entry.word.c_str());

                        ImGui::Indent();
                        ImGui::TextWrapped(
                            "%s",
                            entry.definition.c_str());
                        ImGui::Unindent();

                        ImGui::Separator();
                    }
                }

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
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