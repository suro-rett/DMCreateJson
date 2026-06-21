#pragma execution_character_set("utf-8")

#include "pch.h"
#include "MainScreen.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


void MainScreen::Update() {
    if (ImGui::BeginTable("MainTable", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV))
    {
        ImGui::TableNextColumn();

        ImGui::Text("画像リスト");

        ImGui::TableNextColumn();

        ImGui::Text("アニメーション順");

        ImGui::TableNextColumn();

        ImGui::Text("設定");

        ImGui::EndTable();
    }

}