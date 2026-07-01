#pragma once
#include <String>
#include <memory>
#include <Vector>
#include "Windows.h"

#include <wrl/client.h>
#include <d3d11.h>
#include "DeviceResources.h"
#include "imgui.h"

using Microsoft::WRL::ComPtr;
#define MAXHEIGHT 300.0f

#define IDLE 256

struct sImagePath
{
	std::wstring imagePaths = L"NoData";
	ComPtr<ID3D11ShaderResourceView> texture;

	UINT textureWidth  = 0;
	UINT textureHeight = 0;

};

class ImageList {
private:
	int vkey = IDLE;

	std::vector<sImagePath> simagePath;

	float scale = 1.0f;

	float interval = 100;

	bool loop = true;

	bool PopUpSizeError = false;

	bool sizeMismatch = false;

	DX::DeviceResources* deviceResources;
	bool GetTextureSize(ID3D11ShaderResourceView* srv, UINT& width, UINT& height);
	ImVec2 SetSize(const sImagePath& imagePath);
	void SizeError();
	void CheckSize();
public:
	ImageList(DX::DeviceResources* DeviceResources):deviceResources(DeviceResources){}
	~ImageList(){}

	std::string GetKey();
	void SetKey(int setKey);
	bool IsNormal() { return GetKey() != "不明"; }

	const std::vector<sImagePath>& GetImagePaths();
	void SetAllImage();
	void ResetAllImage();
	void SetImageData(int Vector, std::wstring path);

	void Update();
};