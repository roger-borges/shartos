#include "Light.h"
//#include "materials.h"


//Light Spotlight
Light::Light(IDirect3DDevice9* device,LightType lightType,bool state,D3DXVECTOR3* direction, 
		   D3DXVECTOR3 *position,D3DXCOLOR* colorambient,D3DXCOLOR* colordiff,D3DXCOLOR* colorspec,
		   float range, float falloff, float attenuation0,float attenuation1, float attenuation2,
		   float theda, float phi)
{

	_state=state;  //state of light true or false
	_lightType=lightType; //light type
	_device = device;
	//allocate memory for it
	::ZeroMemory(&_light, sizeof(_light));
	
	//directional light
	if(_lightType==DIRECTIONAL)
	{
	
	_light.Type      = D3DLIGHT_DIRECTIONAL;
	_light.Ambient   = *colorambient;
	_light.Diffuse   = *colordiff;
	_light.Specular  = *colorspec;
	_light.Direction = *direction;
	}
	//pointlight
	if(_lightType==POINT)
	{
	_light.Type      = D3DLIGHT_POINT;
	_light.Ambient   = *colorambient;
	_light.Diffuse   = *colordiff;
	_light.Specular  = *colorspec;
	_light.Position  = *position;
	_light.Range        = range;
	_light.Falloff      = falloff;
	_light.Attenuation0 = attenuation0;
	_light.Attenuation1 = attenuation1;
	_light.Attenuation2 = attenuation2;
	}
	//Spotlight
	if(_lightType==SPOTLIGHT)
	{
	_light.Type      = D3DLIGHT_SPOT;
	_light.Ambient   = *colorambient;
	_light.Diffuse   = *colordiff;
	_light.Specular  = *colorspec;
	_light.Position  = *position;
	_light.Direction = *direction;
	_light.Range        = range;
	_light.Falloff      = falloff;
	_light.Attenuation0 = attenuation0;
	_light.Attenuation1 = attenuation1;
	_light.Attenuation2 = attenuation2;
	_light.Theta        = theda;
	_light.Phi          = phi;
	}
	_device->SetLight(0, &_light);
	_device->LightEnable(0, _state);
}
Light::~Light()
{

}