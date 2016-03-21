#ifndef __PSPSPS__
#define __PSPSPS__

#include "GameState.h"
#include "GameObject.h"

class PlayState : public GameState
{
public: 
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual void setS(int s) { m_s = s; }
	virtual string getStateID() const { return s_playID; }
private:
	static const string s_playID;
	int p_id;    //若改成全局变量，会出错？？？
	int m_s;   //哪个难度的游戏状态
	vector<GameObject*> m_gameObjects;
};


#endif 