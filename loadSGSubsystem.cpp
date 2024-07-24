#include "loadSGSubsystem.h"
#include "audible.h"
#include "game/skybox.h"

void loadSGSubsystem::execute(SceneGraph* scene)
{
	scene->addObject(new Camera(Camera::CameraType::LANDOBJECT));
	
//	scene->addObject((object*)
	scene->addObject((object*)new skybox(scene)); 


	scene->addObject(new Terrain("level4.raw", 256, 256, 10,  1.0f, 0.0f, 1.0f, 1.0f));
	
//	scene->addObject(new staticMesh("tiger.x"));
	scene->addObject(new staticMesh("meshes/factory.x"));

//	static audible* tempAud = new audible();
//	tempAud->loadSound("laser.wav");
//	scene->addObject((object*)tempAud);
//	scene->addObject((object*)new audible());

		
}
loadSGSubsystem::loadSGSubsystem(std::string pathToFile):worldFileName(pathToFile){}