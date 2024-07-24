#include "staticMesh.h"

staticMesh::staticMesh(std::string pathToMesh)
{
	object::addType(std::string("visual"));

//	::MessageBox(0,"start load mesh","",0);
	// save a ptr to the device
//	_device = device;
//	_name=filename;
	//HRESULT hr = 0;
	//
	// Load the XFile data.
	//

	D3DXMatrixIdentity(&objMatrix);
	
	ID3DXBuffer* adjBuffer  = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls   = 0;

//	::MessageBox(0,"1 load mesh","",0);

	if(FAILED(D3DXLoadMeshFromX(  
		pathToMesh.c_str(),
		D3DXMESH_MANAGED,
		_device,
		&adjBuffer,
		&mtrlBuffer,
		NULL,
		&numMtrls,
		&mesh)))
	{
		::MessageBox(0,"LOADING X FILE FAILED",pathToMesh.c_str(),0);
		return;
	}

//	::MessageBox(0,"2 load mesh","",0);

	//
	// Extract the materials, and load textures.
	//

	if( mtrlBuffer != 0 && numMtrls != 0 )
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

//		::MessageBox(0,"2.1 load mesh","",0);

		for(DWORD i = 0; i < numMtrls; i++)
		{
//			::MessageBox(0,"2.2 load mesh","",0);
			// the MatD3D property doesn't have an ambient value set
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material
			Mtrls.push_back( mtrls[i].MatD3D );

			// check if the ith material has an associative texture
			if( mtrls[i].pTextureFilename != 0 )
			{
				// load the texture for the ith subset
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					_device,
					mtrls[i].pTextureFilename,
					&tex);

				// save the loaded texture
				Textures.push_back( tex );
			}
			else
			{
				// no texture for the ith subset
				Textures.push_back( 0 );
			}
//			::MessageBox(0,"2.7 load mesh","",0);
		}
	}
//	::MessageBox(0,"2.8 delete buffer load mesh","",0);

	//delete 
	mtrlBuffer->Release(); 

//	::MessageBox(0,"3 load mesh","",0);
	//
	// Optimize the mesh.
	//

	if(FAILED(mesh->OptimizeInplace(		
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT  |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0)))
	{
		::MessageBox(0,"FAILED TO LOAD X FILE",pathToMesh.c_str(),0);
	}

	//delete 
	adjBuffer->Release(); 

//	::MessageBox(0,"end load mesh","",0);
//	if(pathToMesh == "Atiger.x")
//	{
//		//::MessageBox(0,"DRAWING MESH","DRAWING MESH",0);
//		AddSpin(1.0,1.0,1.0);
//		AddVelocity(0.0,5.0,0.0);
//		AddTranslation(1.0,10.0,1.0);
//		AddRotation(10.0f,10.0f,10.0f);
//		SetTranslation(0,100,0);
//	}	
}

staticMesh::~staticMesh()
{
	//Clean up clean up everybody do you share and clean up
	for(int i = 0; i < Textures.size(); i++)
		delete Textures[i];	
	delete  mesh;    
}

void staticMesh::draw()
{
//	::MessageBox(0,"DRAWING MESH","DRAWING MESH",0);

	

//	if( objMatrix )
		_device->SetTransform(D3DTS_WORLD, &objMatrix);

	D3DXMATRIX temp;
		D3DXMatrixScaling(&temp,125.0f,125.0f,125.0f);
		_device->SetTransform(D3DTS_WORLD, &temp);

//	if( mtrl )
//		_device->SetMaterial(mtrl);

		
	for(int i = 0; i < Mtrls.size(); i++)
		{
			_device->SetMaterial( &Mtrls[i] );
			_device->SetTexture(0, Textures[i]);
			mesh->DrawSubset(i);
		} 

	return;

}