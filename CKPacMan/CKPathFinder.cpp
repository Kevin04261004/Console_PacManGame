#include "CKPathFinder.h"

CKPathFinder::CKPathFinder(CKMap* useMap) : m_map(useMap), m_found(false), m_bCanDiagonalMove(false)
{
    m_mapWidth = m_map->getWidth();
    m_mapHeight = m_map->getHeight();
    m_mapData = new int* [m_mapHeight];
    m_visitData = new bool* [m_mapHeight];
    m_parent = new point * [m_mapHeight];
    for (int i = 0; i < m_mapHeight; ++i)
    {
        m_mapData[i] = new int[m_mapWidth];
        m_visitData[i] = new bool[m_mapWidth];
        m_parent[i] = new point[m_mapWidth];
    }

    ResetData();
}

CKPathFinder::~CKPathFinder()
{
    for (int i = 0; i < m_mapHeight; ++i)
    {
        delete[] m_mapData[i];
        delete[] m_visitData[i];
        delete[] m_parent[i];
    }
    delete[] m_mapData;
    delete[] m_visitData;
    delete[] m_parent;
}

void CKPathFinder::ResetData()
{
    m_visitNode.clear();

    for (int y = 0; y < m_mapHeight; y++) {
        for (int x = 0; x < m_mapWidth; x++) {
            m_mapData[y][x] = INT16_MAX;
            m_visitData[y][x] = false;
            m_parent[y][x].x = 0;
            m_parent[y][x].y = 0;
        }
    }
}

void CKPathFinder::extractMin(point& choicePos, int tx, int ty)
{
    int min = INT16_MAX;
    int curX, curY;
    std::list<point>::reverse_iterator curPos;
    for (curPos = m_visitNode.rbegin(); curPos != m_visitNode.rend(); curPos++) {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                curX = curPos->x + dx;
                curY = curPos->y + dy;
                if (curX < 0 || curX > m_mapWidth - 1 || curY < 0 || curY > m_mapHeight - 1)
                    continue;

                int hx = abs(tx - curX) * 10;
                int hy = abs(ty - curY) * 10;
                int hdist = hx + hy;

                if (m_mapData[curY][curX] + hdist < min && m_visitData[curY][curX] == false && m_map->getMapData(curX, curY) != ECellType::Wall) {
                    min = m_mapData[curY][curX] + hdist;
                    choicePos = { curX, curY };
                }
            }
        }
    }
}

bool CKPathFinder::FindPath(int sx, int sy, int tx, int ty, std::stack<point>& outPath)
{
    ResetData();
    m_found = false;

    point choicePos = { sx, sy };
    m_mapData[sy][sx] = 0;
    m_parent[sy][sx] = choicePos;

    // Shortest Path algorithm
    for (int i = 0; i < m_mapWidth * m_mapHeight; i++) {
        m_visitData[choicePos.y][choicePos.x] = true;
        m_visitNode.push_back(choicePos);

        if (choicePos.x == tx && choicePos.y == ty) {
            m_found = true;
            break;
        }

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (!m_bCanDiagonalMove && (dx != 0 && dy != 0))
                {
                    continue;
                }

                int nx = choicePos.x + dx;
                int ny = choicePos.y + dy;
                int dist;
                if (nx < 0 || nx > m_mapWidth - 1 || ny < 0 || ny > m_mapHeight - 1)
                    continue;

                if (m_visitData[ny][nx] == false && m_map->getMapData(nx, ny) != ECellType::Wall) {
                    dist = (dx == 0 || dy == 0) ? 10 : 14;
                    // 엣지 완화
                    if (m_mapData[choicePos.y][choicePos.x] + dist < m_mapData[ny][nx]) {
                        int val = m_mapData[choicePos.y][choicePos.x] + dist;
                        m_mapData[ny][nx] = val;
                        m_parent[ny][nx] = choicePos;
                    }
                }
            }
        }
        extractMin(choicePos, tx, ty);
    }

    while (!outPath.empty())
    {
        outPath.pop();
    }

    if (m_found) {
        point p;
        p = { tx, ty };
        outPath.push(p);
        while (p.x != sx || p.y != sy) {
            p = m_parent[p.y][p.x];
            outPath.push(p);
        }
    }

    return m_found;
}

bool CKPathFinder::FindRandomPath(int sx, int sy, std::stack<point>& outPath, int additionalSeed)
{
    std::srand(std::time(nullptr) + additionalSeed);

    point target;
    while (true)
    {
        target.x = std::rand() % (m_mapWidth - 2) + 1;
        target.y = std::rand() % (m_mapHeight - 2) + 1;

        if (m_map->getMapData(target.x, target.y) != ECellType::Wall)
        {
            break;
        }
    }

    FindPath(sx, sy, target.x, target.y, outPath);
    
    return true;
}

bool CKPathFinder::FindTarget(int range, sf::Vector2f startPosition, EActorType targetType)
{
    sf::Vector2f targetPoint = m_map->GetActorPoint(targetType);
    sf::Vector2f targetPosition(targetPoint.x * CellInfo::CELL_SIZE, targetPoint.y * CellInfo::CELL_SIZE);

    // 타겟과 거리 계산
    float distanceToTarget = std::sqrt(
        std::pow(targetPosition.x - startPosition.x, 2) +
        std::pow(targetPosition.y - startPosition.y, 2)
    );

    return range >= distanceToTarget;
}
