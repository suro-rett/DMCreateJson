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
};