#include "graphicsSubsystem.h"
#include "visual.h"
#include "camera.h"


void graphicsSubsystem::execute(SceneGraph* scene)
{
	 
  D3DXMATRIX* viewMatrix = new D3DXMATRIX();list<object*> cameras = scene->getObjects("camera");
  if(cameras.empty())
  {D3DXMatrixIdentity(viewMatrix);}
  else
  {
	  list<object*>::iterator camitr=cameras.begin();
	  *viewMatrix = ((*camitr)->getMatrix());
  }
  list<object*> l=scene->getObjects("visual");
  list<object*>::iterator itr=l.begin();
  for(; itr!=l.end(); ++itr)
  { 
	  visual* Graobj=0; 
	  Graobj= dynamic_cast<visual*>(*itr); 
	  if(!Graobj)
	  {
		  //doSomeErrorFunction(); 
	  }
	  else
	  { 
		  Graobj->draw();
	  }
  }
}