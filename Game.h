#ifndef __gameH__
#define __gameH__

#include <d3dx9.h>
#include <list>
#include "engine.h"
#include "kernel.h"
#include "camera.h"
class game{

private:
	enum GameState{inGame,mainMenu, mapsMenu, inGameMenu, Settings,inGameExit,Exit, None};
	int windowWidth, windowHeight;
	int currentState;
	IDirect3DDevice9* _device;
	bool mouseclick0, mouseclick1, mouseWheelUp, mouseWheelDown;
	D3DXMATRIX V;
	D3DXMATRIX scale;
	D3DXMATRIX proj;
	Input* keyMouse;
	D3DPRESENT_PARAMETERS _d3dpp;
	IDirect3D9* _d3d9;

	Kernel* _kernel;


public:
	game();
	~game();

	void run();   //main loop
	void stop();  //exits
	void setDevice(IDirect3DDevice9* Device);		//set the Device
	void mainMenuGui();								//function displays the main menu gui	
	void inGameMenuGui();							//	
	void settingsGui();								//when you click settings in main menu
	void inGameFunc();								//start new game, load the levels	
	void exitFunc();
	void initialize();								//set up 
	void mapsMenuGui();	
	void inGameExitFunc();							//exit from inside tha game.
	void set_d3d9(IDirect3D9 *d3d){ _d3d9=d3d; }
	void ReleaseDevice(){_device->Release();}
	void displays();
	void store_present_parameters(D3DPRESENT_PARAMETERS d){_d3dpp=d;}


};

#endif