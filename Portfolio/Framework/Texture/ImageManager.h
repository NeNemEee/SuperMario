#pragma once
class ImageManager
{
private:
	ImageManager();
	~ImageManager();
public:
	static ImageManager* Get();
	void Delete();
	bool Add(string key, wstring fileName, Vector2 size, COLORREF color = MAGENTA);
	bool Add(string key, wstring fileName, Vector2 size, Vector2 frameSize, COLORREF color = MAGENTA);
	bool Add(string key, wstring fileName, Vector2 size, Vector2 frameSize, bool _isBG, COLORREF color = MAGENTA);
	//bool Remove(string key);
	bool Render(HDC hdc, string key, Vector2 pos, POINT curFrame = { 0,0 });
	ImageInfo* Find(string key);
private:
	static ImageManager* instance;
	map<string, ImageInfo*> images;
};

