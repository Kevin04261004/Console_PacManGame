#pragma once
#include "CKMap.h"
#include <list>
#include <stack>
#include "SFML/Graphics.hpp"

struct point
{
	int x;
	int y;

	point() = default;

	point(int x, int y) : x(x), y(y)
	{
	}

	point& operator=(const point& other) {
		if (this != &other) {
			x = other.x;
			y = other.y;
		}
		return *this;
	}

	bool operator==(const point& other) const {
		return (x == other.x && y == other.y);
	}

	bool operator!=(const point& other) const {
		return (x != other.x && y != other.y);
	}

	point operator+(const point& other) const {
		return point(x + other.x, y + other.y);
	}

	// »¬¼À ¿¬»êÀÚ ¿À¹ö·Îµù
	point operator-(const point& other) const {
		return point(x - other.x, y - other.y);
	}
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
	bool FindRandomPath(int sx, int sy, int width, int height, std::stack<point>& outPath);
};

