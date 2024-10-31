#pragma once

enum class ECellType : char
{
    None = 0,
    Wall = '#',
    Pellet = '.',
    Energizer = 'o',
    Gate = '=',
};

enum class EActorType : char
{
    None = 0,
    Player = 'P',
    Enemy0 = '0',
    Enemy1 = '1',
    Enemy2 = '2',
    Enemy3 = '3',
    Cherry = '9',
};

class CellInfo
{
public:
    static const int CELL_SIZE = 16;
};

