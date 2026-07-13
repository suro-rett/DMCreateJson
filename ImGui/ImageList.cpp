#pragma execution_character_set("utf-8")

#include "pch.h"
#include "ImageList.h"
#include <WICTextureLoader.h>
#include "your'ryWinAPI.h"

std::string ImageList::GetKey() {

    std::string name;

    switch (vkey)
    {
    case IDLE:          name = "IDLE";                   break;

    case VK_LBUTTON:    name = "マウス左ボタン";         break;
    case VK_RBUTTON:    name = "マウス右ボタン";         break;
    case VK_MBUTTON:    name = "マウス中央ボタン";       break;
    case VK_XBUTTON1:   name = "マウスサイドボタン1";    break;
    case VK_XBUTTON2:   name = "マウスサイドボタン2";    break;

    case VK_BACK:       name = "BackSpace"; break;
    case VK_TAB:        name = "Tab";       break;
    case VK_RETURN:     name = "Enter";     break;
    case VK_SHIFT:      name = "Shift";     break;
    case VK_CONTROL:    name = "Ctrl";      break;
    case VK_MENU:       name = "Alt";       break;
    case VK_PAUSE:      name = "Pause";     break;
    case VK_CAPITAL:    name = "CapsLock";  break;
    case VK_ESCAPE:     name = "Esc";       break;
    case VK_SPACE:      name = "Space";     break;

    case VK_PRIOR:      name = "PageUp";    break;
    case VK_NEXT:       name = "PageDown";  break;

    case VK_END:        name = "End";       break;
    case VK_HOME:       name = "Home";      break;

    case VK_LEFT:       name = "←";break;
    case VK_UP:         name = "↑";break;
    case VK_RIGHT:      name = "→";break;
    case VK_DOWN:       name = "↓";break;

    case VK_INSERT:     name = "Insert";    break;
    case VK_DELETE:     name = "Delete";    break;
    case VK_NUMLOCK:    name = "NumLock";   break;
    case VK_SCROLL:     name = "ScrollLock";break;

    case VK_F1:  name = "F1";  break;
    case VK_F2:  name = "F2";  break;
    case VK_F3:  name = "F3";  break;
    case VK_F4:  name = "F4";  break;
    case VK_F5:  name = "F5";  break;
    case VK_F6:  name = "F6";  break;
    case VK_F7:  name = "F7";  break;
    case VK_F8:  name = "F8";  break;
    case VK_F9:  name = "F9";  break;
    case VK_F10: name = "F10"; break;
    case VK_F11: name = "F11"; break;
    case VK_F12: name = "F12"; break;

    case '0': name = "0"; break;
    case '1': name = "1"; break;
    case '2': name = "2"; break;
    case '3': name = "3"; break;
    case '4': name = "4"; break;
    case '5': name = "5"; break;
    case '6': name = "6"; break;
    case '7': name = "7"; break;
    case '8': name = "8"; break;
    case '9': name = "9"; break;

    case 'A': name = "A"; break;
    case 'B': name = "B"; break;
    case 'C': name = "C"; break;
    case 'D': name = "D"; break;
    case 'E': name = "E"; break;
    case 'F': name = "F"; break;
    case 'G': name = "G"; break;
    case 'H': name = "H"; break;
    case 'I': name = "I"; break;
    case 'J': name = "J"; break;
    case 'K': name = "K"; break;
    case 'L': name = "L"; break;
    case 'M': name = "M"; break;
    case 'N': name = "N"; break;
    case 'O': name = "O"; break;
    case 'P': name = "P"; break;
    case 'Q': name = "Q"; break;
    case 'R': name = "R"; break;
    case 'S': name = "S"; break;
    case 'T': name = "T"; break;
    case 'U': name = "U"; break;
    case 'V': name = "V"; break;
    case 'W': name = "W"; break;
    case 'X': name = "X"; break;
    case 'Y': name = "Y"; break;
    case 'Z': name = "Z"; break;

    case VK_NUMPAD0: name = "テンキー0"; break;
    case VK_NUMPAD1: name = "テンキー1"; break;
    case VK_NUMPAD2: name = "テンキー2"; break;
    case VK_NUMPAD3: name = "テンキー3"; break;
    case VK_NUMPAD4: name = "テンキー4"; break;
    case VK_NUMPAD5: name = "テンキー5"; break;
    case VK_NUMPAD6: name = "テンキー6"; break;
    case VK_NUMPAD7: name = "テンキー7"; break;
    case VK_NUMPAD8: name = "テンキー8"; break;
    case VK_NUMPAD9: name = "テンキー9"; break;

    case VK_MULTIPLY:name = "テンキー*";break;
    case VK_ADD:     name = "テンキー+";break;
    case VK_SUBTRACT:name = "テンキー-";break;
    case VK_DECIMAL: name = "テンキー.";break;
    case VK_DIVIDE:  name = "テンキー/";break;
    default:         name = "不明";     break;
    }

	return name;
}

