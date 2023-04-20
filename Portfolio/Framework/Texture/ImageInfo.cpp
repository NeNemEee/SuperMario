#include "Framework.h"
#include "ImageInfo.h"

ImageInfo::ImageInfo(wstring str, int width, int height, COLORREF transColor)
{
    HDC hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    ReleaseDC(hWnd, hdc);

    hBitmap = (HBITMAP)LoadImage(hInst, str.c_str(), IMAGE_BITMAP,
        width, height, LR_LOADFROMFILE);
    imageSize = { width, height };
    imageFrame = imageSize;
    color = transColor;
}

ImageInfo::ImageInfo(wstring str, int width, int height, int f_width, int f_height, COLORREF transColor)
{
    HDC hdc = GetDC(hWnd);
    memDC = CreateCompatibleDC(hdc);
    ReleaseDC(hWnd, hdc);

    hBitmap = (HBITMAP)LoadImage(hInst, str.c_str(), IMAGE_BITMAP,
        width, height, LR_LOADFROMFILE);
    imageSize = { width, height };
    imageFrame = {f_width, f_height};
    color = transColor;
}

ImageInfo::~ImageInfo()
{
    if (memDC != nullptr) {
        DeleteDC(memDC);
    }

    if (hBitmap != nullptr) {
        DeleteObject(hBitmap);
    }
}

void ImageInfo::Render(HDC hdc, Vector2 pos, POINT curFrame)
{
    SelectObject(memDC, hBitmap);
    GdiTransparentBlt(
        hdc,
        (int)(pos.x), (int)(pos.y),
        (int)(imageFrame.x), (int)(imageFrame.y),
        memDC,
        imageFrame.x * curFrame.x, imageFrame.y * curFrame.y,
        imageFrame.x, imageFrame.y,
        color
    );
}

void ImageInfo::RenderBG(HDC hdc, Vector2 pos, POINT imagePos)
{
    SelectObject(memDC, hBitmap);
    GdiTransparentBlt(
        hdc,
        0, 0,
        (int)(imageFrame.x), (int)(imageFrame.y),
        memDC,
        imagePos.x, imagePos.y,
        imageFrame.x, imageFrame.y,
        color
    );
}
