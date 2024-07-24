#ifndef _skyboxH_
#define _skyboxH_

#include "../Quad.h"
#include "../object.h"
#include "../SceneGraph.h"

class skybox : public object
{
public:
	skybox(SceneGraph*);
	void walk(float);
	void setAngleVector(D3DXVECTOR3 angle){angleVector = angle;}
//			graphicsObject():object(std::string("renderable")){}
	Quad* left;
	Quad* right;
	Quad* front;
	Quad* back;
	Quad* top;
	Quad* bottom;

private:
	D3DXVECTOR3 angleVector;

protected:
};

#endif _skyboxH_