void ImageList::SetKey(int setKey) {
	vkey = setKey;
}

void ImageList::SetAllImage() {
    if (simagePath.size() != 0) {
        for (auto& Path : simagePath) {
            if (Path.imagePaths != L"") {
                HRESULT hr = DirectX::CreateWICTextureFromFileEx(
                    deviceResources->GetD3DDevice(),
                    Path.imagePaths.c_str(),
                    0,
                    D3D11_USAGE_DEFAULT,
                    D3D11_BIND_SHADER_RESOURCE,
                    0,
                    0,
                    DirectX::WIC_LOADER_FORCE_RGBA32,
                    nullptr,
                    Path.texture.GetAddressOf());
                if (FAILED(hr))
                {
                    OutputDebugStringA("Load Failed\n");
                }
                if (SUCCEEDED(hr)) {
                    GetTextureSize(Path.texture.Get(), Path.textureWidth, Path.textureHeight);
                    if (Path.textureWidth % 2 == 1 || Path.textureHeight % 2 == 1) {
                        Path.texture.Reset();
                        Path.imagePaths = L"NoData";
                        PopUpSizeError = true;
                    }
                }
            }
        }

        lastTime = (float)m_timer->GetTotalSeconds();
        currentImageFrame = 0;
        CheckSize();
    }
}

void ImageList::CheckSize() {
    int backSizeHeight = -1, backSizeWidth = -1;
    bool check = false;
    for (auto& Path : simagePath) {
        if (backSizeHeight == -1) {
            backSizeHeight = (int)Path.textureHeight;
            backSizeWidth = (int)Path.textureWidth;
        }
        if ((int)Path.textureHeight != backSizeHeight ||(int)Path.textureWidth != backSizeWidth) {
            sizeMismatch = true;
            check = true;
            break;
        }
    }
    if (!check) {
        sizeMismatch = false;
    }
}


void ImageList::ResetAllImage() {
    if (simagePath.size() != 0) {
        for (auto& Path : simagePath) {
            if (Path.texture != nullptr) {
                Path.texture.Reset();
            }
        }
    }
}

void ImageList::SetImageData(int Vector,std::wstring path) {
    if (GIFcheck(path)) { return; }
    if (path != L"") {
        simagePath[Vector].imagePaths = path;
        simagePath[Vector].texture.Reset();
        if (simagePath[Vector].imagePaths != L"NoData") {
            simagePath[Vector].texture.Reset();

            HRESULT hr = DirectX::CreateWICTextureFromFileEx(
                deviceResources->GetD3DDevice(),
                path.c_str(),
                0,
                D3D11_USAGE_DEFAULT,
                D3D11_BIND_SHADER_RESOURCE,
                0,
                0,
                DirectX::WIC_LOADER_FORCE_RGBA32,
                nullptr,
                simagePath[Vector].texture.GetAddressOf());
            if (SUCCEEDED(hr)) {
                GetTextureSize(simagePath[Vector].texture.Get(), simagePath[Vector].textureWidth, simagePath[Vector].textureHeight);
                if (simagePath[Vector].textureWidth % 2 == 1 || simagePath[Vector].textureHeight % 2 == 1) {
                    simagePath[Vector].texture.Reset();
                    simagePath[Vector].imagePaths = L"NoData";
                    PopUpSizeError = true;
                }
            }
            else if (FAILED(hr))
            {
                OutputDebugStringA("Load Failed\n");
            }
        }
    }
    CheckSize();
}
void ImageList::SetImageData(std::vector<std::wstring> path) {
    if (GIFchecks(path)) { return; }
    for (auto& Image : path) {
        simagePath.push_back({});
        if (Image != L"") {
            simagePath.back().imagePaths = Image;
            simagePath.back().texture.Reset();
            if (simagePath.back().imagePaths != L"NoData") {
                simagePath.back().texture.Reset();

                HRESULT hr = DirectX::CreateWICTextureFromFileEx(
                    deviceResources->GetD3DDevice(),
                    Image.c_str(),
                    0,
                    D3D11_USAGE_DEFAULT,
                    D3D11_BIND_SHADER_RESOURCE,
                    0,
                    0,
                    DirectX::WIC_LOADER_FORCE_RGBA32,
                    nullptr,
                    simagePath.back().texture.GetAddressOf());
                if (SUCCEEDED(hr)) {
                    GetTextureSize(simagePath.back().texture.Get(), simagePath.back().textureWidth, simagePath.back().textureHeight);
                    if (simagePath.back().textureWidth % 2 == 1 || simagePath.back().textureHeight % 2 == 1) {
                        simagePath.back().texture.Reset();
                        simagePath.back().imagePaths = L"NoData";
                        PopUpSizeError = true;
                    }
                }
                else if (FAILED(hr))
                {
                    OutputDebugStringA("Load Failed\n");
                }
            }
        }
    }
    CheckSize();
}

