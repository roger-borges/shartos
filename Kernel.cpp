#include "Kernel.h"


void Kernel::executeNextSubsystem(){
//loop through subsystems, executing them with the current scene
	if(_current_scene_p){
		std::map<std::string, subSystem*>::iterator subsystem_itr=_subsystems.begin();
		for(; subsystem_itr!=_subsystems.end(); ++subsystem_itr){
			subsystem_itr->second->execute(_current_scene_p);
		}
	}
	else{
		//trying to use a null scene, not good
	}
}

void Kernel::addSubsystem(const std::string& name, subSystem* ss){
	_subsystems[name]=ss;
}
void Kernel::removeSubsystem(const std::string& name){
	delete _subsystems[name];
	_subsystems.erase(_subsystems.find(name));
}
std::list<std::string> Kernel::querySubsystems()const{
	std::list<std::string> names;
	std::map<std::string, subSystem*>::const_iterator subsystem_itr=_subsystems.begin();
	for(; subsystem_itr!=_subsystems.end(); ++subsystem_itr){
		names.push_back(subsystem_itr->first);
	}
	return names;
}
void Kernel::clearSubsystems(){
	_subsystems.clear();
}


void Kernel::addScene(const std::string& name, SceneGraph* sg){
	_loaded_scenes[name]=sg;
}
void Kernel::removeScene(const std::string& name){
	delete _loaded_scenes[name];
	_loaded_scenes.erase(_loaded_scenes.find(name));
}
std::list<std::string> Kernel::queryScenes()const{
	std::list<std::string> names;
	std::map<std::string, SceneGraph*>::const_iterator scenegraph_itr=_loaded_scenes.begin();
	for(; scenegraph_itr!=_loaded_scenes.end(); ++scenegraph_itr){
		names.push_back(scenegraph_itr->first);
	}
	return names;
}
void Kernel::clearScenes(){
	_loaded_scenes.clear();
}
void Kernel::setScene(const std::string& name){
	
	(_loaded_scenes.find(name)!=_loaded_scenes.end())?_current_scene_p=_loaded_scenes[name]:throw std::string("BAD THINGS");
}