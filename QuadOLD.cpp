/////These are Methods in Class Quad

//#include "engine.h"
#include "vertex.h"
#include "Quad.h"
//#include <d3dx9.h>

Quad::Quad(float x_1, float x_2,float y_1,float y_2, float z_1,float z_2,
		   float n_x,float n_y,float n_z, std::string pathToTexture )
{
	// save a ptr to the device
	//_device = device;
	 object::addType(std::string("visual"));
	
	D3DXCreateTextureFromFile(_device,pathToTexture.c_str(),&_tex);
	
	D3DXMatrixIdentity(&objMatrix);

	_x1=x_1; _y1=y_1; _z1=z_1;
	 _x2=x_2; _y2=y_2; _z2=z_2;
	 _nx=n_x; _ny=n_y; _nz=n_z;

	_device->CreateVertexBuffer(
		24 * sizeof(Vertex), 
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	Vertex* v;
	_vb->Lock(0, 0, (void**)&v, 0);


	// fill in the vertex data
		v[0] = Vertex(_x1, _y1, _z1, _nx,_ny,_nz, 0.0f, 1.0f); 
		v[1] = Vertex(_x1, _y2, _z1,_nx,_ny,_nz, 0.0f, 0.0f); 
		v[2] = Vertex( _x2, _y2, _z2,_nx,_ny,_nz, 1.0f, 0.0f); 
		v[3] = Vertex( _x2, _y1, _z2,_nx,_ny,_nz, 1.0f, 1.0f); 

	
	_vb->Unlock();

	_device->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	WORD* i = 0;
	_ib->Lock(0, 0, (void**)&i, 0);

	// fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;
	_ib->Unlock();
}

Quad::~Quad()
{
	if(_vb){_vb->Release(); _vb = 0;}
	if(_ib){_ib->Release(); _ib = 0;}
}

void Quad::draw()
{		

	//::MessageBox(0,"in the draw function","",0);

	if( objMatrix )
		_device->SetTransform(D3DTS_WORLD, &objMatrix);
	//if( mtrl )
	//	_device->SetMaterial(mtrl);
	if( _tex )
		_device->SetTexture(0, _tex);

	_device->SetStreamSource(0, _vb, 0, sizeof(Vertex));
	_device->SetIndices(_ib);
	_device->SetFVF(FVF_VERTEX);
	_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, 
		0,                  
		0,                  
		4,
		0,
		12);  

	
}