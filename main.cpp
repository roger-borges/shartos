//#define WIN32_LEAN_AND_MEAN  // just say no to MFC

//#include "includes.h"
//#include "engine.h"
//#include "includes.h"
#include <d3dx9.h>
#include "game.h"

#define WINDOW_WIDTH      800	
//800
#define WINDOW_HEIGHT     600
//600

game* thegame=new game();

void Game_Init()
{
	thegame->initialize();
} 
void Game_Main()
{
	thegame->run();
}

void Game_Shutdown()
{
	thegame->ReleaseDevice();
} 

// FUNCTIONS //////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, 
						    UINT msg, 
                            WPARAM wparam, 
                            LPARAM lparam)
{
	// this is the main message handler of the system
	PAINTSTRUCT		ps;		// used in WM_PAINT
	HDC				hdc;	// handle to a device context

	// what is the message 
switch(msg)
	{	
	case WM_CREATE: 
        {
		// do initialization stuff here
        // return success
		return(0);
		} break;
   case WM_KEYDOWN:
		if( wparam == VK_ESCAPE )
			::DestroyWindow(hwnd);
		break;
	case WM_PAINT: 
		{
		// simply validate the window 
   	    hdc = BeginPaint(hwnd,&ps);	 
        
        // end painting
        EndPaint(hwnd,&ps);

        // return success
		return(0);
   		} break;
	case WM_DESTROY: 
		{

		// kill the application, this sends a WM_QUIT message 
		PostQuitMessage(0);

        // return success
		return(0);
		} break;

	default:break;

    } 

// process any messages that we didn't take care of 
return (DefWindowProc(hwnd, msg, wparam, lparam));

} 



// WINMAIN ////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance,
					HINSTANCE hprevinstance,
					LPSTR lpcmdline,
					int ncmdshow)
{

IDirect3DDevice9*     Device = 0;
//D3DADAPTER_IDENTIFIER9 adapter;


WNDCLASSEX winclass; // this will hold the class we create
HWND	   hwnd;	 // generic window handle
MSG		   msg;		 // generic message

// first fill in the window class stucture
winclass.cbSize         = sizeof(WNDCLASSEX);
winclass.style			= CS_DBLCLKS | CS_OWNDC | 
                          CS_HREDRAW | CS_VREDRAW;
winclass.lpfnWndProc	= WindowProc;
winclass.cbClsExtra		= 0;
winclass.cbWndExtra		= 0;
winclass.hInstance		= hinstance;
winclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
winclass.hCursor		= LoadCursor(NULL, IDC_ARROW); 
winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
winclass.lpszMenuName	= NULL;
winclass.lpszClassName	= "WINCLASS1";
winclass.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);



// register the window class
if (!RegisterClassEx(&winclass))
	return(0);

// create the window
if (!(hwnd = CreateWindowEx(NULL,                  // extended style
                            "WINCLASS1",     // class
							"Shartos: A New Era", // title
						    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					 	    0,0,	  // initial x,y
						    WINDOW_WIDTH ,WINDOW_HEIGHT,  // initial width, height
						    NULL,	  // handle to parent 
						    NULL,	  // handle to menu
						    hinstance,// instance of this application
						    NULL)))	// extra creation parms
return(0);

	//Update the window
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

//////////////////////INITILIZE Direct3D/////////////////////////////
	HRESULT hr=0;
	IDirect3D9* d3d9;
	
	d3d9=Direct3DCreate9(D3D_SDK_VERSION);
	//If failed 
	if(!d3d9)
	{
		MessageBox(0, "Direct3DCreate9() - FAILED", 0, 0);
	}
	//thegame->set_d3d9(d3d9);
	/////CHECK for HARDWARE CAPABILITIES/////////////////////
	D3DCAPS9 caps;
	//use the main Video card, use HArdware to render.
	d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int vp=0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	//fill in the D3DPRESENT_PARAMETERS structure, all teh DX options go here
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth            = WINDOW_WIDTH;
	d3dpp.BackBufferHeight           = WINDOW_HEIGHT;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hwnd;
	d3dpp.Windowed                   = true;	//run in window mode
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;

	//Creat the Device, this is what we will use to render everything
	hr = d3d9->CreateDevice(
		D3DADAPTER_DEFAULT, // primary adapter
		D3DDEVTYPE_HAL,         // device type
		hwnd,               // window associated with device
		vp,                 // vertex processing
	    &d3dpp,             // present parameters
	    &Device);

	thegame->setDevice(Device);

	//if 24bit depth buffer doesnt work use 16bit
	if( FAILED(hr) )
	{
		// try again using a 16-bit depth buffer
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		
		hr = d3d9->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hwnd,
			vp,
			&d3dpp,
			&Device);

		//thegame->store_present_parameters(d3dpp);
		//send error message if 16bit doesnt work either
		if( FAILED(hr) )
		{
			d3d9->Release(); // done with d3d9 object
			MessageBox(0, "CreateDevice() - FAILED", 0, 0);
			return false;
		}
	}
	d3d9->Release();
////////////DONE WITH Direct3D stuff.///////////////////////////////////////

// initialize game here////////////////////////
Game_Init();

// enter main event loop
while(TRUE)
	{
    // test if there is a message in queue, if so get it
	if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	   { 
	   // test if this is a quit
       if (msg.message == WM_QUIT)
           break;
	
	   // translate any accelerator keys
	   TranslateMessage(&msg);

	   // send the message to the window proc
	   DispatchMessage(&msg);
	   } // end if
    
       // main game processing goes here
       Game_Main();
       
	} // end while

	// closedown game here
	Game_Shutdown();

// return to Windows like this
return(msg.wParam);

} // end WinMain
