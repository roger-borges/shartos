
#ifndef __QuadH__
#define __QuadH__

#include <d3dx9.h>
#include <string>
#include "Visual.h"

class Quad: public visual
{
public:
	Quad(float x_1, float x_2,float y_1,float y_2, float z_1, float z_2,
		float n_x,float n_y,float n_z, std::string, bool twosided);
	~Quad();
	void newTexture(std::string);
	void walk(float,D3DXVECTOR3);
	void draw();
private:
	//IDirect3DDevice9*       _device;
	float _x1;
	float _x2;
	float _y1;
	float _y2;
	float _z1;
	float _z2;
	float _nx;
	float _ny;
	float _nz;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;
	bool					_twosided;

	D3DXMATRIX m_translationMatrix;
	D3DXMATRIX m_rotationMatrix;
};
#endif //__QuadH__