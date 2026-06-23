#pragma once
#include "ImageList.h"

struct sImageList
{
	bool changeButton = false;
	ImageList  imageList;
};

class MainScreen
{
public:
	void Update();

private:
	void KeyPanel();
	void ImagePanel();
	void ConfigPanel();

	std::vector<sImageList> simageList;

	int choicesImageList = 0;
	bool choiceNormal = false;

	//ImGui::Textにて表示されるtextをウィンドウの中心に表示する
	void CenterImGuiText(const char* text);
};