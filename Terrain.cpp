//Terrain Engin
#include "Terrain.h"
const DWORD Terrain::TerrainVertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

Terrain::Terrain(std::string heightmapFileName,
				 int numVertsPerRow,
				 int numVertsPerCol,
				 int cellSpacing,
				 float heightScale,
				 float lx, float ly, float lz)
{
	object::addType("visual");
	object::addType("terrain");

	D3DXMatrixIdentity(&objMatrix);

	//_device         = device;
	_numVertsPerRow = numVertsPerRow;	
	_numVertsPerCol = numVertsPerCol;
	_cellSpacing    = cellSpacing;	//amount of space between parallel verticies

	_numCellsPerRow = _numVertsPerRow - 1;
	_numCellsPerCol = _numVertsPerCol - 1;

	_width = _numCellsPerRow * _cellSpacing;
	_depth = _numCellsPerCol * _cellSpacing;

	_numVertices  = _numVertsPerRow * _numVertsPerCol;	//#of quads per terrain
	_numTriangles = _numCellsPerRow * _numCellsPerCol * 2; //2 times the triangels and quads

	//scale we want to use( greater this is higher the mountains wil be)
	//scales the heightmap by this much. (1.0 is as much as heightmap)
	_heightScale = heightScale;		

	// load heightmap
	if( !readRawFile(heightmapFileName) )
	{
		::MessageBox(0, "readRawFile - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// scale heights
	for(int i = 0; i < _heightmap.size(); i++)
		_heightmap[i] *= heightScale;

	// compute the vertices
	if( !computeVertices() )
	{
		::MessageBox(0, "computeVertices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}

	// compute the indices
	if( !computeIndices() )
	{
		::MessageBox(0, "computeIndices - FAILED", 0, 0);
		::PostQuitMessage(0);
	}
	D3DXVECTOR3 TEMP(lx,ly,lz);
	Terrain::genTexture(&TEMP);
}

Terrain::~Terrain()
{
	extra::Release<IDirect3DVertexBuffer9*>(_vb);
	extra::Release<IDirect3DIndexBuffer9*>(_ib);
	extra::Release<IDirect3DTexture9*>(_tex);
}


//What is the height at paticular Vertices
int Terrain::getHeightmapEntry(int row, int col)
{
	return _heightmap[row * _numVertsPerRow + col];
}

//define the height of paticular vertices.
void Terrain::setHeightmapEntry(int row, int col, int value)
{
	_heightmap[row * _numVertsPerRow + col] = value;
}


//fill in the Vertices
bool Terrain::computeVertices()
{
	HRESULT hr = 0;

	//Create a VB to hold all the vertices for the Terrain
	hr = _device->CreateVertexBuffer(
		_numVertices * sizeof(TerrainVertex),
		D3DUSAGE_WRITEONLY,
		TerrainVertex::FVF,
		D3DPOOL_MANAGED,
		&_vb,
		0);

	if(FAILED(hr))
		return false;

	// coordinates to start generating vertices at
	//top left corner.
	int startX = -_width / 2;
	int startZ =  _depth / 2;

	// coordinates to end generating vertices at
	//bottom right corner
	int endX =  _width / 2;
	int endZ = -_depth / 2;

	// compute the increment size of the texture coordinates
	// from one vertex to the next.
	float uCoordIncrementSize = 1.0f / (float)_numCellsPerRow;
	float vCoordIncrementSize = 1.0f / (float)_numCellsPerCol;

	TerrainVertex* v = 0;
	_vb->Lock(0, 0, (void**)&v, 0);

	int i = 0;
	for(int z = startZ; z >= endZ; z -= _cellSpacing)
	{
		int j = 0;
		for(int x = startX; x <= endX; x += _cellSpacing)
		{
			// compute the correct index into the vertex buffer and heightmap
			// based on where we are in the nested loop.
			int index = i * _numVertsPerRow + j;

			v[index] = TerrainVertex(
				(float)x,
				(float)_heightmap[index],
				(float)z,
				(float)j * uCoordIncrementSize,
				(float)i * vCoordIncrementSize);

			j++; // next column
		}
		i++; // next row
	}

	_vb->Unlock();

	return true;
}


//Computer indicies
bool Terrain::computeIndices()
{
	HRESULT hr = 0;

	hr = _device->CreateIndexBuffer(
		_numTriangles * 3 * sizeof(WORD), // 3 indices per triangle
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&_ib,
		0);

	if(FAILED(hr))
		return false;

	WORD* indices = 0;
	_ib->Lock(0, 0, (void**)&indices, 0);

	// index to start of a group of 6 indices that describe the
	// two triangles that make up a quad
	int baseIndex = 0;

	// loop through and compute the triangles of each quad
	for(int i = 0; i < _numCellsPerCol; i++)
	{
		for(int j = 0; j < _numCellsPerRow; j++)
		{
			indices[baseIndex]     =   i   * _numVertsPerRow + j;
			indices[baseIndex + 1] =   i   * _numVertsPerRow + j + 1;
			indices[baseIndex + 2] = (i+1) * _numVertsPerRow + j;

			indices[baseIndex + 3] = (i+1) * _numVertsPerRow + j;
			indices[baseIndex + 4] =   i   * _numVertsPerRow + j + 1;
			indices[baseIndex + 5] = (i+1) * _numVertsPerRow + j + 1;

			// next quad
			baseIndex += 6;
		}
	}

	_ib->Unlock();

	return true;
}


//Load Textures for the Terrain
bool Terrain::loadTexture(std::string fileName)
{
	HRESULT hr = 0;

	hr = D3DXCreateTextureFromFile(
		_device,
		fileName.c_str(),
		&_tex);

	if(FAILED(hr))
		return false;

	return true;
}

bool Terrain::genTexture(D3DXVECTOR3*    directionToLight)
{
	// Method fills the top surface of a texture procedurally.  Then
	// lights the top surface.  Finally, it fills the other mipmap
	// surfaces based on the top surface data using D3DXFilterTexture.

	HRESULT hr = 0;

	// texel for each quad cell
	int texWidth  = _numCellsPerRow;
	int texHeight = _numCellsPerCol;

	// create an empty texture
	hr = D3DXCreateTexture(
		_device,
		texWidth, texHeight,
		0, // create a complete mipmap chain
		0, // usage
		D3DFMT_X8R8G8B8,// 32 bit XRGB format
		D3DPOOL_MANAGED, &_tex);

	if(FAILED(hr))
		return false;

	D3DSURFACE_DESC textureDesc; 
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code 
	// that fills the texture is hard coded to a 32 bit pixel depth.
	if( textureDesc.Format != D3DFMT_X8R8G8B8 )
		return false;
		
	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(0/*lock top surface*/, &lockedRect, 
		0 /* lock entire tex*/, 0/*flags*/);         

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < texHeight; i++)
	{
		for(int j = 0; j < texWidth; j++)
		{
			D3DXCOLOR c;

			// get height of upper left vertex of quad.
			float height = (float)getHeightmapEntry(i, j) / _heightScale;

			if( (height) < 42.5f ) 		 c = extra::BEACH_SAND;
			else if( (height) < 85.0f )	 c = extra::LIGHT_YELLOW_GREEN;
			else if( (height) < 127.5f ) c = extra::PUREGREEN;
			else if( (height) < 170.0f ) c = extra::DARK_YELLOW_GREEN;
			else if( (height) < 212.5f ) c = extra::DARKBROWN;
			else	                     c = extra::WHITE;

			// fill locked data, note we divide the pitch by four because the
			// pitch is given in bytes and there are 4 bytes per DWORD.
			imageData[i * lockedRect.Pitch / 4 + j] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	
	
	hr = D3DXFilterTexture(
		_tex,
		0, // default palette
		0, // use top level as source level
		D3DX_DEFAULT); // default filter

	if(FAILED(hr))
	{
		::MessageBox(0, "D3DXFilterTexture() - FAILED", 0, 0);
		return false;
	}

	return true;
}

bool Terrain::lightTerrain(D3DXVECTOR3*    directionToLight)
{
	HRESULT hr = 0;

	D3DSURFACE_DESC textureDesc; 
	_tex->GetLevelDesc(0 /*level*/, &textureDesc);

	// make sure we got the requested format because our code that fills the
	// texture is hard coded to a 32 bit pixel depth.
	if( textureDesc.Format != D3DFMT_X8R8G8B8 )
		return false;
		
	D3DLOCKED_RECT lockedRect;
	_tex->LockRect(
		0,          // lock top surface level in mipmap chain
		&lockedRect,// pointer to receive locked data
		0,          // lock entire texture image
		0);         // no lock flags specified

	DWORD* imageData = (DWORD*)lockedRect.pBits;
	for(int i = 0; i < textureDesc.Height; i++)
	{
		for(int j = 0; j < textureDesc.Width; j++)
		{
			// index into texture, note we use the pitch and divide by 
			// four since the pitch is given in bytes and there are 
			// 4 bytes per DWORD.
			int index = i * lockedRect.Pitch / 4 + j;

			// get current color of quad
			D3DXCOLOR c( imageData[index] );

			// shade current quad
			c *= computeShade(i, j,  directionToLight);;

			// save shaded color
			imageData[index] = (D3DCOLOR)c;
		}
	}

	_tex->UnlockRect(0);

	return true;
}

float Terrain::computeShade(int cellRow, int cellCol,D3DXVECTOR3*    directionToLight )
{
	// get heights of three vertices on the quad
	float heightA = getHeightmapEntry(cellRow,   cellCol);
	float heightB = getHeightmapEntry(cellRow,   cellCol+1);
	float heightC = getHeightmapEntry(cellRow+1, cellCol);

	// build two vectors on the quad
	D3DXVECTOR3 u(_cellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 v(0.0f,         heightC - heightA, -_cellSpacing);

	// find the normal by taking the cross product of two
	// vectors on the quad.
	D3DXVECTOR3 n;
	D3DXVec3Cross(&n, &u, &v);
	D3DXVec3Normalize(&n, &n);

	float cosine = D3DXVec3Dot(&n, directionToLight);

	if(cosine < 0.0f)
		cosine = 0.0f;

	return cosine;
}




//Reads Data from RAW file someHow
bool Terrain::readRawFile(std::string fileName)
{
	// Restriction: RAW file dimensions must be >= to the
	// dimensions of the terrain.  That is a 128x128 RAW file
	// can only be used with a terrain constructed with at most
	// 128x128 vertices.

	// A height for each vertex
	std::vector<BYTE> in( _numVertices );

	std::ifstream inFile(fileName.c_str(), std::ios_base::binary);

	if( inFile == 0 )
		return false;

	inFile.read(
		(char*)&in[0], // buffer
		in.size());// number of bytes to read into buffer

	inFile.close();

	// copy BYTE vector to int vector
	_heightmap.resize( _numVertices );

	for(int i = 0; i < in.size(); i++)
		_heightmap[i] = in[i];

	return true;
}

float Terrain::getHeight(float x, float z)
{
	// Translate on xz-plane by the transformation that takes
	// the terrain START point to the origin.
	x = ((float)_width / 2.0f) + x;
	z = ((float)_depth / 2.0f) - z;

	// Scale down by the transformation that makes the 
	// cellspacing equal to one.  This is given by 
	// 1 / cellspacing since; cellspacing * 1 / cellspacing = 1.
	x /= (float)_cellSpacing;
	z /= (float)_cellSpacing;

	// From now on, we will interpret our positive z-axis as
	// going in the 'down' direction, rather than the 'up' direction.
	// This allows to extract the row and column simply by 'flooring'
	// x and z:

	float col = ::floorf(x);
	float row = ::floorf(z);

	// get the heights of the quad we're in:
	// 
    //  A   B
    //  *---*
    //  | / |
    //  *---*  
    //  C   D

	float A = getHeightmapEntry(row,   col);
	float B = getHeightmapEntry(row,   col+1);
	float C = getHeightmapEntry(row+1, col);
	float D = getHeightmapEntry(row+1, col+1);
	
	float height =(A+B+C+D)/4;
	

	return height;
}

void Terrain::draw()
{
	HRESULT hr = 0;

	if( _device )
	{
		_device->SetTransform(D3DTS_WORLD, &objMatrix);

		_device->SetStreamSource(0, _vb, 0, sizeof(TerrainVertex));
		_device->SetFVF(TerrainVertex::FVF);
		_device->SetIndices(_ib);
		
		_device->SetTexture(0, _tex);

		// turn off lighting since we're lighting it ourselves
		_device->SetRenderState(D3DRS_LIGHTING, false);

		hr =_device->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			0,
			_numVertices,
			0,
			_numTriangles);

		_device->SetRenderState(D3DRS_LIGHTING, true);


	}

}

/////////////////Tree Stuff goes here/////////////////////////////

Tree::Tree()
{
	//_device=device;
//	Tree::one=new Quad(_device,-1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,0.0f,0.0f,-1.0f);
//	Tree::two= new Quad(_device,-1.0f,1.0f,-1.0f,1.0f,-1.0f,-1.0f,0.0f,0.0f,-1.0f);
	
//	Tree::_world_t=false;

}
Tree::~Tree()
{


}
void Tree::draw()
{
	
		//_world=world;
		//Tree::_world_t=true;
	
	
//		one->draw();

//	return true;
}
