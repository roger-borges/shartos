#include "physicsSubsystem.h"
#include "physical.h"
void physicsSubsystem::execute(SceneGraph* sg){
	list<object*> l;
	l=sg->getObjects("physical");
   list<object*>::iterator itr=l.begin();
   for(; itr!=l.end(); ++itr){
      physical* psyobj=0;
      psyobj=dynamic_cast<physical*>(*itr);
      if(!psyobj){
         //doSomeErrorFunction();
      }
      else{
        
		unsigned long currentTime = timeGetTime();
		static unsigned long lastTime = currentTime;
		float elapsed = ( currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		  
		  
		  
		  psyobj->update(elapsed);
      }
   }

}