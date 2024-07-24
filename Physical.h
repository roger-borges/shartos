#ifndef _phys
#define _phys

#include "object.h"

class physical : public virtual object
{
	public:
		physical();
		
		void SetTranslation(float x, float y, float z);
		void SetTranslation( D3DXVECTOR3 translation);
		void AddTranslation(float x, float y, float z);
		void AddTranslation( D3DXVECTOR3 translation);
		D3DXVECTOR3 GetTranslation();

		void SetRotation( float x, float y, float z);
		void SetRotation( D3DXVECTOR3 rotation);
		void AddRotation( float x, float y, float z);
		void AddRotation( D3DXVECTOR3 rotation);
		D3DXVECTOR3 GetRotation();

		void SetVelocity( float x, float y, float z);
		void SetVelocity( D3DXVECTOR3 velocity);
		void AddVelocity( float x, float y, float z);
		void AddVelocity( D3DXVECTOR3 velocity);
		D3DXVECTOR3 GetVelocity();

		void SetSpin( float x, float y, float z);
		void SetSpin( D3DXVECTOR3 spin);
		void AddSpin( float x, float y, float z);
		void AddSpin( D3DXVECTOR3 spin);
		D3DXVECTOR3 GetSpin();

		D3DXVECTOR3 GetFowardVector();
		D3DXVECTOR3 GetRightVector();

		void SetFriction(float friction);
		
		void update(float elapsedTime);


		

protected:
		
	D3DXVECTOR3 m_foward;
	D3DXVECTOR3 m_right;
		
	private:
	
	D3DXVECTOR3 m_translation; // Object's translation in 3D space.
	D3DXVECTOR3 m_rotation; // Object's rotation in radians.

	D3DXVECTOR3 m_velocity; // Object's velocity in units/second.
	D3DXVECTOR3 m_spin; // Object's spin in radians/second.

	D3DXMATRIX m_translationMatrix; // Translation matrix.
	D3DXMATRIX m_rotationMatrix; // Rotation matrix.

	float m_friction;
		
};

#endif _phys