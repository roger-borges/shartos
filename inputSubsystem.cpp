#include "inputSubsystem.h"
#include "Quad.h"
#include "game/skybox.h"
#include "Terrain.h"
#include "staticMesh.h"


#include <typeinfo>

void inputSubsystem::execute(SceneGraph *maps)
{
	_input->Update();
	std::list<object*> objptr = maps->getObjects("camera");
	
	if(objptr.empty())
	{	::MessageBox(0,"This list is empty","Camera(inputSubsystem)",0); return;
	}
	
	list<object*>::iterator itr=objptr.begin(); 
	Camera* cam = dynamic_cast<Camera*>(*itr);

///////////////////////////////////////////////////////////////////////////////////

	std::list<object*> objptr2 = maps->getObjects("skybox");
	std::list<object*> objptr3 = maps->getObjects("terrain");
	
	Terrain* ter;
	if(!objptr3.empty())
	{
		list<object*>::iterator itr3=objptr3.begin();
		ter = dynamic_cast<Terrain*>(*itr3);
	
		if(objptr2.empty())
		{	::MessageBox(0,"This list is empty","Skybox(inputSubsystem)",0); return;
		}
	}
	
	list<object*>::iterator itr2=objptr2.begin(); 
	skybox* skyBox = dynamic_cast<skybox*>(*itr2);

///////////////////////////////////////////////////////////////////////////////////
//getting audible object
//	static audible* soundSystem;
//	std::list<object*> objAud = maps->getObjects("audible");
//	int a = objAud.size();
//		if(a == 1)
//			::MessageBox(0,"greater than 1","",0); 
//	if(!objAud.empty())
//	{
//		if(0 == (soundSystem = dynamic_cast<audible*>(*objAud.begin())))
//			::MessageBox(0,"crappers","Object to Audible",0);
//		if(soundSystem)
//			::MessageBox(0,"good","",0);
//	}



///////////////////////////////////////////////////////////////////////////////////
	
	static bool jump = false;
	static bool up = false;
	static int jumpCount = 100;
	static float down = -1.0;

	if(_input)
	{
		if(_input->GetKeyPress(DIK_W,true))
		{
			//::MessageBox(0,"you pushed w","w",0);
			cam->walk(3.0f);
			skyBox->walk(3.0f);
		}
		if(_input->GetKeyPress(DIK_S,true))
		{
			//::MessageBox(0,"you pushed s","s",0);
			cam->walk(-3.0f);
			skyBox->walk(-3.0f);
		}
		if(_input->GetKeyPress(DIK_A,true))
		{
			//::MessageBox(0,"you pushed a","a",0);
			cam->strafe(-3.0f);
				skyBox->walk(-3.0f);
		}
		if(_input->GetKeyPress(DIK_D,true))
		{
			//::MessageBox(0,"you pushed d","d",0);
			cam->strafe(3.0f);
			skyBox->walk(3.0f);
		}
		if(_input->GetKeyPress(DIK_R,true))
		{
			//::MessageBox(0,"escape!","esc",0);
			cam->fly(1.4f);
		}
		if(_input->GetKeyPress(DIK_F,true))
		{
			//::MessageBox(0,"escape!","esc",0);
			cam->fly(-1.4f);
		}
		if(_input->GetKeyPress(DIK_SPACE,false))
		{
			//::MessageBox(0,"space!","space",0);
		jump = true;	
		up = true;
		down = -1.0;
		}
		if(_input->GetButtonPress(0))
		{
			//static audible* temp = new  audible();
			//static int i=0;
			//if(i==0)
			//{
			//	temp->loadSound(std::string("laser.wav"));
			//	i++;
			//}
			//if(soundSystem)
			//	soundSystem->startSound(std::string("laser.wav"));
			//else
			//	::MessageBox(0,"nope","",0);
		}

		/*if(_input->GetKeyPress(DIK_ESCAPE,false))
		{	//close the program
			PostQuitMessage(0);
		}*/

		cam->yaw(_input->GetDeltaX());
		cam->pitch(_input->GetDeltaY());

		static D3DXMATRIX cameraMatrix;
		static int i=0;
		if(i==0){ i++;
			D3DXMatrixIdentity(&cameraMatrix);
		}

		//cameraMatrix = cam->setViewMatrix();
		cam->getViewMatrix(&cameraMatrix);
//		skyBox->setAngleVector(D3DXVECTOR3(cameraMatrix(3,0),cameraMatrix(3,1),cameraMatrix(3,2)));
		skyBox->setAngleVector(cam->getPosition());
		cam->RepositionBoundingVolume(&cameraMatrix);

		static float elapsed = 0.0;
		static float camh = cam->getPosition().y;
		static float cx = 0.0;
		static D3DXVECTOR3 oldPos(0.0,0.0,0.0);

		cam->_device->SetTransform(D3DTS_VIEW, &cameraMatrix);

		if(ter)
		{
		static float old = ter->getHeight(cam->getPosition().x,cam->getPosition().z);
		//cam->setMatrix(cameraMatrix);

		if(jump)
		{
			if(up)
			{
			
				
					if(jumpCount<10)
					{
						cam->fly(4.0);
						jumpCount--;
					}
					else{
						cam->fly(1.5);
						jumpCount--;

						}
			
			
			if(jumpCount<1)
					{
					jumpCount = 25;
					up = false;
					}
			
			}
			else
			{
				if(cam->getPosition().y < ter->getHeight(cam->getPosition().x,cam->getPosition().z)+30)
				{ jump = false;}
				cam->fly(down);
				down = down - 0.1;
				}
			
		
		
		
		}
		else{
			static D3DXVECTOR3 oldPos(0.0,0.0,0.0);
			D3DXVECTOR3 position;
			cam->getPosition(&position);
			if(ter->getHeight(position.x,position.z)!=old)
			{
				camh= cam->getPosition().y-30;
			cx = ter->getHeight(position.x,position.z)-camh;
			elapsed=0.0;
			}
			float height = ter->getHeight(position.x,position.z);
			
			if(elapsed < 1.0)
			{
				elapsed += .30;
			}
			
			if(cx < 10)
			{
			position.y = position.y + cx*elapsed;
			oldPos.x = position.x;
			oldPos.z = position.z;
			}
			else
			{
			 position.x = oldPos.x;
			 position.z = oldPos.z;
			}
			//position.y = (height+30);
			cam->setPosition(&position);
			/*
			if((cam->getPosition().y > ter->getHeight(cam->getPosition().x+5,cam->getPosition().z+5)+5))
			{

				//while(cam->getPosition().y > ter->getHeight(cam->getPosition().x,cam->getPosition().z)+5)
				//{
				cam->fly(-1.0);
			//}
			
			
			}
			else if(cam->getPosition().y < ter->getHeight(cam->getPosition().x,cam->getPosition().z))
			{
				//while(cam->getPosition().y < ter->getHeight(cam->getPosition().x,cam->getPosition().z)+20)
				//{
					cam->fly(5.0);
				//}
				
			}	
			else
			{
			}
			*/
		}
		}

		//cam->_device->
//		object::_device->SetTransform(D3DTS_VIEW, &cameraMatrix);

//		static Quad* Box = new Quad(-10.0f,10.0f,-10.0f,10.0f,-1.0f,-1.0f,0.0f,0.0f,-1.0f,"randomness.jpg");
//		static IDirect3DTexture9* Tex = 0;
/*		static int i=0;
		if(i==0)
		{
			D3DXCreateTextureFromFile(cam->_device,"randomness.jpg",&Tex);
			i++;
		}
*///		Box->draw();
	}
	else
		::MessageBox(0,"bad input device","",0);
}

inputSubsystem::inputSubsystem()
{
	_input = new Input(::GetActiveWindow());
}