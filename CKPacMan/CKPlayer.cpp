#include "CKPlayer.h"
#include "CellInfo.h"
#include <iostream>
#include "CKMap.h"

CKPlayer::CKPlayer(InputHandler* inputHandler, CKMap* map, float moveSpeed) : CKCharacter(map->GetActorPos(EActorType::Player).x * CellInfo::CELL_SIZE, map->GetActorPos(EActorType::Player).y * CellInfo::CELL_SIZE),
m_animSpeed(0.1f), m_animTimer(0.0f), DEATH_FRAMES(12), NORMAL_FRAMES(6), m_animOver(false), m_direction(sf::Vector2f(0, 0)), m_map(map), m_moveSpeed(moveSpeed)
{
	InitializeSprites();
	m_inputHandler = inputHandler;

	m_inputHandler->onMoveRight.subscribe([this]() {
		
		if (!m_map->IsWall(m_position + sf::Vector2f(CellInfo::CELL_SIZE, 0)))
			m_direction = sf::Vector2f(CellInfo::CELL_SIZE, 0);
	});

	m_inputHandler->onMoveLeft.subscribe([this]() {
		if (!m_map->IsWall(m_position + sf::Vector2f(-CellInfo::CELL_SIZE, 0)))
			m_direction = sf::Vector2f(-CellInfo::CELL_SIZE, 0);
	});

	m_inputHandler->onMoveUp.subscribe([this]() {
		if (!m_map->IsWall(m_position + sf::Vector2f(0, -CellInfo::CELL_SIZE)))
			m_direction = sf::Vector2f(0, -CellInfo::CELL_SIZE);
	});

	m_inputHandler->onMoveDown.subscribe([this]() {
		if (!m_map->IsWall(m_position + sf::Vector2f(0, CellInfo::CELL_SIZE)))
			m_direction = sf::Vector2f(0, CellInfo::CELL_SIZE);
	});
}

void CKPlayer::InitializeSprites()
{
	if (!m_textureNormal.loadFromFile("Resource/Images/Pacman" + std::to_string(CellInfo::CELL_SIZE) + ".png")) {
		std::cerr << "Error loading Pacman texture." << std::endl;
	}
	if (!m_textureDeath.loadFromFile("Resource/Images/PacmanDeath" + std::to_string(CellInfo::CELL_SIZE) + ".png")) {
		std::cerr << "Error loading PacmanDeath texture." << std::endl;
	}
	m_sprite.setTexture(m_textureNormal);  // 초기 스프라이트 텍스처 설정
	Reset();
}

void CKPlayer::Update(float deltaTime)
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
}

void CKPlayer::Draw(sf::RenderWindow& window)
{
	unsigned char frame = static_cast<unsigned char>(floor(m_animTimer / static_cast<float>(m_animSpeed)));
	int yPos = 0;
	if (m_direction == sf::Vector2f(CellInfo::CELL_SIZE, 0)) // Right
	{
		yPos = 0;
	}
	else if (m_direction == sf::Vector2f(0, -CellInfo::CELL_SIZE)) // Up
	{
		yPos = 1;
	}
	else if (m_direction == sf::Vector2f(-CellInfo::CELL_SIZE, 0)) // Left
	{
		yPos = 2;
	}
	else if (m_direction == sf::Vector2f(0, CellInfo::CELL_SIZE)) // Down
	{
		yPos = 3;
	}
	else if (m_isDead || m_isWin)
	{
		yPos = 0;
	}

	m_sprite.setTextureRect(sf::IntRect(CellInfo::CELL_SIZE * frame, CellInfo::CELL_SIZE * yPos, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));

	window.draw(m_sprite);
	
}

void CKPlayer::Dead()
{
	m_isDead = true;
	m_animTimer = 0.0f;
	m_sprite.setTexture(m_textureDeath);
}

void CKPlayer::Win()
{
	m_isWin = true;
	m_animTimer = 0.0f;
	m_sprite.setTexture(m_textureDeath);
}

void CKPlayer::Reset()
{
	m_animOver = 0;
	m_isDead = false;

	m_direction = sf::Vector2f(0, 0);
	
	m_animTimer = 0;
	m_energizerTimer = 0;
	m_sprite.setTexture(m_textureNormal);
}
