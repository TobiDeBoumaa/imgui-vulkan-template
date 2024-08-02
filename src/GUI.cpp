#include "GUI.hpp"

#include <implot.h>

#include "imgui.h"
#include "ImGuiNotify.hpp"

bool show_demo_window = false;
bool show_another_window = false;
bool show_implot_demo = false;

namespace GUI {
void init() {
  // Code here will be run once
}
void render() {
  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);
  if (show_implot_demo) ImPlot::ShowDemoWindow(&show_implot_demo);
  {
#ifdef IMGUI_HAS_VIEWPORT
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
#else
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
#endif
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    ImGui::Begin("Main Window", NULL,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);
    renderMainWindow();
    ImGui::End();
    ImGui::PopStyleVar(1);
  }
  static bool show_another_another_window = false;
  if(show_another_another_window){
  ImGui::Begin("Another Window", &show_another_another_window);
  ImGui::Text("Text: %i", show_demo_window);
  ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window) {
    ImGui::Begin(
        "Another Window",
        &show_another_window);  // Pass a pointer to our bool variable (the
                                // window will have a closing button that will
                                // clear the bool when clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me")) show_another_window = false;
    ImGui::End();
  }
}
void renderMainWindow() {
  if (ImGui::BeginTabBar("BasicTabBar", ImGuiTabBarFlags_None)) {
    if (ImGui::BeginTabItem("Examples")) {
      static int counter = 0;
      static float f = 0.0f;
      ImGui::Text("This is some useful text.");  // Display some text (you can
                                                 // use a format strings too)
      ImGui::Checkbox(
          "Demo Window",
          &show_demo_window);  // Edit bools storing our window open/close state
      ImGui::Checkbox("Another Window", &show_another_window);
      ImGui::Checkbox("ImPlot Demo", &show_implot_demo);

      ImGui::SliderFloat(
          "float", &f, 0.0f,
          1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
      // ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3
      // floats representing a color

      if (ImGui::Button("Increase counter"))  // Buttons return true when
                                              // clicked (most widgets return
                                              // true when edited/activated)
        counter++;
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);
      ImGui::EndTabItem();
      if (ImGui::Button("Success")) {
	    	ImGui::InsertNotification({ImGuiToastType::Success, 3000, "That is a success! %s", "(Format here)"});
	    }
      ImGui::Text("😊Hello, wöörld! 🫤");
      ImGui::Text("🍉 🍊 🍋");
      ImGui::Text("Funktionirän die Ümlaute? 💩 ->ß<-");
    }
    if (ImGui::BeginTabItem("Unused 1")) {
      int bar_data[11] = {25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275};
      float x_data[1000] = {0};
      float y_data[1000] = {0};
      if (ImPlot::BeginPlot("My Plot")) {
        ImPlot::PlotBars("My Bar Plot", bar_data, 11);
        ImPlot::PlotLine("My Line Plot", x_data, y_data, 1000);
        ImPlot::EndPlot();
      }
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Unused 2")) {
      ImGui::Text("This is the Cucumber tab!\nblah blah blah blah blah");
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
  ImGuiIO& io = ImGui::GetIO();
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / io.Framerate, io.Framerate);
}
}  // namespace GUI