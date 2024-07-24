/////These are Methods in Class Quad

//#include "engine.h"
#include "vertex.h"
#include "Quad.h"
//#include <d3dx9.h>

Quad::Quad(float x_1, float x_2,float y_1,float y_2, float z_1,float z_2,
		   float n_x,float n_y,float n_z, std::string pathToTexture, bool twosided )
{
	
	 object::addType(std::string("visual"));
	 //is the quad 2 sided quad
	_twosided=twosided;
	D3DXCreateTextureFromFile(_device,pathToTexture.c_str(),&_tex);
	
	D3DXMatrixIdentity(&objMatrix);

	if(n_y != 0.0f)
	{
//		::MessageBox(0,"QUAD","QUAD",0);
		////////////////////////////
		D3DXVECTOR3 m_rotation;
		m_rotation.x = 0;
		m_rotation.y = 0;
		m_rotation.z = n_y * 1.57;

		D3DXMATRIX rotationX, rotationY;
		D3DXMatrixRotationX( &rotationX, m_rotation.x );
		D3DXMatrixRotationY( &rotationY, m_rotation.y );
		D3DXMatrixRotationZ( &objMatrix, m_rotation.z );
		D3DXMatrixMultiply( &objMatrix, &objMatrix, &rotationX );
		D3DXMatrixMultiply( &objMatrix, &objMatrix, &rotationY );
		//////////////////////////////
	}

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


	D3DXMatrixIdentity(&m_translationMatrix);
	D3DXMatrixIdentity(&m_rotationMatrix);

}

Quad::~Quad()
{
	if(_vb){_vb->Release(); _vb = 0;}
	if(_ib){_ib->Release(); _ib = 0;}
}

void Quad::newTexture(std::string pathToFile)
{
	D3DXCreateTextureFromFile(_device,pathToFile.c_str(),&_tex);
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

/////////////////////////////////////////////////////////////////////////////////
	// Do not light sky box.
	_device->SetRenderState(D3DRS_LIGHTING, false);

	// Don't write skybox to the depth buffer; in this way, 
	// the skybox will never occlude goemtry, which it should not
	// since it is "infinitely" far away.
	_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	_device->SetRenderState(D3DRS_ZENABLE, false);
	 

	// Set sampler states to clamp so that edge seam does not show where
	// two box faces coincide. 
	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

		// Switch to fixed pipe (Release the set shader if there is one).
	// Note that FX set shaders.
	_device->SetVertexShader(0);
	_device->SetPixelShader(0);
///////////////////////////////////////////////////////////////////////////////////
	//render a 1 sided quad
	if(_twosided==false)
	{
	
		_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST, 
			0,                  
			0,                  
			4,
			0,
			12);  
	}
	//draw a 2 sided quad
	else
	{
		_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		_device->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST, 
		0,
		0,
		4,
		0,
		12);
		_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		
	}

///////////////////////////////////////////////////////////////////////////////
				// Restore render states.
	_device->SetRenderState(D3DRS_LIGHTING, true);
	_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	_device->SetRenderState(D3DRS_ZENABLE, true);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
///////////////////////////////////////////////////////////////////////////////
}

void Quad::walk(float units,D3DXVECTOR3 angleVector)
{
	static float x=angleVector.x;
	static float y=angleVector.y;
	static float z=angleVector.z;
	
	static float dx=0;
	static float dy=0;
	static float dz=0;

	dx += angleVector.x - x;
	dy += angleVector.y - y;
	dz += angleVector.z - z;

	if(_ny != 0)
	{
		static D3DXVECTOR3 m_rotation;
		m_rotation.x = 0;
			m_rotation.y = 0;
			m_rotation.z = _ny * 1.57;
			D3DXMATRIX rotationX, rotationY;
		D3DXMatrixRotationX( &rotationX, m_rotation.x );
		D3DXMatrixRotationY( &rotationY, m_rotation.y );
		D3DXMatrixRotationZ( &m_rotationMatrix, m_rotation.z);
	}
	D3DXMatrixTranslation( &m_translationMatrix, dx, 0, dz );
	D3DXMatrixMultiply( &objMatrix ,&m_rotationMatrix,  &m_translationMatrix);
	
	x=angleVector.x;
	y=angleVector.y;
	z=angleVector.z;



/*	if(_ny != 0.0f)
	{
//		::MessageBox(0,"QUAD","QUAD",0);
		////////////////////////////
		
		static int i = 0;
		if(i==0)
		{
			
		}
		
		D3DXMatrixMultiply( &objMatrix, &objMatrix, &rotationX );
		D3DXMatrixMultiply( &objMatrix, &objMatrix, &rotationY );
		//////////////////////////////
	}
*/

}