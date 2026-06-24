#pragma once
#include <String>
#include <memory>
#include <Vector>
#include "Windows.h"

#include <wrl/client.h>
#include <d3d11.h>
#include "DeviceResources.h"

using Microsoft::WRL::ComPtr;

#define IDLE 256

struct sImagePath
{
	std::string imagePaths = "NoData";
	ComPtr<ID3D11ShaderResourceView> texture;
};

class ImageList {
private:
	int vkey = IDLE;

	std::vector<sImagePath> simagePath;

	float scale = 1.0f;

	float interval = 100;

	bool loop = true;

	DX::DeviceResources* deviceResources;
public:
	ImageList(DX::DeviceResources* DeviceResources):deviceResources(DeviceResources){}
	~ImageList(){}

	std::string GetKey();
	void SetKey(int setKey);
	bool IsNormal() { return GetKey() != "不明"; }

	void SetAllImage();
	void ResetAllImage();
	void SetImageData(int Vector, std::string path);

	void Update();
};