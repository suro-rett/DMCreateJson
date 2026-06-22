#pragma once
#include <String>
#include <memory>
#include <Vector>
#include "Windows.h"

#define IDLE 256

class ImageList {
private:
	int key = IDLE;

	std::vector<std::string> imagePaths;

	float scale = 1.0f;

	float interval = 100;

	bool loop = true;
public:
	ImageList(){}
	~ImageList(){}

	std::string GetKey();
};