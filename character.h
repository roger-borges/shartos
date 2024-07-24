#ifndef CHARACTER_H
#define CHARACTER_H

#include "engine.h"
#include "object.h"
//#include "visual.h"
//#include "physical.h"
class visual:virtual object{};
class physical:virtual object{};

class character: visual, physical
{
private:
	
protected:
	std::list<weapon*> _weapons;
	std::list<weapon*>::iterator _current_weapon;
	std::list<std::pair<ammo*, int> > _ammo;
	

public:
	character(const std::string& character_file);
	virtual ~character(){}
	void run();
	void walk();
	void crouch();
	void jump();
	void turnLeft();
	void turnRight();
	void lookUp();
	void lookDown();

	void cycleWeaponLeft();
	void cycleWeaponRight();



};


#endif CHARACTER_H