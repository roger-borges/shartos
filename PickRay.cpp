#include "PickRay.h"


extra::Ray CalcPickRay(int x, int y, IDirect3DDevice9*     Device)
{
	float px = 0.0f;
	float py = 0.0f;

	D3DVIEWPORT9 vp;
	Device->GetViewport(&vp);

	D3DXMATRIX proj;
	Device->GetTransform(D3DTS_PROJECTION, &proj);

	px = ((( 2.0f*x) / vp.Width)  - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	extra::Ray ray;
	ray.Origin    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ray.Direction = D3DXVECTOR3(px, py, 1.0f);

	return ray;
}
void TransRay(extra::Ray* ray, D3DXMATRIX* T)
{
		// transform the ray's origin, w = 1.
	D3DXVec3TransformCoord(
		&ray->Origin,
		&ray->Origin,
		T);

	// transform the ray's direction, w = 0.
	D3DXVec3TransformNormal(
		&ray->Direction,
		&ray->Direction,
		T);

	// normalize the direction
	D3DXVec3Normalize(&ray->Direction, &ray->Direction);


}
bool RayInt(extra::Ray* ray, extra::BoundingSphere* sphere)
{	
	D3DXVECTOR3 v = ray->Origin - sphere->_center;

	float b = 2.0f * D3DXVec3Dot(&ray->Direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	// find the discriminant
	float discriminant = (b * b) - (4.0f * c);

	// test for imaginary number
	if( discriminant < 0.0f )
		return false;

	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// if a solution is >= 0, then we intersected the sphere
	if( s0 >= 0.0f || s1 >= 0.0f )
		return true;
	
	return false;
}