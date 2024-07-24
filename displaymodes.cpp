#include "displaymodes.h"
//#include "text.h"


displayMode::displayMode(IDirect3DDevice9* Device,int Width,int Height,D3DFORMAT Format,int RefreshRate,int bpp,int posX,int posY)
{
	height=Height;
	width=Width;
	refresh=RefreshRate;
	currD3DFormat=Format;
	BPP=bpp;
	currentFormat=new char();
			/*	switch(Format)
				{
					case D3DFMT_X1R5G5B5: currentFormat="D3DFMT_X1R5G5B5";break;
					case D3DFMT_A1R5G5B5: currentFormat="D3DFMT_A1R5G5B5";break;
					case D3DFMT_R5G6B5: currentFormat="D3DFMT_R5G6B5";break;
					case D3DFMT_X8R8G8B8: currentFormat="D3DFMT_X8R8G8B8";break;
					case D3DFMT_A8R8G8B8: currentFormat="D3DFMT_A8R8G8B8";break;
					case D3DFMT_A2R10G10B10: currentFormat="D3DFMT_A2R10G10B10";break;
				}*/
	
	char* tempw=new char();
	itoa(width,tempw,10);

	char* tempx=new char();
	strcpy(tempx,"x");

	char* temph=new char();
	itoa(height,temph,10);

	char* tempc=new char();
	strcpy(tempc,", ");

	char* tempb=new char();
	itoa(bpp,tempb,10);
	strcat(tempb," bits");

	settings= new char();
	settings=strcat(tempc,tempb);
	settings=strcat(temph,tempc);
	settings=strcat(tempx,temph);
	settings=strcat(tempw,tempx);
	settings=strcpy(settings,tempw);
	
	_device=Device;

//	text* disp_the_mode;

	disp_the_mode=new text(&_device);
	disp_the_mode->set_box(posX,posY,posX+15,posY+25);
	//disp_the_mode->initialize_text();
	//disp_the_mode->write_text(settings);
	//ChangeDisplaySettings(

}

LPDEVMODE displayMode::get_dev_mode()
{
	LPDEVMODE dev;
	dev->dmBitsPerPel=(DWORD)BPP;
	dev->dmPelsHeight=(DWORD)height;
	dev->dmPelsWidth=(DWORD)width;
	dev->dmDisplayFlags=(DWORD)0;
	dev->dmDisplayFrequency=(DWORD)60;
	dev->dmPosition.x=(LONG)0;
	dev->dmPosition.y=(LONG)0;

	return dev;
//dmBitsPerPel Bits per pixel
//dmPelsWidth Pixel width
//dmPelsHeight Pixel height
//dmDisplayFlags Mode flags
//dmDisplayFrequency Mode frequency
//dmPosition
}

bool displayMode::draw(int x, int y)
{	
	if(disp_the_mode->is_hover(x,y,settings))return true;
	disp_the_mode->write_text(settings);return false;
}