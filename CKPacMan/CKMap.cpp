#include "CKMap.h"
#include <fstream>

CKMap::CKMap() : m_width(0), m_height(0)
{
    InitializeSprites();
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

    // ũ�⿡ ���� ���� �ʱ�ȭ
    m_mapData.resize(m_height, std::vector<ECellType>(m_width, ECellType::None));

    // �� ������ �ε�
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
                m_mapData[y][x] = ECellType::Player;
                m_playerInitPos = sf::Vector2f(CellInfo::CELL_SIZE * x, CellInfo::CELL_SIZE * y);
                break;
            case '0': m_mapData[y][x] = ECellType::Enemy; break;
            case '1': m_mapData[y][x] = ECellType::Enemy1; break;
            case '2': m_mapData[y][x] = ECellType::Enemy2; break;
            case '3': m_mapData[y][x] = ECellType::Enemy3; break;
            case '=': m_mapData[y][x] = ECellType::Gate; break;
            default: m_mapData[y][x] = ECellType::None; break;
            }
        }
    }

    return true;
}

void CKMap::InitializeSprites()
{
    // ��������Ʈ �ʱ�ȭ
    m_mapTexture.loadFromFile("Resource/Images/Map" + std::to_string(CellInfo::CELL_SIZE) + ".png");
    m_mapSprite.setTexture(m_mapTexture);
}

void CKMap::Draw(sf::RenderWindow& window)
{
    // �ܼ� ����� ���� ���ڿ� ���� �ʱ�ȭ
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
                consoleMap[y][x] = '='; // ����Ʈ
                break;

            case ECellType::Energizer:
                m_mapSprite.setTextureRect(sf::IntRect(CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = 'o'; // ������ �Ŀ���
                break;

            case ECellType::Pellet:
                m_mapSprite.setTextureRect(sf::IntRect(0, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = '.'; // ���� ��
                break;

            case ECellType::Wall:
            {
                bool down = (y < m_height - 1 && m_mapData[y + 1][x] == ECellType::Wall);
                bool up = (y > 0 && m_mapData[y - 1][x] == ECellType::Wall);
                bool left = (x > 0 && m_mapData[y][x - 1] == ECellType::Wall);
                bool right = (x < m_width - 1 && m_mapData[y][x + 1] == ECellType::Wall);

                m_mapSprite.setTextureRect(sf::IntRect(CellInfo::CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CellInfo::CELL_SIZE, CellInfo::CELL_SIZE));
                window.draw(m_mapSprite);
                consoleMap[y][x] = '#'; // ��
            }
            break;

            case ECellType::Player:
                consoleMap[y][x] = 'P'; // �÷��̾�
                break;

            case ECellType::Enemy:
                consoleMap[y][x] = '0'; // �� �⺻ Ÿ��
                break;

            case ECellType::Enemy1:
                consoleMap[y][x] = '1'; // �� Ÿ�� 1
                break;

            case ECellType::Enemy2:
                consoleMap[y][x] = '2'; // �� Ÿ�� 2
                break;

            case ECellType::Enemy3:
                consoleMap[y][x] = '3'; // �� Ÿ�� 3
                break;

            default:
                consoleMap[y][x] = ' '; // �� ����
                break;
            }
        }
    }

    // �ܼ� ���
    //system("cls");
    //for (const auto& line : consoleMap)
    //{
    //    std::cout << line << std::endl;
    //}
}
