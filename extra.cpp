#include "extra.h"

extra::BoundingBox::BoundingBox()
{
	// infinite small 
	_min.x = extra::INFINITY;
	_min.y = extra::INFINITY;
	_min.z = extra::INFINITY;

	_max.x = -extra::INFINITY;
	_max.y = -extra::INFINITY;
	_max.z = -extra::INFINITY;
}

bool extra::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if( p.x >= _min.x && p.y >= _min.y && p.z >= _min.z &&
		p.x <= _max.x && p.y <= _max.y && p.z <= _max.z )
	{
		return true;
	}
	else
	{
		return false;
	}
}

extra::BoundingSphere::BoundingSphere()
{
	_radius = 0.0f;
}
float extra::GetRandomFloat(float lowBound, float highBound)
{
	if( lowBound >= highBound ) // bad input
		return lowBound;

	// get random float in [0, 1] interval
	float f = (rand() % 10000) * 0.0001f; 

	// return float in [lowBound, highBound] interval. 
	return (f * (highBound - lowBound)) + lowBound; 
}

void extra::GetRandomVector(
	  D3DXVECTOR3* out,
	  D3DXVECTOR3* min,
	  D3DXVECTOR3* max)
{
	out->x = GetRandomFloat(min->x, max->x);
	out->y = GetRandomFloat(min->y, max->y);
	out->z = GetRandomFloat(min->z, max->z);
}

//convert Float to DWORD
DWORD extra::FtoDw(float f)
{
	return *((DWORD*)&f);
}



