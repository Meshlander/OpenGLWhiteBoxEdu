/* ======================================================
SFile: SoftAccelDisplay.h
SDate: 2021.10.03.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

struct VideoBuffer 
{
	void* Memory;
	BITMAPINFO BitmapInfo;

}VidBuffer[1];

#define WIDTH 640
#define HEIGHT 480
#define BytesPerPixel 4