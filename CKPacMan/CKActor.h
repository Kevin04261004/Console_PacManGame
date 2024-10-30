#pragma once
#include "SFML/Graphics.hpp"

class CKActor
{
public:
	CKActor(float x, float y);
	virtual ~CKActor();

	inline sf::Vector2f GetPosition() const { return m_sprite.getPosition(); }

	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void InitializeSprites() = 0;

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};

