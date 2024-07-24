	#include "soundSubsystem.h"

// Sound system constructor
soundSubsystem::soundSubsystem()
{
	_aud = new audible();
	_aud->loadSound("laser.wav");
}

soundSubsystem::~soundSubsystem()
{
	_aud->startSound("laser.wav");
}


void soundSubsystem::execute(SceneGraph* scene)
{	
	//compare  the this->time against the last time in the collision part of the scenegraph
	//if the scenegraph time is greater than the this->time then play the collision sound
	//get the current time and assign it to this->time
	//if( MUSIC_ISDONE) _performance->Stop();
	// Shut down program.	

  list<object*> l=scene->getObjects("audio");
  list<object*>::iterator itr=l.begin();
  for(; itr!=l.end(); ++itr)
  { 
	  audible* Graobj=0; 
	  Graobj= dynamic_cast<audible*>(*itr); 
	  if(!Graobj)
	  {
		  //doSomeErrorFunction(); 
	  }
	  else
	  { 
		  Graobj->stopMusic();
	  }
  }

}