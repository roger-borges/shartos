#include "Game.h"
#include "graphicsSubsystem.h"
#include "physicsSubsystem.h"
#include "inputSubsystem.h"
#include "loadSGSubsystem.h"
#include "soundSubsystem.h"
#include "Quad.h"
//#include "kernel.h"
//#include "Shartos/object.h"
//#include "engine.h"


game::game()
{
	windowWidth=800;
	windowHeight=600;
	D3DXMatrixScaling(&scale,0.05f,0.05f,0.05f);
	D3DXMatrixPerspectiveFovLH(&proj,D3DX_PI * 0.5f, // 90 - degree
								(float)windowWidth / (float)windowHeight, 0.1f,10000.0f);
	//keyMouse=new Input(::GetActiveWindow());

}
game::~game()
{
}
void game::initialize()
{
	_device->SetTransform(D3DTS_PROJECTION, &proj);
	_device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	_device->SetRenderState(D3DRS_SPECULARENABLE, true);
	// Set Texture Filter States.
	_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	
	currentState=mainMenu;
	keyMouse=new Input(::GetActiveWindow());
	mouseclick0=mouseclick1=mouseWheelUp=mouseWheelDown=false;

}
void game::setDevice(IDirect3DDevice9* Device)
{
	_device=Device;
	 object::setDevice(_device);//this device gets set into the object class, which is a friend class
}

void game::mainMenuGui()
{	
	::ShowCursor(TRUE);
	static int i=0;
	static text* title=new text(&_device),* newGame=new text(&_device),
		* settings=new text(&_device), * Credits=new text(&_device), * exitAll=new text(&_device);
	static D3DMATERIAL9 WHITE_MTRL=materials::InitMtrl(materials::WHITE, materials::WHITE, materials::WHITE, materials::WHITE, 2.0f);
	static IDirect3DTexture9* Tex = 0;

	


	if(i==0){
	
		title->set_box(20,20,45,70);
		title->set_font("Colonna MT");
		title->set_color(D3DXCOLOR(49.0f/255.0f,179.0f/255.0f,202.0f/255.0f,0.8f));
		newGame->set_box(370,270,390,300);
		settings->set_box(370,305,390,335);
		Credits->set_box(370,340,390,370);
		exitAll->set_box(370,375,390,405);
		i=i+1;}
	

	title->write_text("Shartos: A New Era");
	newGame->write_text("New Game");
	settings->write_text("Settings");//settings->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"Settings");
	Credits->write_text("Credits");//Credits->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"Credits");
	exitAll->write_text("Exit");//exitAll->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"Exit");

	if(newGame->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"New Game") && keyMouse->GetButtonPress(0))currentState=mapsMenu;
	else if(settings->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"Settings") && keyMouse->GetButtonPress(0))currentState=Settings;
	else if(Credits->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"Credits") && keyMouse->GetButtonPress(0))currentState=Settings;
	else if(exitAll->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),"Exit") && keyMouse->GetButtonPress(0))currentState=Exit;
}
void game::exitFunc()
{
	//stop drawing
//	_device->EndScene();
//	_device->Present(0, 0, 0, 0);//Present the back buffer to front
//	_device->Release();
	::CloseWindow(::GetActiveWindow());
	PostQuitMessage(WM_QUIT);
//	exit(1);
	//	return;
}
void game::inGameExitFunc()
{
}
void game::inGameMenuGui()
{
}
void game::settingsGui()
{
	displays();
}
void game::inGameFunc()
{
	_kernel->executeNextSubsystem();

}

void game::run()
{
	//static Quad* Box = new Quad(_device,-1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,0.0f,0.0f,-1.0f);
	static int color=0x11111111;
/*	static int i=0;
	if(i==0)
	{
		IDirect3DSurface9* cursor_image;
		// Turn off window cursor. 
		SetCursor( NULL );

		_device->ShowCursor(true);

		i++;
	}
*/	keyMouse->Update();
	object::_device->SetTransform(D3DTS_VIEW, &V);

	object::_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f, 0);
	object::_device->BeginScene();
	object::_device->SetTransform(D3DTS_WORLD,&scale);
	object::_device->SetMaterial(&materials::WHITE_MTRL);
	//begin drawing

	switch(currentState)
	{
		case mainMenu: mainMenuGui(); break;
		case mapsMenu: mapsMenuGui(); break;
		case inGameMenu: inGameMenuGui();break;
		case Settings: color=0x111111; settingsGui();break;
		case Exit: exitFunc();break;
		case inGameExit: inGameExitFunc();break;
		case inGame: inGameFunc();break;
	}

	//stop drawing
	object::_device->EndScene();
	object::_device->Present(0, 0, 0, 0);//Present the back buffer to front
}