void ImageList::SizeError() {
    ImGui::SetNextWindowSize(ImVec2(500, 200));
    ImGui::OpenPopup("画像設定失敗");
    if (ImGui::BeginPopupModal("画像設定失敗", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("");
        ImGui::Text("画像サイズは高さ・幅どちらも偶数サイズである必要があります");
        ImGui::Text("");
        float buttonWidth = 100.0f;
        float spacing = ImGui::GetStyle().ItemSpacing.x;

        float totalWidth = buttonWidth  + spacing;

        float startX = (ImGui::GetContentRegionAvail().x - totalWidth) * 0.5f;

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + startX);

        if (ImGui::Button("OK", ImVec2(buttonWidth, 50)))
        {
            PopUpSizeError = false;
        }

        ImGui::EndPopup();
    }
}


void ImageList::ImageDataUpdate() {
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.4f, 0.0f, 1.0f, 1.0f));

    if (ImGui::Button("+", ImVec2(ImGui::GetContentRegionAvail().x, 100)))
    {
        SetImageData(OpenImageFilesW());
    }

    if (sizeMismatch) {
        ImGui::Text("注意!");
        ImGui::Text("画像のサイズが統一されていません");
        ImGui::Text("想定外の事が起きる可能性があります");
    }

    for (size_t i = 0; i < simagePath.size(); i++)
    {
        ImGui::PushID((int)i);

        if (!simagePath[i].texture && simagePath[i].imagePaths != L"NoData") {
            if (ImGui::Button("画像読み込み失敗", ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, 100))) {
                SetImageData((int)i, OpenImageFileW());
            }
        }
        else if (!simagePath[i].texture) {
            if (ImGui::Button("NoData", ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, 100))) {
                SetImageData((int)i, OpenImageFileW());
            }
        }
        else {
            if (ImGui::ImageButton("Image", (ImTextureID)simagePath[i].texture.Get(), SetSize(simagePath[i])))
            {
                SetImageData((int)i, OpenImageFileW());
            }
        }

        ImGui::SameLine();
        ImGui::BeginGroup();

        if (ImGui::Button("X"))
        {
            simagePath.erase(simagePath.begin() + i);
            CheckSize();
            ImGui::PopID();
            ImGui::EndGroup();
            break;
        }

        ImGui::PopID();

        ImGui::EndGroup();
    }

    if (PopUpSizeError)SizeError();
    ImGui::PopStyleColor();
}

