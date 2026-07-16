#pragma execution_character_set("utf-8")


#include "pch.h"
#include "MainScreen.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "your'ryWinAPI.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void MainScreen::Update() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_MenuBar;

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.3f, 0.4f, 0.4f, 1.0f));
    ImGui::Begin("MainWindow", nullptr, flags);
    MenuPanel();
    if (ImGui::BeginTable("MainTable", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInnerV))
    {
        if (IsKeyDown(VK_CONTROL) && IsKeyPressed('S'))SaveJson();
        if (IsKeyDown(VK_CONTROL) && IsKeyPressed('O'))OpenJson();
        KeyPanel();
        ImagePanel();
        ConfigPanel();

        ImGui::EndTable();
    }

    ImGui::End();

    ImGui::PopStyleColor(); // スタイルを元に戻す
}

void MainScreen::KeyPanel() {
    ImGui::TableNextColumn();

    ImGui::BeginChild("Key");

    ImGui::Text("キー・ボタン");

    float width = ImGui::GetContentRegionAvail().x;

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.0f, 1.0f, 1.0f));
    if (ImGui::Button("+", ImVec2(width , 100)))
    {
        simageList.push_back({deviceResources,m_time});
    }
    ImGui::PopStyleColor();
    for (size_t i = 0; i < simageList.size(); i++)
    {
        ImGui::PushID((int)i);
        bool current = (i == choicesImageList);
        if (current)
        {
            ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(0.8f, 0.5f, 0.0f, 1.0f));  //選択中の場合はボタンの色変更
        }
        else {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.0f, 1.0f, 1.0f));
        }
        if(ImGui::Button(simageList[i].imageList.GetKey().c_str(), ImVec2(width * 0.5f, 100))){
            if(choicesImageList >= 0)simageList[choicesImageList].imageList.ResetAllImage();
            choicesImageList = (int)i;
            simageList[choicesImageList].imageList.SetAllImage();
        }

        ImGui::PopStyleColor();
        


        ImGui::SameLine();
        ImGui::BeginGroup();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.0f, 1.0f, 1.0f));
        if (ImGui::Button("X"))
        {
            ImGui::PopStyleColor();
            if (choicesImageList == i) {
                choicesImageList = -1;
            }
            else if (choicesImageList > i) {
                choicesImageList -= 1;
            }
            simageList.erase(simageList.begin() + i);
            ImGui::PopID();
            ImGui::EndGroup();
            break;
        }

        if (ImGui::Button("ボタン変更"))
        {
            if (!simageList[i].changeButton) {
                ImGui::PopStyleColor();
                simageList[i].changeButton = true;

                ImGui::PopID();
                ImGui::EndGroup();
                break;
            }
        }
        ImGui::PopStyleColor();

        ChangeKey(i);

        ImGui::PopID();

        ImGui::EndGroup();
    }


    ImGui::EndChild();
}

void MainScreen::ChangeKey(size_t i) {
    if (simageList[i].changeButton) {

        ImGui::SetNextWindowSize(ImVec2(400, 200));
        ImGui::OpenPopup("ボタン変更");
        if (ImGui::BeginPopupModal("ボタン変更", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("反応させたいキー・ボタンを押してください");
            ImGui::Text("元のままにする場合はキャンセルを,");
            ImGui::Text("IDLE(基本的な状態で流れる)にする場合はIDLEを押してください");
            ImGui::Text("");
            float buttonWidth = 100.0f;
            float spacing = ImGui::GetStyle().ItemSpacing.x;

            float totalWidth = buttonWidth * 2 + spacing;

            float startX = (ImGui::GetContentRegionAvail().x - totalWidth) * 0.5f;

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
                simageList[i].imageList.SetLoop(true);
            }

            if (simageList[i].changeButton) {
                for (int j = 0; j < 166; j++) {//166なのはVkで0xA1以降はあまり意味がないため
                    if (IsKeyReleased(j)) {
                        if (simageList[i].imageList.GetKey() == "IDLE") {
                            simageList[i].imageList.SetLoop(false);
                        }
                        simageList[i].imageList.SetKey(j);
                        simageList[i].changeButton = false;
                        break;
                    }
                }
            }


            ImGui::EndPopup();
        }
    }
}

void MainScreen::ImagePanel() {
    ImGui::TableNextColumn();

    ImGui::BeginChild("ImageList");
    ImGui::Text("画像リスト");

 
    if (choicesImageList <= -1) {
        CenterImGuiText("←　キー・ボタンのボタンを");
        CenterImGuiText("選択すると");
        CenterImGuiText("此処が表示されます");
    }
    else {
        simageList[choicesImageList].imageList.ImageDataUpdate();
    }



    ImGui::EndChild();
}