void game::mapsMenuGui()
{

	_kernel = new Kernel();
	_kernel->addScene("ryan",new SceneGraph());
	_kernel->setScene("ryan");
	_kernel->addSubsystem("loadScene",(subSystem*)new loadSGSubsystem("load.xml"));//this would load all world stuff
	_kernel->executeNextSubsystem();
	_kernel->removeSubsystem("loadScene");
	_kernel->addSubsystem("physical",(subSystem*)(new physicsSubsystem()));
	_kernel->addSubsystem("visual",(subSystem*)new graphicsSubsystem());
	_kernel->addSubsystem("input",new inputSubsystem());
	_kernel->addSubsystem("sound",new soundSubsystem());
	currentState = inGame;

	// Set a directional light.															//light
	D3DXCOLOR RE(0.8f, 0.8f, 0.8f, 1.0f);												//light
	D3DXCOLOR RE1(1.0f, 1.0f, 1.0f, 1.0f);												//light
	D3DXCOLOR RE2(0.2f, 0.2f, 0.2f, 1.0f);
	D3DXVECTOR3 VEC(1.0f, -1.0f, 0.0f);  //Direction/Position of the light				//light
	Light World_Light2(object::_device, Light::POINT,true,0,&VEC,&RE,&RE1 ,&RE2,100000.0f,1.0f);	//light






	/*
	static text* exit_string=new text(&_device);
	static maps* map_list=new maps(S"load/maps/worlds.xml");
	static std::list<std::string> map_list_contents;
	static std::list<text> text_map_list;
	static char* name=new char();
	static int position=10;
	static int i=0;
	if(i==0)
	{
		//_d3dpp=_device->PresentParameters;
		//exit_string->set_position(_d3dpp.BackBufferHeight-100,1280-100);
		map_list_contents=map_list->get_name_list();
		std::list<std::string>::iterator liter21;
		for(liter21= map_list_contents.begin(); liter21!=map_list_contents.end();++liter21)
		{
			name=(char*)liter21->c_str();
			static text* title=new text(&_device);
			//title->set_position(position,0); 
			title->set_box(10,position,20,position+20);
			position+=20;
			text_map_list.push_back(*title);
		}
	}

	std::list<std::string>::iterator liter21;
	std::list<text>::iterator liter22;
	liter22=text_map_list.begin();
	for(liter21=map_list_contents.begin(); liter21!=map_list_contents.end();++liter21)
	{	
		if(liter22->is_hover(keyMouse->GetPosX(),keyMouse->GetPosY(),(char*)liter21->c_str()))
		{
			//switch state to load this map...if mouse click, load world
			;
		}
		else liter22->write_text((char*)liter21->c_str());
		++liter22;
	}
	exit_string->write_text("exit");
*/
	}