bool ImageList::GetTextureSize(ID3D11ShaderResourceView* srv,UINT& width,UINT& height)
{
    if (!srv)
        return false;

    Microsoft::WRL::ComPtr<ID3D11Resource> resource;
    srv->GetResource(resource.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    if (FAILED(resource.As(&texture)))
        return false;

    D3D11_TEXTURE2D_DESC desc;
    texture->GetDesc(&desc);

    width = desc.Width;
    height = desc.Height;

    return true;
}

ImVec2 ImageList::SetSize(const sImagePath& imagePath)
{
    if (imagePath.textureWidth == 0 || imagePath.textureHeight == 0)
    {
        return ImVec2(0.0f, 0.0f);
    }

    float maxWidth = ImGui::GetContentRegionAvail().x * 0.8f;

    float Scale = std::min(
        maxWidth / static_cast<float>(imagePath.textureWidth),
        MAXHEIGHT / static_cast<float>(imagePath.textureHeight));

    return ImVec2(imagePath.textureWidth * Scale,imagePath.textureHeight * Scale);
}

const std::vector<sImagePath>& ImageList::GetImagePaths() {
    return simagePath;
}

void ImageList::ConfigUpdate() {
    ImGui::Text("プレビュー");
    

    float size = ImGui::GetContentRegionAvail().x * 0.8f;
    ImVec2 previewSize(size, size);

    ImVec2 previewPos = ImGui::GetCursorScreenPos();

    ImDrawList* previewdraw = ImGui::GetWindowDrawList();

    ImGui::InvisibleButton("PreviewArea", previewSize); //レイアウト領域確保

    previewdraw->AddRect(previewPos, ImVec2(previewPos.x + previewSize.x, previewPos.y + previewSize.y), IM_COL32(180, 180, 180, 255));

    ChangeCurrentFrame();
    
    if (currentImageFrame < simagePath.size()) {
        float previewscale = std::min(previewSize.x / simagePath[currentImageFrame].textureWidth, previewSize.y / simagePath[currentImageFrame].textureHeight);

        ImVec2 imageSize(simagePath[currentImageFrame].textureWidth * previewscale, simagePath[currentImageFrame].textureHeight * previewscale);
        ImVec2 imagePos(previewPos.x + (previewSize.x - imageSize.x) * 0.5f, previewPos.y + (previewSize.y - imageSize.y) * 0.5f);
        previewdraw->AddImage((ImTextureID)simagePath[currentImageFrame].texture.Get(),imagePos,ImVec2(imagePos.x + imageSize.x,imagePos.y + imageSize.y));
    }

    ScalePreview();

    SetFrameMS();
    SetScale();
    SetLoopButton();
}


void ImageList::ChangeCurrentFrame() {
    if ((float)m_timer->GetTotalSeconds() - lastTime >= (simageData.frameMs/1000.0) && CheckImage())
    {
        lastTime = (float)m_timer->GetTotalSeconds();
        setCurrentFrame();
    }
}

bool ImageList::CheckImage() {
    for (auto& Path : simagePath) {
        if (Path.texture != nullptr) {
            return true;
        }
    }
    return false;
}

bool ImageList::CheckImagePath() {
    for (auto& Path : simagePath) {
        if (Path.imagePaths != L"NoData") {
            return true;
        }
    }
    return false;
}

void ImageList::setCurrentFrame() {
    int iniFrame = currentImageFrame;
    for (int i = 0; i<simagePath.size(); i++) {
        if (iniFrame + 1 >= simagePath.size()) {
            iniFrame = 0;
        }
        else {
            iniFrame++;
        }

        if (simagePath[iniFrame].texture != nullptr) {
            currentImageFrame = iniFrame;
            break;
        }
    }
}

void ImageList::ScalePreview() {
    if (ImGui::Button("スケールプレビュー", ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, 50))) {
        if(CheckImage())scalePreviewSetUp = true;
    }

    if (scalePreviewSetUp) {
        ImGui::SetNextWindowSize(ImVec2(400, 220));
        ImGui::OpenPopup("スケールプレビューSetUp");
        if (ImGui::BeginPopupModal("スケールプレビューSetUp", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("次に進むと実際のサイズを確認する事が出来ます");
            ImGui::Text("Escapeキーを押すと戻ることが出来ます");
            ImGui::Text("全画面での表示をお勧めします");
            ImGui::Text("");
            float buttonWidth = 100.0f;
            float spacing = ImGui::GetStyle().ItemSpacing.x;

            float totalWidth = buttonWidth * 2 + spacing;

            float startX = (ImGui::GetContentRegionAvail().x - totalWidth) * 0.5f;

            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + startX);

            if (ImGui::Button("戻る(ESC)", ImVec2(buttonWidth, 50)))
            {
                scalePreviewSetUp = false;
            }
            if (IsKeyReleased(VK_ESCAPE)) {
                scalePreviewSetUp = false;
            }

            ImGui::SameLine();

            if (ImGui::Button("OK(Enter)", ImVec2(buttonWidth, 50)))
            {
                scalePreviewSetUp = false;
                scalePreview      = true;
            }
            if (IsKeyReleased(VK_RETURN)) {
                scalePreviewSetUp = false;
                scalePreview      = true;
            }

            ImGui::EndPopup();
        }
    }

    if (scalePreview) {
        ImGui::OpenPopup("スケールプレビュー");
        if (ImGui::BeginPopupModal(
            "スケールプレビュー",
            nullptr,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar
            ))
        {
            float width = static_cast<float>(simagePath[currentImageFrame].textureWidth) * simageData.scale;
            float height = static_cast<float>(simagePath[currentImageFrame].textureHeight) * simageData.scale;
            ImVec2 avail = ImGui::GetContentRegionAvail();

            // ウィンドウサイズを画像サイズに合わせる
            ImVec2 padding = ImGui::GetStyle().WindowPadding;

            float title = ImGui::GetFrameHeight();

            ImGui::SetWindowSize(ImVec2(width + padding.x * 2,height + padding.y * 2 + title));

            ImGui::Image((ImTextureID)simagePath[currentImageFrame].texture.Get(),ImVec2(width, height));

            if (IsKeyReleased(VK_ESCAPE))
            {
                ImGui::CloseCurrentPopup();
                scalePreview = false;
            }

            ImGui::EndPopup();
        }
    }
}

