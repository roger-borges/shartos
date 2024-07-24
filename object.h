#ifndef OBJ_H
#define OBJ_H

#include "engine.h"
#include "BoundingVolume.h"
class object: public BoundingVolume
{
private:
	friend class game;
	static void setDevice(IDirect3DDevice9*);
	std::list<std::string> _type_list;
	

protected:
	object();
	void addType(const std::string&);
	D3DXMATRIX viewMatrix;// pulled from private
	D3DXMATRIX objMatrix;//pulled from private
public:
	
	virtual ~object(){}
	const std::list<std::string>& getTypeList()const{return _type_list;}
	D3DXMATRIX getMatrix() const;
	void setMatrix(D3DXMATRIX);
	void multMatrix(D3DXMATRIX);
	void translateMatrix(D3DXVECTOR3);
	void rotateMatrix(D3DXVECTOR3);
	void scaleMatrix(D3DXVECTOR3);
	static IDirect3DDevice9* _device;
};
//IDirect3DDevice9* object::_device=0;





#endif OBJ_H