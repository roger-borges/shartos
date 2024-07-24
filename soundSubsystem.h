#ifndef sound_sub_h
#define sound_sub_h

#define INITGUID

#include "audible.h"
#include "subSystem.h"


class soundSubsystem : public subSystem
{
private:
	static audible* _aud;

protected:

public:

	soundSubsystem();
	~soundSubsystem();
	void execute(SceneGraph*);

};



#endif sound_sub_h