#include "object.h"

IDirect3DDevice9* object::_device=0;
object::object()
{
}
void object::addType(const std::string& type){
	_type_list.push_back(type);
}

void object::setDevice(IDirect3DDevice9* dev)
{
	_device=dev;
}

D3DXMATRIX object::getMatrix() const
{   
	return objMatrix;
}