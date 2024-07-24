#ifndef NPCHARACTER_H
#define NPCHARACTER_H
#include "character.h"
class nonplayercharater :
	public character
{
private:
protected:
	ai::ann _ann;
public:
	nonplayercharater();
	~nonplayercharater();
	void executeANN(std::list<float>&);
};

#endif NPCHARACTER_H