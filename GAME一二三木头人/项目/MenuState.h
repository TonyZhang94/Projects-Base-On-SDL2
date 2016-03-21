#ifndef __MSMSMS__
#define __MSMSMS__

#include "GameState.h"
#include "GameObject.h"

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }
		// call back functions for menu items
private:
	static void s_menuToPlay();
	static void s_exitFromMenu();
private:
	static const std::string s_menuID;
	vector<GameObject*> m_gameObjects;
};




#endif 