#pragma once

enum class ECellType : char
{
    None = 0,
    Wall = '#',
    Pellet = '.',
    Energizer = 'o',
    Player = 'P',
    Enemy = '0',
    Enemy1 = '1',
    Enemy2 = '2',
    Enemy3 = '3',
    Gate = '=',
};

class CellInfo
{
public:
    static const int CELL_SIZE = 16;
};

