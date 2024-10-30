#pragma once
#include "CKMap.h"
#include <list>
#include <stack>
#include "SFML/Graphics.hpp"

struct point
{
	int x;
	int y;
};

class CKPathFinder
{
private:
	CKMap* m_map;
	std::list<point> m_visitNode;
	bool m_found;
	
	void extractMin(point& choicePos, int tx, int ty);

	int** m_mapData;
	bool** m_visitData;
	point** m_parent;

	int m_mapWidth;
	int m_mapHeight;
	bool m_bCanDiagonalMove;
public:
	CKPathFinder(CKMap* useMap);
	virtual ~CKPathFinder();

	void ResetData();

public:
	bool FindPath(int sx, int sy, int tx, int ty, std::stack<point>& outPath);

};

