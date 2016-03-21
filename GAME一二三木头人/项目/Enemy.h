#ifndef _EEEEE_
#define _EEEEE_

#include "utility.h"
#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(const LoaderParams* pParams) : GameObject(pParams) {}
	void update();
	//void clean() {}
};

#endif