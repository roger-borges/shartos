#ifndef sub_sys_h
#define sub_sys_h

#include "SceneGraph.h"

class subSystem
{
public:
	virtual void execute(SceneGraph*)=0;
};
#endif sub_sys_h