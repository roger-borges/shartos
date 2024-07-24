#ifndef _inputSybsystemH_
#define _inputSybsystemH_

#include "input.h"
#include "camera.h"
#include "subSystem.h"

class inputSubsystem : public subSystem
{
private:
	Input* _input;
protected:
public:
	inputSubsystem();
	void execute(SceneGraph*);
};



#endif