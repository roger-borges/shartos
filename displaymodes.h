#include<d3dx9.h>
#include "text.h"

class displayMode{
private:
	char* currentFormat;
	D3DFORMAT currD3DFormat;
	int height;
	int width;
	int refresh;
	char* bytesPerPixel;
	int BPP;
	char* settings;//string to be rendered
	IDirect3DDevice9* _device;
	text* disp_the_mode;

	
public:
//	text* disp_the_mode;
	displayMode(IDirect3DDevice9*,int,int,D3DFORMAT,int,int,int,int);
	bool draw(int,int);
	D3DFORMAT get_format(){return currD3DFormat;}
	int get_height(){return height;}
	int get_width(){return width;}
	LPDEVMODE get_dev_mode();

};
