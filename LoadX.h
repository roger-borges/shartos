
#ifndef __LoadXH__
#define __LoadXH__

#include <d3dx9.h>
#include <Windows.h>
#include <mmsystem.h>
#include <string>

using namespace std;

class LoadX
{
public:
	LoadX(IDirect3DDevice9* device,LPSTR filename);
	~LoadX();
	

	bool draw(D3DXMATRIX* world, D3DMATERIAL9* mtrl);
private:
	LPSTR _name;
	ID3DXMesh*              _Mesh;				//mesh
	D3DMATERIAL9*           _MeshMaterials;
	LPDIRECT3DTEXTURE9*     _MeshTextures;		// Textures for our mesh
	DWORD                   _NumMaterials;
	LPD3DXBUFFER			_D3DXMtrlBuffer;	//Mtr buffer
	IDirect3DDevice9*       _device;			//device
	D3DXMATERIAL*			_d3dxMaterials;
};
#endif //__LoadXH__