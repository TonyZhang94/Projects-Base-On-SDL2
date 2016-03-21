#ifndef __PPSPPS__
#define __PPSPPS__

#include "GameState.h"
#include "GameObject.h"

class PauseState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual string getStateID() const { return s_pauseID; }
private:
	static void s_pauseToMain();
	static void s_resumePlay();
	static const string s_pauseID;
	vector<GameObject*> m_gameObjects;
};

#endif 