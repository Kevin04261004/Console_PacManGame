#include "CKMap.h"
#include <fstream>
#include "CKSoundManager.h"
#include "CKEnemy.h"

CKMap::CKMap(CKSoundManager* soundManager, GameManager* gm) : m_width(0), m_height(0)
{
    InitializeSprites();
    if (!m_pellet01SoundBuffer.loadFromFile("Resource/Sounds/eat_dot_0.wav"))
    {
        std::cerr << "Load Sound Fail" << std::endl;
        exit(1);
    }
    if (!m_pellet02SoundBuffer.loadFromFile("Resource/Sounds/eat_dot_1.wav"))
    {
        std::cerr << "Load Sound Fail" << std::endl;
        exit(1);
    }
    m_soundManager = soundManager;
    m_pelletTrigger = false;

    m_gameManager = gm;
}

bool CKMap::LoadMapFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open map file." << std::endl;
        return false;
    }

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
        m_width = std::max(m_width, static_cast<int>(line.length()));
    }
    m_height = static_cast<int>(lines.size());

    // 크기에 맞춰 벡터 초기화
    m_mapData.resize(m_height, std::vector<ECellType>(m_width, ECellType::None));

    // 맵 데이터 로드
    for (int y = 0; y < m_height; ++y)
    {
        int yLength = static_cast<int>(lines[y].length());
        for (int x = 0; x < yLength; ++x)
        {
            char tileChar = lines[y][x];
            switch (tileChar)
            {
            case '#': m_mapData[y][x] = ECellType::Wall; break;
            case '.': m_mapData[y][x] = ECellType::Pellet; break;
            case 'o': m_mapData[y][x] = ECellType::Energizer; break;
            case 'P':
                m_mapData[y][x] = ECellType::None;
                m_actorPointMap[EActorType::Player] = sf::Vector2f(x, y);
                break;
            case '0':
                m_mapData[y][x] = ECellType::None;
                m_actorPointMap[EActorType::Enemy0] = sf::Vector2f(x, y);
                break;
            case '1':
                m_mapData[y][x] = ECellType::None;
                m_actorPointMap[EActorType::Enemy1] = sf::Vector2f(x, y);
                break;
            case '2':
                m_mapData[y][x] = ECellType::None;
                m_actorPointMap[EActorType::Enemy2] = sf::Vector2f(x, y);
                m_actorPointMap[EActorType::InBox] = sf::Vector2f(x, y);
                break;
            case '3':
                m_mapData[y][x] = ECellType::None;
                m_actorPointMap[EActorType::Enemy3] = sf::Vector2f(x, y);
                break;
            case '=': m_mapData[y][x] = ECellType::Gate; break;
            default: m_mapData[y][x] = ECellType::None; break;
            }
        }
    }

    return true;
}

void CKMap::InitializeSprites()
{
    // 스프라이트 초기화
    m_mapTexture.loadFromFile("Resource/Images/Map" + std::to_string(CellInfo::CELL_SIZE) + ".png");
    m_mapSprite.setTexture(m_mapTexture);
}

