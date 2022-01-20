/* ======================================================
SFile: SoftAccelDisplay.cpp
SDate: 2021.10.03.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

void StartVideoBuffer() 
{
	VidBuffer->Memory = VirtualAlloc(0, WIDTH*HEIGHT*BytesPerPixel, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
	VidBuffer->BitmapInfo.bmiHeader.biSize = sizeof(VidBuffer->BitmapInfo.bmiHeader);
	VidBuffer->BitmapInfo.bmiHeader.biWidth = WIDTH;
	VidBuffer->BitmapInfo.bmiHeader.biHeight = HEIGHT;
	VidBuffer->BitmapInfo.bmiHeader.biPlanes = 1;
	VidBuffer->BitmapInfo.bmiHeader.biBitCount = BytesPerPixel * 8;
	VidBuffer->BitmapInfo.bmiHeader.biCompression = BI_RGB;
}

inline void UpdateBuffer(HDC hdc) 
{
	StretchDIBits(
		hdc,
		0,
		0,
		WIDTH,
		HEIGHT,
		0,
		0,
		WIDTH,
		HEIGHT,
		VidBuffer->Memory,
		&VidBuffer->BitmapInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
}

