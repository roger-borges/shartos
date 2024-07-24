//Class light adds lights to the world
#ifndef __LightH__
#define __LightH__
#include <d3dx9.h>
//#include "Light.h"

class Light
{
public:
	//Light type
	 enum LightType { DIRECTIONAL, POINT, SPOTLIGHT };
	 Light(IDirect3DDevice9* device,LightType lightType,bool state,D3DXVECTOR3 *direction, 
		   D3DXVECTOR3 *position, D3DXCOLOR* colorambient,D3DXCOLOR* colordiff,D3DXCOLOR* colorspec,
		   float range, float falloff, float attenuation0=1.0f,
		   float attenuation1=0.0f, float attenuation2=0.0f,
		   float theda=0.0f, float phi=0.0f);
	~Light();
private:
	bool _state;
	LightType  _lightType;
	IDirect3DDevice9*       _device;
	D3DLIGHT9 _light;
};
#endif //__LightH__