void CKMap::Draw(sf::RenderWindow& window)
{
    // 콘솔 출력을 위한 문자열 벡터 초기화
    std::vector<std::string> consoleMap(m_height, std::string(m_width, ' '));

    for (unsigned char y = 0; y < m_height; y++)
    {
        for (unsigned char x = 0; x < m_width; x++)
        {
            m_mapSprite.setPosition(static_cast<float>(CellInfo::CELL_SIZE * x), static_cast<float>(CellInfo::CELL_SIZE * y));

            switch (m_mapData[y][x])
            {
            case ECellType::Gate:
                m_mapSprite.setTextureRect(sf::IntRect(2 * CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = '='; // 게이트
                break;

            case ECellType::Energizer:
                m_mapSprite.setTextureRect(sf::IntRect(CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = 'o'; // 에너지 파워업
                break;

            case ECellType::Pellet:
                m_mapSprite.setTextureRect(sf::IntRect(0, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = '.'; // 작은 점
                break;

            case ECellType::Wall:
            {
                bool down = (y < m_height - 1 && m_mapData[y + 1][x] == ECellType::Wall);
                bool up = (y > 0 && m_mapData[y - 1][x] == ECellType::Wall);
                bool left = (x > 0 && m_mapData[y][x - 1] == ECellType::Wall);
                bool right = (x < m_width - 1 && m_mapData[y][x + 1] == ECellType::Wall);

                m_mapSprite.setTextureRect(sf::IntRect(CellInfo::CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = '#'; // 벽
            }
            break;
            default:
                consoleMap[y][x] = ' '; // 빈 공간
                break;
            }
        }
    }

    for (const auto& actorPos : m_actorPointMap) {
        int x = actorPos.second.x;
        int y = actorPos.second.y;

        if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
            switch (actorPos.first) {
            case EActorType::Player:
                consoleMap[y][x] = 'P'; // 플레이어
                break;
            case EActorType::Enemy0:
                consoleMap[y][x] = '0'; // 적 0
                break;
            case EActorType::Enemy1:
                consoleMap[y][x] = '1'; // 적 1
                break;
            case EActorType::Enemy2:
                consoleMap[y][x] = '2'; // 적 2
                break;
            case EActorType::Enemy3:
                consoleMap[y][x] = '3'; // 적 3
                break;
            default:
                break;
            }
        }
    }

    // 콘솔 출력
    system("cls");
    for (const auto& line : consoleMap)
    {
        std::cout << line << std::endl;
    }
}

bool CKMap::IsWall(int x, int y) const {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return true;

    return m_mapData[y][x] == ECellType::Wall;
}

bool CKMap::IsWall(sf::Vector2f pos) const {
    int x = static_cast<int>(pos.x / CellInfo::CELL_SIZE);
    int y = static_cast<int>(pos.y / CellInfo::CELL_SIZE);

    return IsWall(x, y);
}

void CKMap::ActorMove(EActorType actorType, int beforeX, int beforeY, int x, int y, bool getPellet)
{
    if (getPellet) {
        if (m_mapData[y][x] == ECellType::Pellet) {
            m_pelletTrigger = !m_pelletTrigger;
            m_soundManager->PlaySFXOneShoot(m_pelletTrigger ? m_pellet01SoundBuffer : m_pellet02SoundBuffer);
            m_mapData[y][x] = ECellType::None;
        }
        else if (m_mapData[y][x] == ECellType::Energizer) {
            m_mapData[y][x] = ECellType::None;
            m_gameManager->SetPowerTime();
        }
    }
    m_actorPointMap[actorType].x = x;
    m_actorPointMap[actorType].y = y;

    CheckCollisionWithEnemies();
}

void CKMap::ActorMove(EActorType actorType, sf::Vector2f before, sf::Vector2f pos, bool getPellet)
{
    int b_x = static_cast<int>(before.x / CellInfo::CELL_SIZE);
    int b_y = static_cast<int>(before.y / CellInfo::CELL_SIZE);
    int x = static_cast<int>(pos.x / CellInfo::CELL_SIZE);
    int y = static_cast<int>(pos.y / CellInfo::CELL_SIZE);

    ActorMove(actorType, b_x, b_y, x, y, getPellet);
}

void CKMap::CheckCollisionWithEnemies()
{
    // 플레이어 위치 가져오기
    sf::Vector2f playerPoint = m_actorPointMap[EActorType::Player];

    // 각 적과 플레이어의 위치가 같은지 검사
    for (auto& actorData : m_actorPointMap)
    {
        if (actorData.first == EActorType::Player)
        {
            continue;
        }
        if (actorData.second == playerPoint)
        {
            CKEnemy* enemy = dynamic_cast<CKEnemy*>(m_actorMap[actorData.first]);
            enemy->PlayerCollisionEnter();
        }
    }
}
