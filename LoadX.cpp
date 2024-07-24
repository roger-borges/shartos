/////Thesse are Methods in Class LoadX 

//#include "engine.h"
//#include "includes.h"
#include "LoadX.h"
#include "vertex.h"
#include <vector>


LoadX::LoadX(IDirect3DDevice9* device,LPSTR filename)
{
	
	// save a ptr to the device
	_device = device;
	_name=filename;
	_NumMaterials = 0L;

	// Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromX( _name, D3DXMESH_SYSTEMMEM, 
                                   _device, NULL, 
                                   &_D3DXMtrlBuffer, NULL, &_NumMaterials, 
                                   &_Mesh ) ) )
   

	//now extract all the material here.
	_d3dxMaterials = (D3DXMATERIAL*)_D3DXMtrlBuffer->GetBufferPointer();
    _MeshMaterials = new D3DMATERIAL9[_NumMaterials];
    _MeshTextures  = new LPDIRECT3DTEXTURE9[_NumMaterials];
	 for( DWORD i=0; i<_NumMaterials; i++ )
    {
        // Copy the material
        _MeshMaterials[i] = _d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        _MeshMaterials[i].Ambient = _MeshMaterials[i].Diffuse;

        _MeshTextures[i] = NULL;
        if( _d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(_d3dxMaterials[i].pTextureFilename) > 0 )
        {
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFile( _device, 
                                                _d3dxMaterials[i].pTextureFilename, 
                                                &_MeshTextures[i] ) ) )
            {
                
               
            }
        }
    }
	// Done with the material buffer
    _D3DXMtrlBuffer->Release();


}

LoadX::~LoadX()
{
	    if( _MeshMaterials != NULL ) 
        delete[] _MeshMaterials;

    if( _MeshTextures )
    {
        for( DWORD i = 0; i < _NumMaterials; i++ )
        {
            if( _MeshTextures[i] )
                _MeshTextures[i]->Release();
        }
        delete[] _MeshTextures;
    }
    if( _Mesh != NULL )
        _Mesh->Release();
    
    if( _device != NULL )
        _device->Release();

	  
}

bool LoadX::draw(D3DXMATRIX* world, D3DMATERIAL9* mtrl)
{
	if( world )
		_device->SetTransform(D3DTS_WORLD, world);
	if( mtrl )
		_device->SetMaterial(mtrl);

	 for( DWORD i=0; i<_NumMaterials; i++ )
        {
            // Set the material and texture for this subset
            _device->SetMaterial( &_MeshMaterials[i] );
            _device->SetTexture( 0, _MeshTextures[i] );
        
            // Draw the mesh subset
            _Mesh->DrawSubset( i );
        }

	return true;
}

