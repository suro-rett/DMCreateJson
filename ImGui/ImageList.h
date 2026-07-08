#pragma once
#include <String>
#include <memory>
#include <Vector>
#include "Windows.h"

#include <wrl/client.h>
#include <d3d11.h>
#include "DeviceResources.h"
#include "imgui.h"
#include "StepTimer.h"

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

struct sImageData
{
	int frameMs = 75;
	float scale = 1.0f;
	bool loop = true;
};

class ImageList {
private:
	int vkey = IDLE;

	std::vector<sImagePath> simagePath;
	sImageData simageData;

	DX::DeviceResources* deviceResources;
	DX::StepTimer* m_timer;
#pragma region イメージデータ(真ん中)
	bool PopUpSizeError = false;//画像リストで新しく選んだ画像が奇数サイズじゃないかチェック
	bool sizeMismatch = false;	//画像リストの各画像サイズチェック

	bool GetTextureSize(ID3D11ShaderResourceView* srv, UINT& width, UINT& height);
	ImVec2 SetSize(const sImagePath& imagePath);
	void SizeError();
	void CheckSize();
#pragma endregion
#pragma region プレビュー
	int currentImageFrame = 0;	//プレビュー画面で流すフレーム
	float lastTime = 0;
	void ChangeCurrentFrame();
	bool CheckImage();
	void setCurrentFrame();
#pragma endregion
#pragma region スケールプレビュー
	void ScalePreview();
	bool scalePreviewSetUp = false;
	bool scalePreview = false;
#pragma endregion

	void SetFrameMS();
	void SetScale();
	void SetLoopButton();

	int e = 0;
public:
	ImageList(DX::DeviceResources* DeviceResources, DX::StepTimer* time):deviceResources(DeviceResources), m_timer(time){}
	~ImageList(){}

	std::string GetKey();
	void SetKey(int setKey);
	bool IsNormal() { return GetKey() != "不明"; }

	const std::vector<sImagePath>& GetImagePaths();
	void SetAllImage();
	void ResetAllImage();
	void SetImageData(int Vector, std::wstring path);

	void ImageDataUpdate();
	void ConfigUpdate();
	void SetLoop(bool aloop) { simageData.loop = aloop; }
};