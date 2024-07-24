#include "skybox.h"
#include <d3dx9.h>

skybox::skybox(SceneGraph *scene)
{
	object::addType(std::string("skybox"));
	D3DXMatrixIdentity(&objMatrix);

	left =		new Quad( 5120.0f,  -5120.0f, -5120.0f, 5120.0f, -5120.0f, -5120.0f, 0.0f, 0.0f, 1.0f, "images/4a.jpg",false);//left
	right =		new Quad( 5120.0f,   5120.0f, -5120.0f, 5120.0f, 5120.0f, -5120.0f, 0.0f, 0.0f, 1.0f, "images/3a.jpg",false);//right
	front =		new Quad( -5120.0f, -5120.0f, -5120.0f, 5120.0f, -5120.0f, 5120.0f, 0.0f, 0.0f, 1.0f, "images/1a.jpg",false);//front
	back =		new Quad( -5120.0f,  5120.0f, -5120.0f, 5120.0f, 5120.0f, 5120.0f, 0.0f, 0.0f, 1.0f, "images/2a.jpg",false);//back
	top =		new Quad( -5100.0f, -5100.0f, -5120.0f, 5120.0f, -5120.0f, 5120.0f, 0.0f, -1.0f, 0.0f, "images/5a.jpg",false);//top
	bottom =	new Quad( -5100.0f, -5100.0f, -5120.0f, 5120.0f, -5120.0f, 5120.0f, 0.0f, 1.0f, 0.0f, "images/6a.jpg",false);//bottom

	//left
	scene->addObject(left);
	//right
	scene->addObject(right);
	//front
	scene->addObject(front);
	//back
	scene->addObject(back);
	//top
	scene->addObject(top);
	//bottom
	scene->addObject(bottom);

//	left->newTexture("images/top.jpg");

}

void skybox::walk(float units)
{
//	_device->SetTransform(D3DTS_WORLD, &objMatrix);
//	objMatrix(0,2) *= units;
//	objMatrix(2,2) *= units;

	left->walk(units,angleVector);
	right->walk(units,angleVector);
	front->walk(units,angleVector);
	back->walk(units,angleVector);
	top->walk(units,angleVector);
	bottom->walk(units,angleVector);

}

