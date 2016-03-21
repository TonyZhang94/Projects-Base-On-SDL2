#ifndef __GSMGSM__
#define __GSMGSM__

#include "GameState.h"

class GameStateMachine
{
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();
private:
	vector<GameState*> m_gameStates;
};



#endif