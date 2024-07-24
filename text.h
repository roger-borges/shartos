#ifndef __textH__
#define __textH__

//#include "engine.h"
//#include "includes.h"
#include <d3dx9.h>

class text{
private:
	float x_pos, y_pos;
	bool italic;
	TCHAR font[32];
	RECT rc;
	ID3DXFont* fonts;
	HRESULT  hr;
	D3DXCOLOR color;
	IDirect3DDevice9* *_Device;
	class weighs{
	public:
				static const int dontCare=FW_DONTCARE;
				static const int thin=FW_THIN;
				static const int extraLight=FW_EXTRALIGHT; 
				static const int ultraLight=FW_ULTRALIGHT; 
				static const int light=FW_LIGHT; 
				static const int normal=FW_NORMAL;
				static const int regular=FW_REGULAR;
				static const int medium=FW_MEDIUM;
				static const int semiBold=FW_SEMIBOLD;
				static const int demiBold=FW_DEMIBOLD;
				static const int bold=FW_BOLD;
				static const int extraBold=FW_EXTRABOLD; 
				static const int ultraBold=FW_ULTRABOLD;
				static const int heavy=FW_HEAVY;
				static const int black=FW_BLACK;
	};

	class precision{
		public:
			static const int outChar=OUT_CHARACTER_PRECIS;
			static const int default0=OUT_DEFAULT_PRECIS;
			static const int deviceChoose=OUT_DEVICE_PRECIS;
			static const int outline=OUT_OUTLINE_PRECIS;
			static const int postScript=OUT_PS_ONLY_PRECIS;
			static const int rasterFont=OUT_RASTER_PRECIS;
			static const int enumerated=OUT_STRING_PRECIS;
			static const int stroke=OUT_STROKE_PRECIS;
			static const int onlyTrueType=OUT_TT_ONLY_PRECIS;
			static const int trueType=OUT_TT_PRECIS;
	};
public:
	text(IDirect3DDevice9* *Device);
	void initialize_text();
	void write_text(char*);
	void write_text_hover(char*);
	void set_font(char*);
	void set_color(D3DXCOLOR);
	void set_position(int, int);
	void set_hw(int,int);
	void set_box(int left, int top, int right, int bottom);
	void get_box(int *left, int *top, int *right, int *bottom);
	int get_left(); int get_right();
	int get_top(); int get_bottom();
	bool is_hover(int,int, char*);
	void set_italic(bool);
	weighs* weight;
	precision* precise;	
};

/*
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
	LPDEVMODE get_dev_mode();

};
*/



#endif

/*output precision
OUT_CHARACTER_PRECIS Not used. 
OUT_DEFAULT_PRECIS Specifies the default font mapper behavior. 
OUT_DEVICE_PRECIS Instructs the font mapper to choose a Device font when the system contains multiple fonts with the same name. 
OUT_OUTLINE_PRECIS Windows NT/2000/XP: This value instructs the font mapper to choose from TrueType and other outline-based fonts. 
OUT_PS_ONLY_PRECIS Windows 2000/XP: Instructs the font mapper to choose from only PostScript fonts. If there are no PostScript fonts installed in the system, the font mapper returns to default behavior. 
OUT_RASTER_PRECIS Instructs the font mapper to choose a raster font when the system contains multiple fonts with the same name. 
OUT_STRING_PRECIS This value is not used by the font mapper, but it is returned when raster fonts are enumerated. 
OUT_STROKE_PRECIS Windows NT/2000/XP: This value is not used by the font mapper, but it is returned when TrueType, other outline-based fonts, and vector fonts are enumerated. 
Windows 95:This value is used to map vector fonts, and is returned when TrueType or vector fonts are enumerated. 
 
OUT_TT_ONLY_PRECIS Instructs the font mapper to choose from only TrueType fonts. If there are no TrueType fonts installed in the system, the font mapper returns to default behavior. 
OUT_TT_PRECIS Instructs the font mapper to choose a TrueType font when the system contains multiple fonts with the same name. 
*/

/*pitchandfamily
DEFAULT_PITCH
FIXED_PITCH
VARIABLE_PITCH 

Bits 4 through 7 of the member specify the font family and can be one of the following values. 

FF_DECORATIVE
FF_DONTCARE
FF_MODERN
FF_ROMAN
FF_SCRIPT
FF_SWISS 

The proper value can be obtained by using the Boolean OR operator to join one pitch constant with one family constant. 

Font families describe the look of a font in a general way. They are intended for specifying fonts when the exact typeface desired is not available. The values for font families are as follows. Value Meaning 
FF_DECORATIVE Novelty fonts. Old English is an example. 
FF_DONTCARE Use default font. 
FF_MODERN Fonts with constant stroke width (monospace), with or without serifs. Monospace fonts are usually modern. Pica, Elite, and CourierNew are examples. 
FF_ROMAN Fonts with variable stroke width (proportional) and with serifs. MS Serif is an example. 
FF_SCRIPT Fonts designed to look like handwriting. Script and Cursive are examples. 
FF_SWISS Fonts with variable stroke width (proportional) and without serifs. MS Sans Serif is an example. 

*/

/*quality
ANTIALIASED_QUALITY Windows NT 4.0 and later: Font is always antialiased if the font supports it and the size of the font is not too small or too large. 
Windows 95 Plus!, Windows 98/Me: The display must greater than 8-bit color, it must be a single plane device, it cannot be a palette display, and it cannot be in a multiple display monitor setup. In addition, you must select a TrueType font into a screen DC prior to using it in a DIBSection, otherwise antialiasing does not occur.
 
CLEARTYPE_QUALITY Windows XP: If set, text is rendered (when possible) using ClearType antialiasing method. See Remarks for more information. 
DEFAULT_QUALITY Appearance of the font does not matter. 
DRAFT_QUALITY Appearance of the font is less important than when PROOF_QUALITY is used. For GDI raster fonts, scaling is enabled, which means that more font sizes are available, but the quality may be lower. Bold, italic, underline, and strikeout fonts are synthesized if necessary. 
NONANTIALIASED_QUALITY Windows 95/98/Me, Windows NT 4.0 and later: Font is never antialiased. 
PROOF_QUALITY 
*/