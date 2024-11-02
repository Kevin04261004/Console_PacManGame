#include "CKActor.h"
CKActor::CKActor(float x, float y, GameManager* gm)
{
	m_position = sf::Vector2f(x, y);
	m_sprite.setPosition(m_position);
	m_gameManager = gm;
}

CKActor::~CKActor()
{
}

