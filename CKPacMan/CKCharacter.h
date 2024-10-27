#pragma once
#include "CKActor.h"

class CKCharacter : public CKActor
{
public:
	CKCharacter(float x, float y, float speed);
	virtual ~CKCharacter();
	virtual void Dead();
protected:
	virtual void Move(float deltaTime, sf::Vector2f moveDir);

	float m_speed;

	bool m_isDead;
};

