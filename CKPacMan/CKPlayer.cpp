#include "CKPlayer.h"
#include "CellInfo.h"
#include <iostream>

CKPlayer::CKPlayer(float x, float y, float speed, InputHandler* inputHandler) : CKCharacter(x, y, speed), m_animSpeed(4), m_animTimer(0.0f),
DEATH_FRAMES(12), NORMAL_FRAMES(6), m_animOver(false), m_direction(sf::Vector2f(0,0))
{
	InitializeSprites();
	m_inputHandler = inputHandler;

	m_inputHandler->onMoveRight.subscribe([this]() {
		m_direction = sf::Vector2f(1, 0);
		});

	m_inputHandler->onMoveLeft.subscribe([this]() {
		m_direction = sf::Vector2f(-1, 0);
		});

	m_inputHandler->onMoveUp.subscribe([this]() {
		m_direction = sf::Vector2f(0, -1);
		});

	m_inputHandler->onMoveDown.subscribe([this]() {
		m_direction = sf::Vector2f(0, 1);
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
	m_sprite.setOrigin(CellInfo::CELL_SIZE / 2, CellInfo::CELL_SIZE / 2);
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

	m_position += m_direction * m_speed;

	m_sprite.setPosition(m_position.x, m_position.y);
}

void CKPlayer::Draw(sf::RenderWindow& window)
{
	unsigned char frame = static_cast<unsigned char>(floor(m_animTimer / static_cast<float>(m_animSpeed)));
	int yPos = 0;
	if (m_direction == sf::Vector2f(1, 0)) // Right
	{
		yPos = 0;
	}
	else if (m_direction == sf::Vector2f(0, -1)) // Up
	{
		yPos = 1;
	}
	else if (m_direction == sf::Vector2f(-1, 0)) // Left
	{
		yPos = 2;
	}
	else if (m_direction == sf::Vector2f(0, 1)) // Down
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
