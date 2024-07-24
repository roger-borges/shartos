
#include "scripting.h"


//conversion macro for std::string to String*
String* stdToManagedStr(string convert_this)
{
	String* end_result;
	const char* newpath=convert_this.c_str();
	end_result=newpath;
	return end_result;		
}

//String* to std::string converstion macro
string convertStrings(String* convert_this)
{char *cPointer =(char *) Marshal::StringToHGlobalAnsi(convert_this).ToPointer();
	return( (string)cPointer);}



//String* to char* conversion macro
char* convertToChars(String* convert_this)
{return (char *) Marshal::StringToHGlobalAnsi(convert_this).ToPointer();}

//#include "music.h"
//			CMP3_MCI mp3Player;



World::Weapon World::loadWeapon(String* path)
{
	//Console::WriteLine(path); Console::WriteLine(S"just wrote path");
	Weapon wep;
	try
	{
		String* format = S"XmlNodeType::{0,-12}{1,-10}{2}";	
		XmlTextReader* xmlcont = new XmlTextReader(path);
		while(xmlcont->Read())
		{
			//Console::WriteLine(S"loop");
			if(0==String::Compare(xmlcont->Name,S"name") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				wep.name=convertStrings(xmlcont->Value);
//				//cout<<wep.name;
			}
			else if(0==String::Compare(xmlcont->Name,S"type") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				wep.type=convertStrings(xmlcont->Value);
//				//cout<<wep.name;
			}
			if(0==String::Compare(xmlcont->Name,S"texture") && XmlNodeType::Element==xmlcont->NodeType)
			{
				//Console::Write(S"TEXTURe: ");
				xmlcont->Read();
				//xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);
				wep.texture=convertStrings(xmlcont->Value);
				////cout<<"texture: "<<wep.texture<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"mesh_path") && XmlNodeType::Element==xmlcont->NodeType)
			{
//				//cout<<"MESH_PATH";
				xmlcont->Read();
				wep.mesh_path=convertStrings(xmlcont->Value);
//				//cout<<wep.mesh_path;
			}
			else if(0==String::Compare(xmlcont->Name,S"damage") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
				wep.damage=(float)atof(convertToChars(xmlcont->Value));
//				//cout<<"damage"<<wep.damage<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"accuracy") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
				wep.accuracy=(float)atof(convertToChars(xmlcont->Value));
//				//cout<<"damage"<<wep.damage<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"bullet_speed") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
				wep.bull_speed=(float)atof(convertToChars(xmlcont->Value));
//				//cout<<"bullet speed "<<wep.bull_speed<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"shots_per_second") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
				wep.fire_frequency=(float)atof(convertToChars(xmlcont->Value));
//				//cout<<"frequency "<<wep.fire_frequency<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"ammo") && XmlNodeType::Element==xmlcont->NodeType)
			{
				//Console::WriteLine(S"AMMO");
				xmlcont->Read();
				xmlcont->Read();
				while(!(0==String::Compare(xmlcont->Name,S"ammo") && XmlNodeType::EndElement==xmlcont->NodeType))
				{
					if(0==String::Compare(xmlcont->Name,S"ammo_type") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
				//		Console::WriteLine(S"AMMO TYPE");
				//		Console::WriteLine(xmlcont->Value);
						wep.ammo_type.push_back(convertStrings(xmlcont->Value));
				//		//cout<<"ammo type: "<<wep.ammo_type.front()<<endl;
					}
					xmlcont->Read();
				}
			}
			else if(0==String::Compare(xmlcont->Name,S"attach_point") && XmlNodeType::Element==xmlcont->NodeType)
			{
				float x=0,y=0,z=0;
				//Console::WriteLine(S"ATTACH POINT");
				xmlcont->Read();
				while(!(0==String::Compare(xmlcont->Name,S"attach_point") && XmlNodeType::EndElement==xmlcont->NodeType))
				{
					if(0==String::Compare(xmlcont->Name,S"x") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						//Console::Write(S"X: "); Console::WriteLine(xmlcont->Value);
						x=(float)atof(convertToChars(xmlcont->Value));
						//cout<<"X: "<<x<<endl;
					}
					else if(0==String::Compare(xmlcont->Name,S"y") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						//Console::Write(S"Y: "); Console::WriteLine(xmlcont->Value);
						y=(float)atof(convertToChars(xmlcont->Value));
						//cout<<"Y: "<<y<<endl;
					}
					else if(0==String::Compare(xmlcont->Name,S"z") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						//Console::Write(S"Z: "); Console::WriteLine(xmlcont->Value);
						z=(float)atof(convertToChars(xmlcont->Value));
						//cout<<"Z: "<<z<<endl;
					}
					xmlcont->Read();
				}
				if(0==String::Compare(xmlcont->Name,S"attach_point") && XmlNodeType::EndElement==xmlcont->NodeType)
				{
					wep.attach_point=D3DXVECTOR3(x,y,z);
				}
			}
		}
	}
	catch (Exception* ex)
	{
		Console::WriteLine(ex->Message);

	}

	return wep;
}

World::Ammo World::loadAmmo(String* path)
{
	Ammo arsenal;
	

	try{
		String* format = S"XmlNodeType::{0,-12}{1,-10}{2}";	
		XmlTextReader* xmlcont = new XmlTextReader(path);
		while(xmlcont->Read())
		{
			if(0==String::Compare(xmlcont->Name,S"damage") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				arsenal.damage=atol(convertToChars(xmlcont->Value));
			//	cout<<"ARSENAL DAMAGE: "<<arsenal.damage<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"ammo_out") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				arsenal.ammo_out=atoi(convertToChars(xmlcont->Value));
			//	cout<<"ARSENAL AMMO OUT: "<<arsenal.ammo_out<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"damage_animation") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				arsenal.damage_animation=convertStrings(xmlcont->Value);
			//	cout<<"ARSENAL DAMAGE ANIMATION: "<<arsenal.damage_animation<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"mesh_path") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				arsenal.mesh_path=convertStrings(xmlcont->Value);
			//	cout<<"ARSENAL MESH PATH: "<<arsenal.mesh_path<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"type") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				arsenal.type=convertStrings(xmlcont->Value);
			//	cout<<"ARSENAL TYPE: "<<arsenal.type<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"name") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				arsenal.name=convertStrings(xmlcont->Value);
			//	cout<<"ARSENAL NAME: "<<arsenal.name<<endl;
			}


		}

	}
	catch (Exception* ex)
	{
		Console::WriteLine(ex->Message);

	}
//	cout<<endl;
	return arsenal;
}

World::Character World::loadCharacter(String* path)
{
	Character person;
	try{
		String* format = S"XmlNodeType::{0,-12}{1,-10}{2}";	
		XmlTextReader* xmlcont = new XmlTextReader(path);
		while(xmlcont->Read())
		{
			if(0==String::Compare(xmlcont->Name,S"attach_direction") && XmlNodeType::Element==xmlcont->NodeType)
			{
				float x1=0,y1=0,z1=0;
				while(!(0==String::Compare(xmlcont->Name,S"attach_direction") && XmlNodeType::EndElement==xmlcont->NodeType))
				{
					xmlcont->Read();
					if(0==String::Compare(xmlcont->Name,S"x") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						x1=(float) atof(convertToChars(xmlcont->Value));
					}
					else if(0==String::Compare(xmlcont->Name,S"y") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						y1=(float) atof(convertToChars(xmlcont->Value));
					}
					else if(0==String::Compare(xmlcont->Name,S"z") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						z1=(float) atof(convertToChars(xmlcont->Value));
					}
					else if(0==String::Compare(xmlcont->Name,S"attach_direction") && XmlNodeType::EndElement==xmlcont->NodeType)
					{
						person.attach_direction=D3DXVECTOR3(x1,y1,z1);
						//cout<<"CHARACTER ATTACH DIRECTION: "<<x1<<" "<<y1<<" "<<z1<<endl;
					}

				}
			}
			else if(0==String::Compare(xmlcont->Name,S"attach_point") && XmlNodeType::Element==xmlcont->NodeType)
			{
				float x=0,y=0,z=0;
				while(!(0==String::Compare(xmlcont->Name,S"attach_point") && XmlNodeType::EndElement==xmlcont->NodeType))
				{
					xmlcont->Read();
					if(0==String::Compare(xmlcont->Name,S"x") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						x=(float) atof(convertToChars(xmlcont->Value));
					}
					else if(0==String::Compare(xmlcont->Name,S"y") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						y=(float) atof(convertToChars(xmlcont->Value));
					}
					else if(0==String::Compare(xmlcont->Name,S"z") && XmlNodeType::Element==xmlcont->NodeType)
					{
						xmlcont->Read();
						z=(float) atof(convertToChars(xmlcont->Value));
					}
					else if(0==String::Compare(xmlcont->Name,S"attach_point") && XmlNodeType::EndElement==xmlcont->NodeType)
					{
						person.attach_point=D3DXVECTOR3(x,y,z);
					//	cout<<"CHARACTER ATTACH POINT: "<<x<<" "<<y<<" "<<z<<endl;
					}

				}
			}
			else if(0==String::Compare(xmlcont->Name,S"speed") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.speed=(float)atof(convertToChars(xmlcont->Value));
			//	cout<<"CHARACTER SPEED: "<<person.speed<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"armor") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.armor=(float)atof(convertToChars(xmlcont->Value));
			//	cout<<"CHARACTER ARMOR: "<<person.armor<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"hit_points") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.hit_points=(float)atof(convertToChars(xmlcont->Value));
			//	cout<<"CHARACTER HIT POINTS: "<<person.hit_points<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"ai_file") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.AI_file=convertStrings(xmlcont->Value);
			//	cout<<"CHARACTER AI FILE: "<<person.AI_file<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"texture") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.texture=convertStrings(xmlcont->Value);
			//	cout<<"CHARACTER TEXTURE: "<<person.texture<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"mesh_path") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.mesh_path=convertStrings(xmlcont->Value);
			//	cout<<"CHARACTER MESH PATH: "<<person.mesh_path<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"type") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.type=convertStrings(xmlcont->Value);
			//	cout<<"CHARACTER TYPE: "<<person.type<<endl;
			}
			else if(0==String::Compare(xmlcont->Name,S"name") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
//				xmlcont->Read();
				//Console::WriteLine(xmlcont->Value);Console::WriteLine(S"just wrote name");
				person.name=convertStrings(xmlcont->Value);
			//	cout<<"CHARACTER NAME: "<<person.name<<endl;
			}
		}
	}
	catch (Exception* ex)
	{
		Console::WriteLine(ex->Message);

	}
//	cout<<endl;
	return person;
}
/*
std::list<std::string> World::loadPlaylist(String* path)
{
	XmlTextReader* xmlcont = new XmlTextReader(path);
	std::list<std::string> Play;
	try
	{
		while(!(0==String::Compare(xmlcont->Name,S"music") && XmlNodeType::EndElement==xmlcont->NodeType))
		{
			xmlcont->Read();
			if(0==String::Compare(xmlcont->Name,S"song") && XmlNodeType::Element==xmlcont->NodeType)
			{
				xmlcont->Read();
	
				mp3Player.Load(convertStrings(xmlcont->Value));
				mp3Player.Play();
				LPCSTR name=convertStrings(xmlcont->Value).c_str();
				
				//printf("%s",name);
				cout<<convertStrings(xmlcont->Value).c_str();
				MCIDEVICEID mcid=mciGetDeviceID("./load/music/Going.mp3") ;
				UINT a; //MCI_STATUS b;
				//cout<<mp3Player.GetFileName();
		//		std::string na; cout<<na.c_str();
				for(;;){
				a=mciSendCommand(mcid,MCI_CDA_STATUS_TYPE_TRACK ,NULL,NULL);
				cout<<MCI_STATUS_START   <<" a: "<<a<<endl;}
				//for(;;)
				//{//if(i==-1000000)
//				a=mciSendCommand(mcid,a,NULL,NULL);
			//	for(;;) cout<<"a";
		//		printf("%d\n",a);
					
					
				//}
			}
		}
	}
	catch (Exception* ex)
	{
		Console::Write(ex->Message);Console::Write(S"ROGER BORGES");
	}

	return Play;
}
*/

World World::XmlLoadWorld(std::string fileName)
{
	World this_world;
	String* file = stdToManagedStr(fileName);
	//String* fileName2=S"./load/maps/mainworld.xml";
	
//	this_world.Weap.front().name;
	try
	{
		String* format = S"XmlNodeType::{0,-12}{1,-10}{2}";	

		XmlTextReader* xmlreader = new XmlTextReader(file);
		while (xmlreader->Read())
		{
			String* out = String::Format(format, __box(xmlreader->NodeType),xmlreader->Name,xmlreader->Value);
			
			if(0==xmlreader->Name->Compare(xmlreader->Name,S"name") && XmlNodeType::Element==xmlreader->NodeType)
			{
				String* state=S"start";
				xmlreader->Read();
				while(0!=String::Compare(state,S"exit"))
				{
				//	Console::WriteLine(S"NAME");
					if(xmlreader->Value!=S"")
					{	
						this_world.name=convertStrings(xmlreader->Value);
						////cout<<this_world.name<<endl;
						state=S"exit";
					}
					else if(xmlreader->Name==S"name")
						state=S"exit";
					else
						Console::WriteLine(S"I don't understand world name");
				
				}
			}
		/*	else if(0==String::Compare(xmlreader->Name,S"music") && XmlNodeType::Element==xmlreader->NodeType)
			{
				xmlreader->Read();
//				Console::WriteLine(xmlreader->Value);
				this_world.playlist=loadPlaylist(xmlreader->Value);

//				xmlreader->Read();
			//	LPCWSTR path=(LPCWSTR)convertToChars(xmlreader->Value);
			//	Console::WriteLine(S"");
			//	Console::WriteLine(xmlreader->Value);
			//	cout<<(char*)path<<endl;
			//	Console::WriteLine(S"");
			}*/
			else if(0==xmlreader->Name->Compare(xmlreader->Name,S"lighting") && XmlNodeType::Element==xmlreader->NodeType)
			{
//				Console::WriteLine(S"LIGHTING");
				String* state=S"start";
				xmlreader->Read();
				while(state!=S"exit")
				{
				//	Console::WriteLine(S"loop");
					if(xmlreader->Value!=S"")
					{
						this_world.lighting=convertStrings(xmlreader->Value);
						////cout<<this_world.lighting<<endl;
						state=S"exit";
					}
					//else if(0==String::Compare(xmlreader->Name,S"lighting"))
					//	state=S"exit";
					else Console::WriteLine(S"I don't understand lighting.");
				}
			}
			else if(0==xmlreader->Name->Compare(xmlreader->Name,S"mesh") && XmlNodeType::Element==xmlreader->NodeType)
			{
//				Console::WriteLine(S"MESH");
				String* state=S"start";
				//xmlreader->Read();
				while(state!=S"exit")
				{
					xmlreader->Read();
					if(0!=String::Compare(xmlreader->Value,S""))
					{
						//Console::WriteLine(xmlreader->Value);
						this_world.mesh_path=convertStrings(xmlreader->Value);
						////cout<<this_world.mesh_path<<endl;
						state=S"exit";
					}
					//else Console::WriteLine(S"I don't understand world mesh.");
				}
			}
			//gravity load
			else if(0==xmlreader->Name->Compare(xmlreader->Name,S"gravity") && XmlNodeType::Element==xmlreader->NodeType)
			{				
				float x=0, y=0, z=0, exit=0;
				String* state1=S"start";
				int i;
				for(i=0;i<8;i++)
				{
				//	////cout<<i;
					//Console::WriteLine(S"trying");
					xmlreader->Read();
					if(0==String::Compare(xmlreader->Name,S"x") && XmlNodeType::Element==xmlreader->NodeType)
					{
						xmlreader->Read();
//						Console::WriteLine(S"X");
						//Console::WriteLine(xmlreader->Value);
						x=(float)atof(convertToChars(xmlreader->Value));
						////cout<<x<<endl;
					}
					else if(0==String::Compare(xmlreader->Name,S"y") && XmlNodeType::Element==xmlreader->NodeType)
					{
						xmlreader->Read();
//						Console::WriteLine(S"Y");
						//Console::WriteLine(xmlreader->Value);
						y=(float)atof(convertToChars(xmlreader->Value));
						////cout<<y<<endl;
					}
					else if(0==String::Compare(xmlreader->Name,S"z") && XmlNodeType::Element==xmlreader->NodeType)
					{
						xmlreader->Read();
//						Console::WriteLine(S"Z");
						//Console::WriteLine(xmlreader->Value);
						z=(float)atof(convertToChars(xmlreader->Value));
						////cout<<z<<endl;
					}
				}
				if(i==8)
				{
					this_world.gravity=D3DXVECTOR3(x,y,z);
				}

			}
			else if(0==xmlreader->Name->Compare(xmlreader->Name,S"weapons") && XmlNodeType::Element==xmlreader->NodeType)
			{
//				Console::WriteLine(S"WEAPONS");
				String* state=S"start"; String* temp_path="";
				//xmlreader->Read();
				while(0!=String::Compare(state,S"exit"))
				{
					xmlreader->Read();
					xmlreader->Read();
					if(0==String::Compare(xmlreader->Name,S"w"))
					{
						xmlreader->Read();
						//Console::WriteLine(xmlreader->Value);
						temp_path=xmlreader->Value;
//						Console::WriteLine(temp_path);
							//load into weapons linked list in this_world
							this_world.Weap.push_front(loadWeapon(temp_path));
//							//cout<<endl<<this_world.Weap.front().name<<"--woohoo"<<endl;
						xmlreader->Read();
						//state=S"exit";
					}
					else if(0==String::Compare(xmlreader->Name,S"weapons") && XmlNodeType::EndElement==xmlreader->NodeType)
						state=S"exit";
					else 
					{
//						Console::WriteLine(S"I don't understand weapons.");
//						Console::WriteLine(xmlreader->Name);
						state=S"exit";
					}
				}
			}
			else if(0==String::Compare(xmlreader->Name,S"ammo") && XmlNodeType::Element==xmlreader->NodeType)
			{
				//Console::WriteLine(S"BULLETS");
				String* state=S"start"; String* temp_path="";
				//xmlreader->Read();
				while(!(0==String::Compare(xmlreader->Name,S"ammo") && XmlNodeType::EndElement==xmlreader->NodeType))
				{
					xmlreader->Read();
					xmlreader->Read();
					if(0==String::Compare(xmlreader->Name,S"bullet"))
					{
						xmlreader->Read();
						//Console::WriteLine(xmlreader->Value);
						//temp_path=xmlreader->Value;
//						Console::WriteLine(temp_path);
							//load into weapons linked list in this_world
//							this_world.Ammos.Add(&loadAmmo(temp_path));
							this_world.Ammos.push_front(loadAmmo(xmlreader->Value));
						xmlreader->Read();
						//state=S"exit";
					}
					else if(XmlNodeType::EndElement!=xmlreader->NodeType && XmlNodeType::Element!=xmlreader->NodeType) 
					{
						//Console::Write(xmlreader->NodeType);
						Console::WriteLine(S"I don't understand ammo.");
//						Console::WriteLine(xmlreader->Name);
						state=S"exit";
					}
				}
			}
			else if(0==String::Compare(xmlreader->Name,S"characters") && XmlNodeType::Element==xmlreader->NodeType)
			{
//				Console::WriteLine(S"CHARACTERS");
				String* state=S"start"; String* temp_path="";
				//xmlreader->Read();
				while(!(0==String::Compare(xmlreader->Name,S"characters") && XmlNodeType::EndElement==xmlreader->NodeType))
				{
//					xmlreader->Read();
					xmlreader->Read();
					if(0==String::Compare(xmlreader->Name,S"ch_human") || 0==String::Compare(xmlreader->Name,"ch_alien"))
					{
						xmlreader->Read();
						//Console::WriteLine(xmlreader->Value);
						temp_path=xmlreader->Value;
						//Console::WriteLine(temp_path);
							//load into weapons linked list in this_world
//							this_world.Ammos.Add(&loadAmmo(temp_path));
							this_world.Characters.push_front(loadCharacter(temp_path));
//							//cout<<"character path: "<<this_world.Characters.front()"<<endl;
						xmlreader->Read();
						//state=S"exit";
					}
			//		else if(0==String::Compare(xmlreader->Name,S"ammo") && XmlNodeType::EndElement==xmlreader->NodeType)
			//			state=S"exit";
			//		else if(
			//		{Console::Write(xmlreader->Name);
			//			Console::WriteLine(S"I don't understand characters.");
//						
			//			state=S"exit";
			//		}
				}
				
			}
		}
	}
	catch (Exception* ex)
	{
		Console::Write(ex->Message);Console::WriteLine(S" Load World Error");
	}
	__finally
	{
	}

	return this_world;
}

World::~World()
{

}
/*
main()
{
	std::string path="./load/maps/mainworld.xml";
		World this_world=this_world.XmlLoadWorld(path);
		cout<<"-------------------------------------------"<<endl;
		cout<<"MAP PROPERTIES, LOADED FROM MAP SCRIPT FILE"<<endl;
		cout<<"-------------------------------------------"<<endl;
		cout<<"Map Name: "<<this_world.name<<endl;
		cout<<"Gravity Address: "<<this_world.gravity<<endl;
		cout<<"Lighting: "<<this_world.lighting<<endl;
		cout<<"Mesh Path: "<<this_world.mesh_path<<endl;
		cout<<endl;
	list<World::weep>::iterator liter; // Iterator for looping over list elements
	for ( liter = this_world.Weap.begin(); liter != this_world.Weap.end(); ++liter )
	{//iterating through list of weapons
		cout<<"Weapon Name: "<<liter->name<<endl;
		cout<<"Weapon Type: "<<liter->type<<endl;
		cout<<"Weapon Accuracy: "<<liter->accuracy<<endl;
		cout<<"Weapon Bullet Speed: "<<liter->bull_speed<<endl;
		cout<<"Weapon Damage: "<<liter->damage<<endl;
		cout<<"Weapon Mesh Path: "<<liter->mesh_path<<endl;
		cout<<"Weapon Fire Frequency: "<<liter->fire_frequency<<endl;
		cout<<"Weapon texture: "<<liter->texture<<endl;
		
		//every weapon uses different ammos types. here is the list of ammo types for this weapon
		list<string>::iterator ammotype;//list of ammo types this weapon can handle
		for(ammotype=liter->ammo_type.begin(); ammotype!=liter->ammo_type.end(); ++ammotype)
		{//iterating through list of ammo types for this weapon
			cout<<" Weapon's Ammo Types: "<<ammotype->c_str()<<endl;
		}
		  
	cout<<endl;}

	list<World::ammo>::iterator liter1; // Iterator for looping over list elements
	for ( liter1 = this_world.Ammos.begin(); liter1 != this_world.Ammos.end(); ++liter1 )
	{
		cout<<"Ammo Name: "<<liter1->name<<endl;
		cout<<"Ammo Type: "<<liter1->type<<endl;
		cout<<"Ammo Mesh Path: "<<liter1->mesh_path<<endl;
		cout<<"Ammo Damage Animation: "<<liter1->damage_animation<<endl;
		cout<<"Ammo Damage: "<<liter1->damage<<endl;
		cout<<"Ammo Ammo Out: "<<liter1->ammo_out<<endl<<endl;
	}

	list<World::character>::iterator liter2;
	for(liter2 = this_world.Characters.begin(); liter2 != this_world.Characters.end(); ++liter2)
	{
		cout<<"Character Name: "<<liter2->name<<endl;
		cout<<"Character Type: "<<liter2->type<<endl;
		cout<<"Character Mesh Path: "<<liter2->mesh_path<<endl;
		cout<<"Character Texture: "<<liter2->texture<<endl;
		cout<<"Character AI File: "<<liter2->AI_file<<endl;
		cout<<"Character Hit Points: "<<liter2->hit_points<<endl;
		cout<<"Character Armor: "<<liter2->armor<<endl;
		cout<<"Character Speed: "<<liter2->speed<<endl;
		cout<<endl;
	}


	system("PAUSE");
	
}*/