void ImageList::SetFrameMS() {
    ImGui::Text("");

    ImGui::Text("FrameMS");
    ImGui::SliderInt("##NextFrameMsSlider", &simageData.frameMs, 1, 300);
    ImGui::SameLine();
    ImGui::InputInt("##NextFrameMsInput", &simageData.frameMs, 1, 300);
    simageData.frameMs = std::clamp(simageData.frameMs, 1, 300);
}

void ImageList::SetScale() {
    ImGui::Text("");
    ImGui::Text("Scale　※スケールプレビューを元に調整してください");
    ImGui::SliderFloat("##ScaleSlider", &simageData.scale, 0.01f, 2.00f, "%.2f");
    ImGui::SameLine();
    ImGui::InputFloat("##ScaleInput", &simageData.scale, 0.01f, 2.00f, "%.2f");
    simageData.scale = std::clamp(simageData.scale, 0.1f, 2.0f);
}

void ImageList::SetLoopButton() {
    ImGui::Text("");
    ImGui::Text("ループ");
    if (GetKey() == "IDLE") {
        ImGui::Text("※IDLEはループON固定です");
    }
    if (ImGui::RadioButton("ON", simageData.loop))if (GetKey() != "IDLE")simageData.loop = true;
    ImGui::SameLine();
    if (ImGui::RadioButton("OFF", !simageData.loop))if (GetKey() != "IDLE")simageData.loop = false;
}

bool ImageList::GIFchecks(std::vector<std::wstring> paths) {

    if (GIFALLCheck()) {
        if (simagePath.size() != 0) {
            std::wstring message = L"GIF画像と他の種類の画像を混ぜることは出来ません\nまたはGIF画像を二つ以上くっつけることは出来ません\n";
            MessageBoxW(NULL, message.c_str(), L"Error", MB_OK);
            return true;
        }
    }
    
    for (auto& Image : paths) {
        if (substrBack(WStringToString(Image), 3, 3) == "gif") {
            if (paths.size() != 1) {
                std::wstring message = L"GIF画像と他の種類の画像を混ぜることは出来ません\nまたはGIF画像を二つ以上くっつけることは出来ません\n";
                MessageBoxW(NULL, message.c_str(), L"Error", MB_OK);
                return true;
            }
            if (simagePath.size() != 0) {
                std::wstring message = L"GIF画像と他の種類の画像を混ぜることは出来ません\nまたはGIF画像を二つ以上くっつけることは出来ません\n";
                MessageBoxW(NULL, message.c_str(), L"Error", MB_OK);
                return true;
            }
        }
    }
    return false;
}

bool ImageList::GIFcheck(std::wstring path) {
    if (substrBack(WStringToString(path), 3, 3) == "gif") {
        if (simagePath.size() != 1) {
            std::wstring message = L"GIF画像と他の種類の画像を混ぜることは出来ません\nまたはGIF画像を二つ以上くっつけることは出来ません\n";
            MessageBoxW(NULL, message.c_str(), L"Error", MB_OK);
            return true;
        }
    }
    return false;
}

bool ImageList::GIFALLCheck() {
    for (auto& Image : simagePath) {
        if (substrBack(WStringToString(Image.imagePaths), 3, 3) == "gif") {
            return true;
        }
    }
    return false;
}