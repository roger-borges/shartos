#ifndef SCRIPT_H
#define SCRIPT_H

//#include <dshow.h>
//#include<mmsystem.h>
//#include "music.h"

//make sure managed extensions are turned to Yes in the project properties
#include<d3dx9.h>
#include<vector>
#include<string>
#include <iostream>
#include<list>
#using <mscorlib.dll>
#using <System.Xml.dll>
using namespace std;
using std::list;
using namespace System;
using namespace System::Xml;
//using namespace System::Runtime::InteropServices;
using System::Runtime::InteropServices::Marshal;
#include<mmsystem.h>

class World
{
private:
typedef struct Ammo{
	string name;//Name of bullet
	string type;//type of ammo
	string mesh_path;//location of .X file
	string damage_animation;//path to damage animation file
	int ammo_out;//number that ammo runs out at
	long damage;//how damaging bullet can be(potential not actual)

	Ammo()
	{ name=""; type=""; mesh_path=""; damage_animation=""; 
	  damage=0; ammo_out=0;
	}
}Ammo;

typedef struct Character{
	string name;//name of character
	string type;//type of character
	string mesh_path;//path of .X file
	string texture;//path of texture file;
	string AI_file;//path of AI script
	D3DXVECTOR3 attach_point;//point weapon will be attached on character
	D3DXVECTOR3 attach_direction;//direction weapon will be attached
	float hit_points;//how vulnerable character is
	float armor;//how much armor character loads up with
	float speed;//how fast character moves

	Character()
	{ name=""; type=""; mesh_path=""; texture=""; AI_file="";
	  attach_point=D3DXVECTOR3(0.0f,0.0f,0.0f); 
	  attach_direction=D3DXVECTOR3(0.0f,0.0f,0.0f);
	  hit_points=7; armor=50; speed=25;
	}
}Character;

typedef struct Weapon{
	string name;//name of weapon
	string type;//type of weapon?
	string mesh_path;//location of x file
	string texture;//location of texture
	list<std::string> ammo_type;//different types of ammo weapon can have
	D3DXVECTOR3 attach_point;//location weapon will be on person
	float damage;//strength of weapon - used it conjunction with ammo damage
	float bull_speed;//speed of bullet
	float fire_frequency;//how quickly you can fire multiple bullets(per second)
	float accuracy;//accuracty of weapon

	Weapon()
	{
		name=""; type=""; mesh_path=""; damage=0; bull_speed=0; fire_frequency=0;
		texture=""; ammo_type.clear(); attach_point=D3DXVECTOR3(0.0f,0.0f,0.0f);
		accuracy=0;
	}
}Weapon;

public:
	std::string name;//name of world
	std::string lighting;
	D3DXVECTOR3 gravity;//gravity effects
	std::string mesh_path;//location of x file
	std::list<Weapon> Weap;//list of weapons to be used in world
	std::list<Ammo> Ammos;//list of ammo to be used in game
	std::list<Character> Characters;
	std::list<std::string>playlist;

	typedef Weapon weep;
	typedef Ammo ammo;
	typedef Character character;
	
	std::list<std::string> loadPlaylist(String* path);
	 Weapon loadWeapon(String* path);
	 Ammo loadAmmo(String* path);
	 Character loadCharacter(String* path);
	virtual World XmlLoadWorld(std::string fileName);

	World()
	{
		Weapon(); Ammo(); Character();
		name=""; lighting=""; mesh_path=""; gravity=D3DXVECTOR3(0.0f,0.0f,0.0f);
		Weap.clear(); Ammos.clear(); Characters.clear();
	}
	~World();
};

class maps{
	private:
		struct name{
			std::string name_map;
		};
		char* directory;
		std::list<std::string> maps_list;
		std::list<std::string> maps_name_list;
	public:
		maps(String*);
		~maps();
		std::list<std::string> get_list(){return maps_list; }
		std::list<std::string> get_name_list(){return maps_name_list; }
		char* getdir(){return directory;}
};

#endif