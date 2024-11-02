#include "CKEnemy.h"
#include "CKMap.h"
#include "CKPathFinder.h"

CKEnemy::CKEnemy(CKMap* map, float moveSpeed, EActorType type, GameManager* gm) : CKCharacter(map->GetActorPoint(type).x* CellInfo::CELL_SIZE, map->GetActorPoint(type).y* CellInfo::CELL_SIZE, gm),
m_animSpeed(0.1f), m_animTimer(0.0f), DEATH_FRAMES(1), NORMAL_FRAMES(6), m_animOver(false),
m_direction(sf::Vector2f(0, 0)), m_map(map), m_moveSpeed(moveSpeed)
{
	InitializeSprites();
	if (type != EActorType::Enemy0 && type != EActorType::Enemy1 && type != EActorType::Enemy2 && type != EActorType::Enemy3)
	{
		std::cerr << "Wrong Enemy Type!!" << std::endl;
		exit(1);
	}
	m_enemyType = type;

	m_pathFinder = new CKPathFinder(m_map);
	switch (m_enemyType)
	{
	case EActorType::Enemy0:
		m_stateManager = new StateManager(EEnemyState::Hunter, this, gm);
		break;
	case EActorType::Enemy1:
		m_stateManager = new StateManager(EEnemyState::Hunter, this, gm);
		break;
	case EActorType::Enemy2:
		m_stateManager = new StateManager(EEnemyState::Hunter, this, gm);
		break;
	case EActorType::Enemy3:
		m_stateManager = new StateManager(EEnemyState::Hunter, this, gm);
		break;
	default:
		exit(1);
		break;
	}
}

CKEnemy::~CKEnemy()
{
	delete m_pathFinder;
}

void CKEnemy::InitializeSprites()
{
	if (!m_texture.loadFromFile("Resource/Images/Ghost" + std::to_string(CellInfo::CELL_SIZE) + ".png"))
	{
		exit(1);
	}
	m_sprite.setTexture(m_texture);
	m_eyeSprite.setTexture(m_texture);
	Reset();
}

