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
    for (auto& Path : simagePath) {
        if (Path.imagePaths != L"") {
            HRESULT hr = DirectX::CreateWICTextureFromFile(
                deviceResources->GetD3DDevice(),
                Path.imagePaths.c_str(),
                nullptr,
                Path.texture.GetAddressOf());
            if (FAILED(hr))
            {
                OutputDebugStringA("Load Failed\n");
            }
        }
    }
}


void ImageList::ResetAllImage() {
    for (auto& Path : simagePath) {
        if (Path.texture != nullptr) {
            Path.texture.Reset();
        }
    }
}

void ImageList::SetImageData(int Vector,std::wstring path) {
    if (path != L"") {
        simagePath[Vector].imagePaths = path;
        simagePath[Vector].texture.Reset();
        if (simagePath[Vector].imagePaths != L"NoData") {
            simagePath[Vector].texture.Reset();
            HRESULT hr = DirectX::CreateWICTextureFromFile(
                deviceResources->GetD3DDevice(),
                path.c_str(),
                nullptr,
                simagePath[Vector].texture.GetAddressOf());
            if (SUCCEEDED(hr)) {
                GetTextureSize(simagePath[Vector].texture.Get(), simagePath[Vector].textureWidth, simagePath[Vector].textureHeight);
            }
            else if (FAILED(hr))
            {
                OutputDebugStringA("Load Failed\n");
            }
        }
    }
}


void ImageList::Update() {
    if (ImGui::Button("+", ImVec2(ImGui::GetContentRegionAvail().x, 100)))
    {
        simagePath.push_back({ });
        SetImageData((int)simagePath.size() - 1, OpenImageFileW());
    }

    for (size_t i = 0; i < simagePath.size(); i++)
    {
        ImGui::PushID((int)i);

        if (!simagePath[i].texture) {
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
            ImGui::PopID();
            ImGui::EndGroup();
            break;
        }

        ImGui::PopID();

        ImGui::EndGroup();
    }


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

