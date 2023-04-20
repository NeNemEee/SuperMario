#include "Framework.h"
#include "ImageManager.h"

ImageManager* ImageManager::instance = nullptr;

ImageManager::ImageManager()
{
}

ImageManager::~ImageManager()
{
	for (pair<string, ImageInfo*> image : images) {
		delete image.second;
		image.second = nullptr;
	}
}

ImageManager* ImageManager::Get()
{
	if (instance == nullptr)
		instance = new ImageManager;

	return instance;
}

void ImageManager::Delete()
{
	delete instance;
}

bool ImageManager::Add(string key, wstring fileName, Vector2 size, COLORREF color)
{
	if (images.count(key) > 0) {
		return false;
	}

	ImageInfo* temp = new ImageInfo(fileName, (int)size.x, (int)size.y, color);
	images[key] = temp;

	return true;
}

bool ImageManager::Add(string key, wstring fileName, Vector2 size, Vector2 frameSize, COLORREF color)
{
	if (images.count(key) > 0) {
		return false;
	}


	ImageInfo* temp = new ImageInfo(fileName, (int)size.x, (int)size.y, (int)frameSize.x, (int)frameSize.y, color);
	images[key] = temp;
}

bool ImageManager::Add(string key, wstring fileName, Vector2 size, Vector2 frameSize, bool _isBG, COLORREF color)
{
	if (images.count(key) > 0) {
		return false;
	}

	ImageInfo* temp = new ImageInfo(fileName, (int)size.x, (int)size.y, (int)frameSize.x, (int)frameSize.y, color);
	temp->SetBG();
	images[key] = temp;

	return false;
}

/*bool ImageManager::Remove(string key)
{
	if (images.count(key) <= 0) {
		return false;
	}

	delete images[key];
	images.erase(key);
	return true;
}*/

bool ImageManager::Render(HDC hdc, string key, Vector2 pos, POINT curFrame)
{
	if (images.count(key) <= 0) {
		return false;
	}

	if (images[key]->GetIsBG()) {
		images[key]->RenderBG(hdc, pos, curFrame);
	}
	else {
		images[key]->Render(hdc, pos, curFrame);
	}

	

	return true;
}



ImageInfo* ImageManager::Find(string key)
{
	if (images.count(key) <= 0) {
		return nullptr;
	}

	return images[key];
}
