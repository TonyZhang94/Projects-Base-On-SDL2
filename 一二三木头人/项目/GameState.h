#ifndef _GSGSGS_
#define _GSGSGS_

#include "utility.h"

class GameState
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual void setS(int s) {}
	virtual void setPS(int ps) {}
	virtual string getStateID() const = 0;
};

#endif 