void MainScreen::ConfigPanel() {
    ImGui::TableNextColumn();
    ImGui::BeginChild("Config");

    ImGui::Text("設定");
    if (choicesImageList <= -1) {

    }
    else {
        simageList[choicesImageList].imageList.ConfigUpdate();
    }

    ImGui::EndChild();
}


void MainScreen::CenterImGuiText(const char* text) {
    ImVec2 textSize = ImGui::CalcTextSize(text);
    ImVec2 windowSize = ImGui::GetWindowSize();

    ImGui::SetCursorPosX(
        (windowSize.x - textSize.x) * 0.5f
    );

    ImGui::Text("%s", text);
}

void MainScreen::MenuPanel() {
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("ファイル")) {
            if (ImGui::MenuItem("開く", "Ctrl+O")) {
                OpenJson();
            }
            if (ImGui::MenuItem("保存", "Ctrl+S")) { 
                SaveJson();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void MainScreen::OpenJson() {
    std::wstring FileName = OpenJsonFileW();
    if (FileName != L"") {
        if (subwstrBack(FileName, 4, 4) == L"json") {
            std::ifstream file(FileName);
            if (!file.is_open())
            {
                std::wstring message = L"jsonファイル読み込み失敗。 ファイル名：" + FileName + L"\n\n重要ファイルが見つからないため、ソフトを停止します\n";
                MessageBoxW(NULL, message.c_str(), L"Error", MB_OK);
                return;
            }
            json j;

            file >> j;

            bool File = true;

            if (!j.contains("imageData"))
            {
                MessageBoxW(
                    nullptr,
                    L"このアプリ用のJSONファイルではありません。",
                    L"エラー",
                    MB_OK | MB_ICONERROR);

                return;
            }

            for (const auto& img : j["imageData"])
            {
                if (!img.contains("type") ||
                    !img.contains("paths") ||
                    !img.contains("frameMs") ||
                    !img.contains("scale") ||
                    !img.contains("loop"))
                {
                    MessageBoxW(
                        nullptr,
                        L"JSONの形式が正しくありません。",
                        L"エラー",
                        MB_OK | MB_ICONERROR);
                    File = false;
                    return;
                }
            }

            simageList.clear();
            choicesImageList = -1;

            
            //imageData.emplace_back();
            for (const auto& img : j["imageData"])
            {
                sImageData imageData{img["frameMs"].get<int>(),img["scale"].get<float>(),img["loop"].get<bool>() };

                std::vector<sImagePath> imagePath;
                for (int i = 0; i < img["paths"].get<std::vector<std::string>>().size(); i++) {
                    imagePath.emplace_back();
                    imagePath.back().imagePaths = StringToWString(img["paths"].get<std::vector<std::string>>()[i]);
                }

                simageList.push_back({ deviceResources,m_time });
                simageList.back().imageList.SetKey(img["type"].get<int>());
                simageList.back().imageList.SetJsonImage(imagePath, imageData);
            }
        }
    }
}

void MainScreen::SaveJson() {
    std::string fileName;
    if (simageList.size() != 0) {
        bool a = false;
        for (auto& List : simageList) {
            if (!a) {
                a = List.imageList.CheckImagePath();
            }
        }
        if (a) {
            fileName = SaveFileDialogString("NewFile", "json", GetRelativePath().c_str());
            if (fileName == "") {
                return;
            }
        }
        else {
            std::wstring message = L"jsonファイル保存失敗。 \n\nデータが無いため保存できません\n";
            MessageBoxW(NULL, message.c_str(), L"Error", MB_OK);
            return;
        }
    }

    nlohmann::json j;

    j["imageData"] = nlohmann::json::array();

    for (auto& List : simageList) {
        if (List.imageList.CheckImagePath()) {
            std::vector<std::string> Path;
            for (auto& Image : List.imageList.GetImagePath()) {
                if (Image.imagePaths != L"NoData") {
                    Path.emplace_back(WStringToString(Image.imagePaths));
                }
            }
            nlohmann::json item;

            item["paths"] = Path;
            item["type"] = List.imageList.GetIntKey();
            item["frameMs"] = List.imageList.GetImageData().frameMs;
            item["scale"] = std::round(List.imageList.GetImageData().scale * 1000.0f) / 1000.0f;
            item["loop"] = List.imageList.GetImageData().loop;

            j["imageData"].push_back(item);
        }
    }

    std::ofstream ofs(fileName);

    if (ofs)
    {
        ofs << std::setw(2) << j;
    }
}

void MainScreen::OnDropImages(std::vector<std::wstring> paths) {
    if (choicesImageList >= 0) {
        simageList[choicesImageList].imageList.OnDropImages(paths);
    }
}