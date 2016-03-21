#ifndef __PLA__
#define __PLA__

#include "GameObject.h"
#include "Vector2D.h"

class Player : public GameObject
{
public:
	Player(const LoaderParams* pParams, Vector2D* V , int n=1 ,int t = 200, int initial = 0);
	virtual void update();
	/*virtual void setN(int n) { m_n = n; }
	virtual void setVelocity(float x, float y) { m_velocity.setX(x); m_velocity.setY(y); }*/
	virtual ~Player() {}
	/*void clean() {}*/
private:
	/*static int id;*/
	Vector2D  m_velocity;
	int m_t;   //m_t越大，动作速度越小
	int m_n;
	int m_init;
};

#endif
