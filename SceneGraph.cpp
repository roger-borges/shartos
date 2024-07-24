#include "SceneGraph.h"

void SceneGraph::addObject(object* obj)
{
	std::list<std::string>::const_iterator itr= obj->getTypeList().begin();
	for(; itr!=obj->getTypeList().end(); ++itr){
		_typeLists[ *itr ].push_back(obj);
	}
}

std::list<object*> SceneGraph::getObjects(const std::string& type)
{
	return _typeLists[type];
}

std::list<std::string> SceneGraph::queryObjects()const
{ 
	std::list<std::string> typeList; 
	for(std::map<std::string,std::list<object*> >::const_iterator itr = typeList.begin(); itr!=typeList.end(); ++itr)
	  { 
		   typeList.push_back(itr->first); 
	  } 
      return typeList; 
 } 

