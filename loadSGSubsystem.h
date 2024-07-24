#ifndef loadSG_sub_h
#define loadSG_sub_h

#include "subSystem.h"
#include "camera.h"
#include "Quad.h"
#include "Terrain.h"
#include "staticMesh.h"
//#include "staticMesh.h"

class loadSGSubsystem : subSystem
{
private:
const std::string worldFileName;
protected:

public:

	void execute(SceneGraph*);
	loadSGSubsystem(std::string);



};



#endif loadSG_sub_h