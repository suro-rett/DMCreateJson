#pragma execution_character_set("utf-8")


#include "pch.h"
#include "MainScreen.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <Vector>
#include "your'ryWinAPI.h"

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
            ImGui::SetNextWindowSize(ImVec2(400, 200));
            ImGui::OpenPopup("ボタン変更");
            if (ImGui::BeginPopupModal( "ボタン変更", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("反応させたいキー・ボタンを押してください");
                ImGui::Text("元のままにする場合はキャンセルを,");
                ImGui::Text("IDLE(基本的な状態で流れる)にする場合はIDLEを押してください");
                ImGui::Text("");
                float buttonWidth = 100.0f;
                float spacing = ImGui::GetStyle().ItemSpacing.x;

                float totalWidth = buttonWidth * 2 + spacing;

                float startX =(ImGui::GetContentRegionAvail().x - totalWidth) * 0.5f;

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + startX);

                if (ImGui::Button("キャンセル", ImVec2(buttonWidth, 50)))
                {
                    simageList[i].changeButton = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("IDLE", ImVec2(buttonWidth, 50)))
                {
                    simageList[i].imageList.SetKey(IDLE);
                    simageList[i].changeButton = false;
                }

                if (simageList[i].changeButton) {
                    for (int j = 0; j < 256; j++) {
                        if (IsKeyDown(j)) {
                            simageList[i].imageList.SetKey(j);
                            simageList[i].changeButton = false;
                        }
                    }
                }


                ImGui::EndPopup();
            }
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
