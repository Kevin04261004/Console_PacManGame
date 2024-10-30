#pragma once
#include "CKCharacter.h"
#include "CellInfo.h"
#include "CKPathFinder.h"

class CKEnemy : public CKCharacter
{
public:
	CKEnemy(class CKMap* map, float moveSpeed, EActorType type);
	virtual ~CKEnemy();

	void InitializeSprites() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Dead() override;
	void Win();
	void Reset();
	bool FindPath(CKActor* target);

protected:
	CKMap* m_map;
	enum class EActorType m_enemyType;

	CKPathFinder* m_pathFinder;
	std::stack<point> m_path;

	sf::Texture m_texture;
	sf::Sprite m_eyeSprite;
	sf::Color m_baseColor;

	float m_animSpeed;
	float m_moveSpeed;
	float m_animTimer;
	float m_energizerTimer;
	float m_moveTimer;
	const int DEATH_FRAMES;
	const int NORMAL_FRAMES;
	bool m_animOver;

	sf::Vector2f m_direction;

	bool m_isWin;
	bool m_isHunted;
};

