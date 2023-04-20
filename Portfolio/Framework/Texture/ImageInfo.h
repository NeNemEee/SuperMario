#pragma once
class ImageInfo
{
	friend class ImageManager;
private:
	ImageInfo(wstring str, int width, int height, COLORREF transColor = MAGENTA);
	ImageInfo(wstring str, int width, int height, int f_width, int f_height, COLORREF transColor = MAGENTA);
	~ImageInfo();
private:
	void Render(HDC hdc, Vector2 pos, POINT curFrame = { 0,0 });
	void RenderBG(HDC hdc, Vector2 pos, POINT imagePos);
public:
	void SetBG() {
		isBG = true;
	}

	bool GetIsBG() {
		return isBG;
	}

	POINT GetSize() {
		return imageSize;
	};

	POINT GetFrame() {
		return imageFrame;
	};
private:
	HDC memDC = nullptr;
	HBITMAP hBitmap = nullptr;
	POINT imageSize = {};
	POINT imageFrame = {};
	COLORREF color;
	bool isBG = false;
};

