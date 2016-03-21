#ifndef __LSLSLS__
#define __LSLSLS__

#include "utility.h"
#include "GameState.h"
#include "GameObject.h"

enum p_states
{
	LEVEL1 = 1,
	LEVEL2 = 2,
	LEVEL3 = 3
};

class LevelState : public GameState
{
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const {return s_menuID ;}

private:
	static void s_ToLevel1();
	static void s_ToLevel2();
	static void s_ToLevel3();
private:
	static const string s_menuID;
	vector< GameObject* > m_gameObjects;
};



#endif