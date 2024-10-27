#include "CKCharacter.h"

CKCharacter::CKCharacter(float x, float y, float speed) : CKActor(x, y), m_speed(speed)
{
	
}

CKCharacter::~CKCharacter()
{
}

void CKCharacter::Dead()
{
}

void CKCharacter::Move(float deltaTime, sf::Vector2f moveDir)
{
	m_sprite.move(moveDir * deltaTime);
}
