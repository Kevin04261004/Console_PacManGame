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
    Player = 'P',
    Enemy0 = '0',
    Enemy1 = '1',
    Enemy2 = '2',
    Enemy3 = '3',
    Cherry = '¢À',
};

class CellInfo
{
public:
    static const int CELL_SIZE = 16;
};

