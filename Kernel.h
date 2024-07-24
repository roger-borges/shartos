#ifndef kernel_h
#define kernel_h

#include <map>

#include "SceneGraph.h"
#include "subSystem.h"

class Kernel
{
public:
	void executeNextSubsystem();
	void addSubsystem(const std::string&, subSystem*);
	void removeSubsystem(const std::string&);
	std::list<std::string> querySubsystems()const;
	void clearSubsystems();
	void addScene(const std::string&, SceneGraph*);
	void removeScene(const std::string&);
	std::list<std::string> queryScenes()const;
	void clearScenes();
	void setScene(const std::string&);
	
private:
	
	std::map<std::string, subSystem*> _subsystems;
	std::map<std::string, SceneGraph*> _loaded_scenes;
	SceneGraph* _current_scene_p;

};
#endif kernel_h