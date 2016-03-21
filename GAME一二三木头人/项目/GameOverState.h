#ifndef __GOSGOS__
#define	__GOSGOS__

#include "GameState.h"
#include "GameObject.h"

enum over_states
{
	LOSE = 0,
	WIN = 1,
};

class GameOverState : public GameState
{
public:
	GameOverState(int state) : m_state(state) {}
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void setS(int s) { m_state = s; }
	virtual void setPS(int ps) { pre_sta = ps;}
	virtual std::string getStateID() const {return s_gameOverID;}
private:
	static void s_gameOverToMain();
	static void s_restartPlay();
	static const string s_gameOverID;
	std::vector<GameObject*> m_gameObjects;
	int m_state;   //要显示输赢的状态
	static int pre_sta;   //OVER之前的状态
};






#endif