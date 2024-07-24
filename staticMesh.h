#ifndef _staticMeshH_
#define _staticMeshH_

#include <d3dx9.h>
#include <string>
#include "visual.h"
#include "physical.h"

class staticMesh : public visual, public physical
{
private:
	LPD3DXMESH						mesh;
	std::vector<D3DMATERIAL9>       Mtrls;
	std::vector<IDirect3DTexture9*> Textures;
public:
	staticMesh(std::string);
	~staticMesh();
	void draw();

};

















#endif _staticMeshH_