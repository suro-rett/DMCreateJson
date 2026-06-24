#pragma once
#include "ImageList.h"
#include "DeviceResources.h"
#include "imgui.h"

struct sImageList
{
	bool changeButton = false;
	ImageList  imageList;

	sImageList(DX::DeviceResources* deviceResources)
		: imageList(deviceResources)
	{
	}
};

class MainScreen
{
public:
	void Update();

	MainScreen(DX::DeviceResources* DeviceResource) :deviceResources(DeviceResource){}
	MainScreen(){}
private:
	void KeyPanel();
	void ImagePanel();
	void ConfigPanel();


	DX::DeviceResources* deviceResources;

	std::vector<sImageList> simageList;

	int choicesImageList = -1;
	//bool choiceNormal = false;

	//ImGui::Textにて表示されるtextをウィンドウの中心に表示する
	void CenterImGuiText(const char* text);
};

//ImFont* SetFontSizeJapanese(float size, ImGuiIO& io, const char* font = "") {
//	ImFont* imFont;
//	if (font == "") {
//		return io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", size, nullptr, io.Fonts->GetGlyphRangesJapanese());
//	}
//	else {
//		return io.Fonts->AddFontFromFileTTF(font, size, nullptr, io.Fonts->GetGlyphRangesJapanese());
//	}
//	return imFont;
//}