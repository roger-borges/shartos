#include "Physical.h"

physical::physical()

{
    object::addType(std::string("physical"));
	SetTranslation( 0.0f, 5.0f, 0.0f);
	SetRotation( 0.0f, 0.0f, 0.0f);
	SetVelocity( 0.0f, 0.0f, 0.0f);
	SetSpin( 0.0f, 0.0f, 0.0f);


	m_foward = D3DXVECTOR3( 0.0f, 0.0f, 1.0f);
	m_right =  D3DXVECTOR3( 1.0f, 1.0f, 1.0f);

	m_friction = 0.0f;
	SetBoundingSphere(D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), 10.0f );
	SetEllipsoidRadius( D3DXVECTOR3(2.0f,2.0f,2.0f ));

}

void physical::update(float elapsedTime)
{

float friction = 1.0f - m_friction * elapsedTime; //need to calc elapsedTime
m_velocity *= friction;


D3DXVECTOR3 velocity = m_velocity * elapsedTime;
AddTranslation(velocity.x, velocity.y, velocity.z);

m_spin *= friction;
D3DXVECTOR3 spin = m_spin * elapsedTime;
AddRotation(spin.x, spin.y, spin.z);

D3DXMatrixMultiply( &objMatrix , &m_rotationMatrix, &m_translationMatrix);
D3DXMatrixInverse( &viewMatrix, NULL, &objMatrix);

m_foward.x = (float)sin(m_rotation.y);
m_foward.y = (float)-tan(m_rotation.x);
m_foward.x = (float)cos(m_rotation.y);
D3DXVec3Normalize(&m_foward, &m_foward);

m_right.x = (float)cos(m_rotation.y);
m_right.x = (float)tan(m_rotation.z);
m_right.x = (float)-sin(m_rotation.y);
D3DXVec3Normalize( &m_right, &m_right);


RepositionBoundingVolume(&m_translationMatrix);
//if(GetEllipsoidRadius().y > -100)
//	SetVelocity(5.0,-5.0,5.0);
//else
  //  SetVelocity(0.0,0.0,0.0);
	
//reposition bounding volume class here

}






void physical::SetTranslation( float x, float y, float z )
{
	m_translation.x = x;
	m_translation.y = y;
	m_translation.z = z;

	D3DXMatrixTranslation( &m_translationMatrix, m_translation.x, m_translation.y, m_translation.z );
}


void physical::SetTranslation( D3DXVECTOR3 translation )
{
	m_translation = translation;

	D3DXMatrixTranslation( &m_translationMatrix, m_translation.x, m_translation.y, m_translation.z );
}

void physical::AddTranslation( float x, float y, float z )
{
	m_translation.x += x;
	m_translation.y += y;
	m_translation.z += z;

	D3DXMatrixTranslation( &m_translationMatrix, m_translation.x, m_translation.y, m_translation.z );
}

void physical::AddTranslation( D3DXVECTOR3 translation )
{
	m_translation += translation;

	D3DXMatrixTranslation( &m_translationMatrix, m_translation.x, m_translation.y, m_translation.z );
}


D3DXVECTOR3 physical::GetTranslation()
{
	return m_translation;
}

void physical::SetRotation( float x, float y, float z )
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;

	D3DXMATRIX rotationX, rotationY;
	D3DXMatrixRotationX( &rotationX, m_rotation.x );
	D3DXMatrixRotationY( &rotationY, m_rotation.y );
	D3DXMatrixRotationZ( &m_rotationMatrix, m_rotation.z );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationX );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationY );
}


void physical::SetRotation( D3DXVECTOR3 rotation )
{
	m_rotation = rotation;

	D3DXMATRIX rotationX, rotationY;
	D3DXMatrixRotationX( &rotationX, m_rotation.x );
	D3DXMatrixRotationY( &rotationY, m_rotation.y );
	D3DXMatrixRotationZ( &m_rotationMatrix, m_rotation.z );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationX );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationY );
}


void physical::AddRotation( float x, float y, float z )
{
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;

	D3DXMATRIX rotationX, rotationY;
	D3DXMatrixRotationX( &rotationX, m_rotation.x );
	D3DXMatrixRotationY( &rotationY, m_rotation.y );
	D3DXMatrixRotationZ( &m_rotationMatrix, m_rotation.z );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationX );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationY );
}


void physical::AddRotation( D3DXVECTOR3 rotation )
{
	m_rotation += rotation;

	D3DXMATRIX rotationX, rotationY;
	D3DXMatrixRotationX( &rotationX, m_rotation.x );
	D3DXMatrixRotationY( &rotationY, m_rotation.y );
	D3DXMatrixRotationZ( &m_rotationMatrix, m_rotation.z );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationX );
	D3DXMatrixMultiply( &m_rotationMatrix, &m_rotationMatrix, &rotationY );
}


D3DXVECTOR3 physical::GetRotation()
{
	return m_rotation;
}


void physical::SetVelocity( float x, float y, float z )
{
	m_velocity.x = x;
	m_velocity.y = y;
	m_velocity.z = z;
}

void physical::SetVelocity( D3DXVECTOR3 velocity )
{
	m_velocity = velocity;
}


void physical::AddVelocity( float x, float y, float z )
{
	m_velocity.x += x;
	m_velocity.y += y;
	m_velocity.z += z;
}


void physical::AddVelocity( D3DXVECTOR3 velocity )
{
	m_velocity += velocity;
}


D3DXVECTOR3 physical::GetVelocity()
{
	return m_velocity;
}

void physical::SetSpin( float x, float y, float z )
{
	m_spin.x = x;
	m_spin.y = y;
	m_spin.z = z;
}

void physical::SetSpin( D3DXVECTOR3 spin )
{
	m_spin = spin;
}

void physical::AddSpin( float x, float y, float z )
{
	m_spin.x += x;
	m_spin.y += y;
	m_spin.z += z;
}

void physical::AddSpin( D3DXVECTOR3 spin )
{
	m_spin = spin;
}

D3DXVECTOR3 physical::GetSpin()
{
	return m_spin;
}