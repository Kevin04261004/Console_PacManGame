#include "CKActor.h"

CKActor::CKActor(float x, float y)
{
	m_position = sf::Vector2f(x, y);
	m_sprite.setPosition(m_position);
}

CKActor::~CKActor()
{
}

