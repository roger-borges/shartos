#ifndef _visualH_
#define _visualH_

#include "object.h"

class visual : public virtual object
{
	public:
		visual(){object::addType(std::string("visual"));}
		virtual void draw(){};
	protected:
		D3DXMATRIX                   _world;
		D3DMATERIAL9                 _mtrl;
		IDirect3DTexture9*           _tex;

};

#endif _visualH_