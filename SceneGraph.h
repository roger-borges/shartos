#ifndef scene_h
#define scene_h

#include<map>
//#include<list>

#include "engine.h"
#include "object.h"

class SceneGraph
{
private:
	std::map<std::string,std::list<object*> > _typeLists;

protected:

public:
	void addObject(object*);
	std::list<object*> getObjects(const std::string&);
	std::list<std::string> queryObjects()const;



};

#endif scene_h