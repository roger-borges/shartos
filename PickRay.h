#include <d3dx9.h>
#include "extra.h"
#ifndef __PickRayH__
#define __PickRayH__

	//compute the picking Ray, all the math stuff in here
	extra::Ray CalcPickRay(int x, int y, IDirect3DDevice9*     Device);
	//Transform the picking Ray into WorldSpace
	void TransRay(extra::Ray* ray, D3DXMATRIX* T);
	//check if the ray intersects with the sphere surrounding the object
	bool RayInt(extra::Ray* ray, extra::BoundingSphere* sphere);
	

#endif //__PickRayH__