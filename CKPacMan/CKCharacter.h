#pragma once
#include "CKActor.h"

class CKCharacter : public CKActor
{
public:
	CKCharacter(float x, float y);
	virtual ~CKCharacter();
	virtual void Dead();
protected:
	virtual void Move(float deltaTime, sf::Vector2f moveDir);

	bool m_isDead;
};

