#pragma execution_character_set("utf-8")


#include "pch.h"
#include "MainScreen.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <Vector>

void MainScreen::Update() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse;

    ImGui::Begin("MainWindow", nullptr, flags);

    if (ImGui::BeginTable("MainTable", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV))
    {
        KeyPanel();
        ImagePanel();
        ConfigPanel();

        ImGui::EndTable();
    }

    ImGui::End();

}

void MainScreen::KeyPanel() {
    ImGui::TableNextColumn();

    ImGui::BeginChild("Key");

    ImGui::Text("キー・ボタン");

    float width = ImGui::GetContentRegionAvail().x;


    if (ImGui::Button("+", ImVec2(width , 100)))
    {
        simageList.push_back({});
    }

    for (size_t i = 0; i < simageList.size(); i++)
    {
        ImGui::PushID((int)i);

        ImGui::Button(simageList[i].imageList.GetKey().c_str(), ImVec2(width * 0.7f, 100));

        ImGui::SameLine();

        ImGui::BeginGroup();

        if (ImGui::Button("X"))
        {
            if (!simageList[i].changeButton) {
                simageList.erase(simageList.begin() + i);
                ImGui::PopID();
                ImGui::EndGroup();
                break;
            }
        }

        if (ImGui::Button("ボタン変更"))
        {
            if (!simageList[i].changeButton) {
                simageList[i].changeButton = true;

                ImGui::PopID();
                ImGui::EndGroup();
                break;
            }
        }

        if (simageList[i].changeButton) {
            ImGui::SetNextWindowSize(ImVec2(350, 200));
            ImGui::Begin("ボタン変更", nullptr,ImGuiWindowFlags_NoDocking);
            ImGui::Text("反応させたいキー・ボタンを押してください");
            ImGui::Text("元のままにする場合は×ボタンを押してください");

            ImGui::End();
        }

        ImGui::PopID();

        ImGui::EndGroup();
    }


    ImGui::EndChild();
}

void MainScreen::ImagePanel() {
    ImGui::TableNextColumn();

    ImGui::BeginChild("ImageList");

    ImGui::Text("画像リスト");

    ImGui::EndChild();
}

void MainScreen::ConfigPanel() {
    ImGui::TableNextColumn();

    ImGui::Text("設定");
}
