#include "Enemy.h"

void Enemy::update()
{

	m_x = int ((SDL_GetTicks() / 10));
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

//void Enemy::draw(SDL_Renderer* pRenderer)
//{
//	GameObject::draw(pRenderer);
//}

//void Enemy::load(int x, int y, int width, int height, string
//	textureID)
//{
//	GameObject::load(x, y, width, height, textureID);
//}