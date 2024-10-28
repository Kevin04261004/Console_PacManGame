#pragma once
#include "CKCharacter.h"
#include "InputHandler.h"

class CKPlayer : public CKCharacter
{
public:
	CKPlayer(InputHandler* inputHandler, class CKMap* map);
	void InitializeSprites() override;
	void Update(float deltaTime);
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Dead() override;
	void Win();
	void Reset();
protected:
	InputHandler* m_inputHandler;
	CKMap* m_map;

	sf::Texture m_textureNormal;
	sf::Texture m_textureDeath;

	float m_animSpeed;
	float m_animTimer;
	float m_energizerTimer;
	float m_moveTimer;
	const int DEATH_FRAMES;
	const int NORMAL_FRAMES;
	bool m_animOver;
	
	sf::Vector2f m_direction;

	bool m_isWin;
};

