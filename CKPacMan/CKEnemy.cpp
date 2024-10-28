#include "CKEnemy.h"
#include "CKMap.h"


CKEnemy::CKEnemy(CKMap* map, float moveSpeed, EActorType type) : CKCharacter(map->GetActorPos(type).x* CellInfo::CELL_SIZE, map->GetActorPos(type).y* CellInfo::CELL_SIZE),
m_animSpeed(0.1f), m_animTimer(0.0f), DEATH_FRAMES(1), NORMAL_FRAMES(6), m_animOver(false),
m_direction(sf::Vector2f(0, 0)), m_map(map), m_moveSpeed(moveSpeed), m_isHunted(false)
{
	InitializeSprites();
	if (type != EActorType::Enemy0 && type != EActorType::Enemy1 && type != EActorType::Enemy2 && type != EActorType::Enemy3)
	{
		std::cerr << "Wrong Enemy Type!!" << std::endl;
		exit(1);
	}
	m_enemyType = type;
}

void CKEnemy::InitializeSprites()
{
	if (!m_texture.loadFromFile("Resource/Images/Ghost" + std::to_string(CellInfo::CELL_SIZE) + ".png"))
	{

	}
	m_sprite.setTexture(m_texture);
	m_eyeSprite.setTexture(m_texture);
	Reset();
}

void CKEnemy::Update(float deltaTime)
{
	m_animTimer += deltaTime;
	if (m_animTimer > (m_isDead ? DEATH_FRAMES : NORMAL_FRAMES) * m_animSpeed)
	{
		if (m_isDead || m_isWin)
		{
			m_animOver = true;
		}
		else
		{
			m_animTimer = 0.f;
		}
	}

	m_moveTimer += deltaTime;
	if (m_moveTimer > m_moveSpeed)
	{
		sf::Vector2f pos = m_position + m_direction;
		if (pos.x < 0) {
			pos.x = (m_map->getWidth() - 1) * CellInfo::CELL_SIZE;
		}
		else if (pos.x >= m_map->getWidth() * CellInfo::CELL_SIZE) {
			pos.x = 0;
		}
		if (!m_map->IsWall(pos))
		{
			m_map->ActorMove(EActorType::Player, m_position, pos, true, false);
			m_position = pos;
			m_moveTimer = 0.0f;
		}
	}

	m_sprite.setPosition(m_position.x, m_position.y);
	m_eyeSprite.setPosition(m_position.x, m_position.y);
}

void CKEnemy::Draw(sf::RenderWindow& window)
{
	unsigned char frame = static_cast<unsigned char>(floor(m_animTimer / static_cast<float>(m_animSpeed)));
	
	int yPos = 0;
	m_sprite.setTextureRect(sf::IntRect(CellInfo::CELL_SIZE * frame, CellInfo::CELL_SIZE * yPos, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));

	sf::Color baseColor = sf::Color::White;

	switch (m_enemyType)
	{
	case EActorType::Enemy0:
		baseColor = sf::Color::Red;
		break;
	case EActorType::Enemy1:
		baseColor = sf::Color::Cyan;
		break;
	case EActorType::Enemy2:
		baseColor = sf::Color::Magenta;
		break;
	case EActorType::Enemy3:
		baseColor = sf::Color::Yellow;
		break;
	default:
		exit(1);
		break;
	}


	m_sprite.setColor(m_isHunted ? sf::Color::Blue : baseColor);
	
	
	int xPos = 0;
	if (m_direction == sf::Vector2f(CellInfo::CELL_SIZE, 0)) // Right
	{
		xPos = 0;
	}
	else if (m_direction == sf::Vector2f(0, -CellInfo::CELL_SIZE)) // Up
	{
		xPos = 1;
	}
	else if (m_direction == sf::Vector2f(-CellInfo::CELL_SIZE, 0)) // Left
	{
		xPos = 2;
	}
	else if (m_direction == sf::Vector2f(0, CellInfo::CELL_SIZE)) // Down
	{
		xPos = 3;
	}
	yPos = 1;
	auto hunter = sf::IntRect(CellInfo::CELL_SIZE * xPos, CellInfo::CELL_SIZE * yPos, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE);
	auto hunted = sf::IntRect(CellInfo::CELL_SIZE * 4, CellInfo::CELL_SIZE * yPos, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE);
	m_eyeSprite.setTextureRect(m_isHunted ? hunted : hunter);
	
	
	window.draw(m_sprite);
	window.draw(m_eyeSprite);
}

void CKEnemy::Dead()
{
	m_isDead = true;
	m_animTimer = 0.0f;
}

void CKEnemy::Win()
{
	m_isWin = true;
	m_animTimer = 0.0f;
	m_sprite.setTexture(m_texture);
}

void CKEnemy::Reset()
{
	m_animOver = 0;
	m_isDead = false;

	m_direction = sf::Vector2f(0, 0);

	m_animTimer = 0;
	m_energizerTimer = 0;
	m_sprite.setTexture(m_texture);
}
