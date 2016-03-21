#ifndef __GOGOGO__
#define __GOGOGO__

#include "utility.h"
#include "LoaderParams.h"
#include "Vector2D.h";

class GameObject
{
public:
	//void load(int x, int y, int width, int height, string textureID);
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}
	virtual Vector2D& getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	void setFrame(int f) { m_currentFrame = f;}
	/*virtual void setN(int n) {}
	virtual void setVelocity(float x, float y) {}*/
	int getFrame() { return m_currentFrame; }
protected:
	GameObject(const LoaderParams* pParams);
	virtual ~GameObject() {}
protected:
	string m_textureID;
	int m_currentFrame;
	int m_currentRow;
	int m_width;
	int m_height;

	Vector2D m_position;
};


#endif