void game::displays()
{
/*	static std::list<displayMode> displayList;
	static text* title=new text(&_device);
	static text* exit1=new text(&_device);
	D3DDISPLAYMODE a;
			_device->GetDisplayMode(0,&a);
			a.Height;
	static int i=0;
	if(i==0)
	{
		exit1->set_position(0,400);
		displayMode *a;
		static text *adapter_info=new text(&_device); 
			adapter_info->set_position(100,100);
		static D3DADAPTER_IDENTIFIER9 adapter;
			_d3d9->GetAdapterIdentifier(D3DADAPTER_DEFAULT,0,&adapter);
			
				D3DFORMAT allowedFormats[6];
				allowedFormats[0] = D3DFMT_X1R5G5B5;
				allowedFormats[1] = D3DFMT_A1R5G5B5;
				allowedFormats[2] = D3DFMT_R5G6B5;
				allowedFormats[3] = D3DFMT_X8R8G8B8;
				allowedFormats[4] = D3DFMT_A8R8G8B8;
				allowedFormats[5] = D3DFMT_A2R10G10B10;
				

				static char af=2;//there are qty5 w/2,3
					unsigned long totalAdapterModes = _d3d9->GetAdapterModeCount( D3DADAPTER_DEFAULT, allowedFormats[af] );
//			char* a=new char();
				//ltoa(totalAdapterModes,a,10);

				int Y=50;
				for(char af=0; af<=5;af++)
				{	
					
					
					unsigned long totalAdapterModes = _d3d9->GetAdapterModeCount( D3DADAPTER_DEFAULT, allowedFormats[af] );
					for( unsigned long m = 0; m < totalAdapterModes; m++ )
					{
						D3DDISPLAYMODE mode;//this will enumerate device modes for given format
						_d3d9->EnumAdapterModes( D3DADAPTER_DEFAULT, allowedFormats[af], m, &mode );
									// Reject small display modes.
						if( mode.Height < 480 )
							continue;

						// Create the new display mode.
			//			DisplayMode *displayMode = new DisplayMode;
			//			memcpy( &displayMode->mode, &mode, sizeof( D3DDISPLAYMODE ) );
						int bpp=0;
						if( af < 3 ){
							bpp=16;
							a = new displayMode(_device,mode.Width,mode.Height,mode.Format,mode.RefreshRate,bpp,50,Y );
						}else{
							bpp=32;
							a = new displayMode(_device,mode.Width,mode.Height,mode.Format,mode.RefreshRate,bpp, 50,Y );
						}
						Y+=30;
						//add to the list of display modes
						displayList.push_back(*a);	
					}
			}
			title->set_box(10,10,33,40);
			title->set_italic(true);
			title->set_color(D3DXCOLOR(0.0f,0.3f,1.0f,1.0f));
		i++;
	}
	//settins menu is displayed here
	title->write_text("Resolutions and Bits");
	//traverse list of displayModes and draw text
	list<displayMode>::iterator liter;
	for(liter =  displayList.begin(); liter != displayList.end(); ++liter)
	{
		if(liter->draw((int)keyMouse->GetPosX(),(int)keyMouse->GetPosY()) && keyMouse->GetButtonPress(0))
		{
			//_device->EndScene();
			//_device->Present(0, 0, 0, 0);//Present the back buffer to front
			//exit1->write_text("ROGEr");
			//_d3dpp.Windowed=false;
			_d3dpp.BackBufferWidth=liter->get_width();
			_d3dpp.BackBufferHeight=liter->get_height();
			_d3dpp.BackBufferFormat=liter->get_format();
			_d3dpp.BackBufferCount=0;
			
						DWORD multi_samples[18];
						DWORD answer;
							multi_samples[0]=D3DMULTISAMPLE_NONE;
							multi_samples[1]=D3DMULTISAMPLE_NONMASKABLE;
							multi_samples[2]=D3DMULTISAMPLE_2_SAMPLES;
							multi_samples[3]=D3DMULTISAMPLE_3_SAMPLES;
							multi_samples[4]=D3DMULTISAMPLE_4_SAMPLES;
							multi_samples[5]=D3DMULTISAMPLE_5_SAMPLES;
							multi_samples[6]=D3DMULTISAMPLE_6_SAMPLES;
							multi_samples[7]=D3DMULTISAMPLE_7_SAMPLES;
							multi_samples[8]=D3DMULTISAMPLE_8_SAMPLES;
							multi_samples[9]=D3DMULTISAMPLE_9_SAMPLES ;
							multi_samples[10]=D3DMULTISAMPLE_10_SAMPLES ;
							multi_samples[11]=D3DMULTISAMPLE_11_SAMPLES ;
							multi_samples[12]=D3DMULTISAMPLE_12_SAMPLES ;
							multi_samples[13]=D3DMULTISAMPLE_13_SAMPLES ;
							multi_samples[14]=D3DMULTISAMPLE_14_SAMPLES ;
							multi_samples[15]=D3DMULTISAMPLE_15_SAMPLES ;
							multi_samples[16]=D3DMULTISAMPLE_16_SAMPLES ;
							multi_samples[17]=D3DMULTISAMPLE_FORCE_DWORD;
							
						for(int i=0;i<18;i++)
						{ 
							if(D3D_OK==_d3d9->CheckDeviceMultiSampleType(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								_d3dpp.BackBufferFormat,
								false,
								(D3DMULTISAMPLE_TYPE)multi_samples[i],
								&answer))
									if(FAILED(_device->Reset(&_d3dpp)))
									{
										//exit1->write_text("THIS SHIT DONT WORK");
										//exit(1);
									}
						}

			
			//	TheCamera.getViewMatrix(&V);
			//	_device->SetTransform(D3DTS_VIEW, &V);

			//	_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x111111, 1.0f, 0);
			//	_device->BeginScene();
			//	_device->SetTransform(D3DTS_WORLD,&scale);
			//	_device->SetMaterial(&materials::WHITE_MTRL);
		}
		//liter->draw(100,100);
	}
//	static char* convert=new char();
//	itoa(a.Height,convert,10);
//	exit1->write_text(convert);
//	exit1->write_text("convert");
*/
}