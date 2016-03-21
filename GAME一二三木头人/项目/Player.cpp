#include "Player.h"

Player::Player(const LoaderParams* pParams, Vector2D* V, int n, int t , int initial) : 
GameObject(pParams), m_n(n), m_t(t), m_init(initial)
{ 
	m_velocity.setX(V->getX()); 
	m_velocity.setY(V->getY()); 
}

void Player::update()
{
	m_position +=  m_velocity;
	m_currentFrame = int( (( m_init + (SDL_GetTicks() / m_t )) % m_n ) );
}