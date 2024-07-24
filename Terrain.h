
#ifndef __TerrainH__
#define __TerrainH__
#include <d3dx9.h>
#include "engine.h"
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "visual.h"
#include "Quad.h"
class Tree
{
	private:
//		IDirect3DDevice9* _device;
//		Quad* one;
//		Quad* two;
		D3DXMATRIX* _world;
		D3DMATERIAL9* _mtrl;
		IDirect3DTexture9* _tex;
		bool _world_t;
	public:
		Tree();
		~Tree();
		void draw();
};

class Terrain : public visual
{
public:
	Terrain(
		std::string heightmapFileName, 
		int numVertsPerRow,  
		int numVertsPerCol, 
		int cellSpacing,    // space between cells
		float heightScale,
		float lx, float ly, float lz);   

	~Terrain();

	int  getHeightmapEntry(int row, int col);
	void setHeightmapEntry(int row, int col, int value);

	float getHeight(float x, float z);

	bool  loadTexture(std::string fileName);
	bool  genTexture(D3DXVECTOR3*    directionToLight);
	void  draw();

private:
//	D3DXMATRIX              _bla;
//	IDirect3DDevice9*       _device;
	D3DXVECTOR3			    _temp;
	IDirect3DTexture9*      _tex;
	IDirect3DVertexBuffer9* _vb;
	IDirect3DIndexBuffer9*  _ib;

	int _numVertsPerRow;	//# of vertices per Row
	int _numVertsPerCol;	//# of vertices per Colum
	int _cellSpacing;		//space between Parallel vertices.

	int _numCellsPerRow;	//# of cells per Row =(_numVertsperRow-1)
	int _numCellsPerCol;	//# of cells per colum =(_numVertspercolum-1)
	int _width;				//_numCellsPerRow*cellspacing
	int _depth;				//_numCellsPerCol*cellspacing
	int _numVertices;		//total # of vertices in the terrai
	int _numTriangles;		//total # of Tirangles in terrain

	float _heightScale;

	//contains the height of each vertices for the entire terrain.
	std::vector<int> _heightmap;

	// helper methods
	bool  readRawFile(std::string fileName);
	bool  computeVertices();
	bool  computeIndices();
	bool  lightTerrain(D3DXVECTOR3*    directionToLight);
	float computeShade(int cellRow, int cellCol,D3DXVECTOR3*    directionToLight);

	struct TerrainVertex
	{
		TerrainVertex(){}
		TerrainVertex(float x, float y, float z, float u, float v)
		{
			_x = x; _y = y; _z = z; _u = u; _v = v;
		}
		float _x, _y, _z;
		float _u, _v;

		static const DWORD FVF;
	};
};


#endif // __TerrainH__