void CKEnemy::Update(float deltaTime)
{
	m_stateManager->UpdateState(deltaTime);

	m_animTimer += deltaTime;
	if (m_animTimer > (m_isDead ? DEATH_FRAMES : NORMAL_FRAMES) * m_animSpeed)
	{
		if (m_isDead)
		{
			m_animOver = true;
		}
		else
		{
			m_animTimer = 0.f;
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


	m_sprite.setColor(m_stateManager->GetCurrentStateType() == EEnemyState::Hunted ? sf::Color::Blue : baseColor);
	
	
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
	m_eyeSprite.setTextureRect(m_stateManager->GetCurrentStateType() == EEnemyState::Hunted ? hunted : hunter);
	
	window.draw(m_sprite);
	window.draw(m_eyeSprite);
}

void CKEnemy::Dead()
{
	m_isDead = true;
	m_animTimer = 0.0f;
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

bool CKEnemy::FindPath(EActorType targetType)
{
	point targetPos = point(m_map->GetActorPoint(targetType).x, m_map->GetActorPoint(targetType).y);

	return FindPath(targetPos);
}

bool CKEnemy::FindPath(point targetPoint)
{
	point startPoint(m_position.x / CellInfo::CELL_SIZE, m_position.y / CellInfo::CELL_SIZE);

	return m_pathFinder->FindPath(startPoint.x, startPoint.y, targetPoint.x, targetPoint.y, m_path);
}

void CKEnemy::FindRandomPointAndPath()
{
	point startPoint(m_position.x / CellInfo::CELL_SIZE, m_position.y / CellInfo::CELL_SIZE);

	m_pathFinder->FindRandomPath(startPoint.x, startPoint.y, m_path, GetEnemyType());
}

void CKEnemy::SetNextDirection()
{
	if (!TrySetSamePointInPath())
	{
		return;
	}

	m_direction = sf::Vector2f(0, 0);
	
	point nextPoint;
	if (HasPath())
	{
		m_path.pop();
		nextPoint = m_path.top();
		sf::Vector2f nextPos(nextPoint.x * CellInfo::CELL_SIZE, nextPoint.y * CellInfo::CELL_SIZE);
		m_direction = nextPos - m_position;
	}
}

void CKEnemy::SetReverseNextDirection()
{
	SetNextDirection();

	sf::Vector2f reverseDirection = -m_direction;
	sf::Vector2f reversePos = m_position + reverseDirection;

	// 반대 방향이 벽인지 확인
	if (!m_map->IsWall(reversePos))
	{
		m_direction = reverseDirection;
	}
	else
	{
		// 반대쪽이 벽인 경우, 양 옆 중 벽이 아닌 쪽을 선택
		sf::Vector2f leftDirection, rightDirection;

		// 현재 방향에 따라 양 옆 방향 설정
		if (m_direction == sf::Vector2f(CellInfo::CELL_SIZE, 0) || m_direction == sf::Vector2f(-CellInfo::CELL_SIZE, 0)) // 좌우 이동 중일 때
		{
			leftDirection = sf::Vector2f(0, -CellInfo::CELL_SIZE);   // 위쪽
			rightDirection = sf::Vector2f(0, CellInfo::CELL_SIZE);   // 아래쪽
		}
		else // 상하 이동 중일 때
		{
			leftDirection = sf::Vector2f(-CellInfo::CELL_SIZE, 0);   // 왼쪽
			rightDirection = sf::Vector2f(CellInfo::CELL_SIZE, 0);   // 오른쪽
		}

		// 양 옆 방향 중 벽이 아닌 쪽을 m_direction으로 설정
		sf::Vector2f leftPos = m_position + leftDirection;
		sf::Vector2f rightPos = m_position + rightDirection;

		if (!m_map->IsWall(leftPos))
		{
			m_direction = leftDirection;
		}
		else if (!m_map->IsWall(rightPos))
		{
			m_direction = rightDirection;
		}
		else
		{
			// 모든 방향이 벽일 경우 정지
			m_direction = sf::Vector2f(0, 0);
		}
	}
}

bool CKEnemy::TrySetSamePointInPath()
{
	point currentPoint(m_position.x / CellInfo::CELL_SIZE, m_position.y / CellInfo::CELL_SIZE);
	while (!m_path.empty() && m_path.top() != currentPoint)
	{
		m_path.pop();
	}

	if (!m_path.empty())
	{
		// m_path.pop();
		return true;
	}
	else
	{
		return false;
	}
	return true;
}

void CKEnemy::Move()
{
	sf::Vector2f pos = m_position + m_direction;

	// 양 옆으로 이동이 가능하게.
	if (pos.x < 0) {
		pos.x = (m_map->getWidth() - 1) * CellInfo::CELL_SIZE;
	}
	else if (pos.x >= m_map->getWidth() * CellInfo::CELL_SIZE) {
		pos.x = 0;
	}
	if (!m_map->IsWall(pos))
	{
		m_map->ActorMove(m_enemyType, m_position, pos, false);
		m_position = pos;
	}
}

bool CKEnemy::HasPath()
{
	if (!TrySetSamePointInPath())
	{
		return false;
	}
	if (m_path.empty() || m_path.size() < 2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CKEnemy::IsPlayerInRange(int range)
{
	return m_pathFinder->FindTarget(range, m_position, EActorType::Player);
}

void CKEnemy::PlayerCollisionEnter()
{
	if (m_stateManager == nullptr)
	{
		std::cerr << "Error: m_stateManager is NULL in PlayerCollisionEnter!" << std::endl;
		return;
	}
	if (m_stateManager->GetCurrentStateType() == EEnemyState::Hunted)
	{
		m_stateManager->ChangeState(EEnemyState::Eaten);
	}
	else if (m_stateManager->GetCurrentStateType() == EEnemyState::Hunter)
	{
		m_gameManager->GameOver();
	}
}
