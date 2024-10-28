#include "CKCharacter.h"

CKCharacter::CKCharacter(float x, float y) : CKActor(x, y)
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
