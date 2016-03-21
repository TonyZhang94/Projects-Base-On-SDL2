#ifndef __BBBBBBB__
#define __BBBBBBB__

class BackGround : public GameObject
{
public:
	BackGround(const LoaderParams* pParams) : GameObject(pParams) {}
	virtual void draw(){
		TextureManager::Instance()->draw(m_textureID, m_position.getX(), m_position.getY(),
		m_width, m_height, TheGame::Instance()->getRenderer());
	}//  ??
};

#endif


