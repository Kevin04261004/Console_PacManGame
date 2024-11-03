#pragma once
#include "CKCharacter.h"
#include "CellInfo.h"
#include "CKPathFinder.h"
#include "StateManager.h"

class CKEnemy : public CKCharacter
{
public:
	CKEnemy(class CKMap* map, float moveSpeed, EActorType type, GameManager* gm, class CKSoundManager* soundManager);
	virtual ~CKEnemy();

	void InitializeSprites() override;
	virtual void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Dead() override;
	void Win();
	void Reset();
	bool FindPath(EActorType targetType);
	bool FindPath(point targetPoint);
	void FindRandomPointAndPath();
	void SetNextDirection();
	void SetReverseNextDirection();
	bool TrySetSamePointInPath();
	void Move();
	bool HasPath();
	inline int GetEnemyType() { return (int)m_enemyType; }
	bool IsPlayerInRange(int range);
	void PlayerCollisionEnter();
	inline CKSoundManager* GetSoundManager() { return m_soundManager; }

protected:
	CKMap* m_map;
	CKSoundManager* m_soundManager;
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
	const int DEATH_FRAMES;
	const int NORMAL_FRAMES;
	bool m_animOver;

	sf::Vector2f m_direction;

	StateManager* m_stateManager;
};

