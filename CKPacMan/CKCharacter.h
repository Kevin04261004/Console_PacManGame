#pragma once
#include "CKActor.h"

class CKCharacter : public CKActor
{
public:
	CKCharacter(float x, float y);
	virtual ~CKCharacter();
	virtual void Dead();
protected:
	virtual void Draw(sf::RenderWindow& window) {}
	virtual void Update(float deltaTime) {}
	virtual void InitializeSprites() {}
	bool m_isDead;
};

