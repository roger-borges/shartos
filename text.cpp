#include "text.h"
#include "materials.h"

text::text(IDirect3DDevice9* *Device)
{
//	default rect, height, width, bold, italic, charset, quality, pitchandfamily, font
	SetRect(&rc,370,270,390,300);
	italic=false;
	fonts=NULL;
	strcpy((char*)font, "Courier New");
	color=materials::WHITE;
	_Device=Device;

		hr = D3DXCreateFont( *_Device,             // D3D device
						rc.bottom-rc.top,      // Height
						rc.right-rc.left,      // Width
						weight->bold,         // Weight
                         1,                    // MipLevels, 0 = autogen mipmaps
                         italic,               // Italic, true or false
                         DEFAULT_CHARSET,      // CharSet
						 precise->default0,    // OutputPrecision
                         ANTIALIASED_QUALITY,  // Quality
                         DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
                         font,                 // pFaceName, like Arial
                         &fonts);              // ppFont, font variable	
//monowidth fonts Lucida Sans Typewriter, Courier New, Lucida Console
}

//this initialize function can be a big memory hog for some reason.
//i suggest this function only be called during setup or as during a settings change
void text::initialize_text()
{  
	hr = D3DXCreateFont( *_Device,             // D3D device
						rc.bottom-rc.top,      // Height
						rc.right-rc.left,      // Width
						weight->bold,         // Weight
                         1,                    // MipLevels, 0 = autogen mipmaps
                         italic,               // Italic, true or false
                         DEFAULT_CHARSET,      // CharSet
						 precise->default0,    // OutputPrecision
                         ANTIALIASED_QUALITY,  // Quality
                         DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
                         font,                 // pFaceName, like Arial
                         &fonts);              // ppFont, font variable	
//	int EnumFontFamiliesEx(HDC,LPLOGFONT,FONTENUMPROC,LPARAM,DWORD);
}
void text::write_text(char* convert_this)
{
	static ID3DXSprite* g_pTextSprite = NULL;
	hr = D3DXCreateSprite( *_Device, &g_pTextSprite ) ;
	fonts->DrawText(NULL,(LPCTSTR)convert_this,-1,&rc, DT_NOCLIP,color);
	g_pTextSprite->Release();
}
void text::write_text_hover(char* convert_this)
{
	static ID3DXSprite* g_pTextSprite = NULL;
	hr = D3DXCreateSprite( *_Device, &g_pTextSprite ) ;
	fonts->PreloadText( convert_this,-1);
	fonts->DrawText(NULL,(LPCTSTR)convert_this,-1,&rc,DT_NOCLIP,D3DXCOLOR( 1.0f, 0.0f, 0.0f, 1.0f ));
	g_pTextSprite->Release();
}
bool text::is_hover(int x_mouse,int y_mouse, char* name)
{
	if(x_mouse>=rc.left && x_mouse<=get_left()+(get_right()*strlen(name)) && y_mouse+15>=rc.top && y_mouse+15<=rc.bottom)
	{write_text_hover(name); return true;}
	return false;
}
void text::set_font(char* fname)
{
for(int i = 0; i < 32; i++)
   font[i] = (TCHAR) fname[i];

	initialize_text();
}
void text::set_color(D3DXCOLOR temp)
{
	color=temp;
}
void text::set_position(int x, int y)
{
	int tempH=rc.bottom-rc.top, tempW=rc.right=rc.bottom;
	rc.top=x; rc.left=y; rc.bottom=rc.top+tempH; rc.right=rc.left+tempW;
}
void text::set_hw(int h,int w)//big memory hog, call sparingly
{
	rc.bottom=rc.top+h; rc.right=rc.left+w;
	initialize_text();//this is why its a big memory hog
}
void text::set_box(int left, int top, int right, int bottom)//big memory hog, call sparingly
{
	rc.left=left; rc.top=top; rc.right=right; rc.bottom=bottom;
	initialize_text();//this is why its a big memory hog
}
void text::get_box(int *left, int *top, int *right, int *bottom)
{
	*left=rc.left; *right=rc.right;
	*top=rc.top; *bottom=rc.bottom;
}
int text::get_left(){return rc.left;} int text::get_right(){return rc.right-rc.left;}
int text::get_top(){return rc.top;} int text::get_bottom(){return rc.bottom;}

void text::set_italic(bool x)
{
	italic=x;
	initialize_text();
}