#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellInfo.h"

class CKMap
{
public:
    CKMap();

    // �� ���� �б�
    bool LoadMapFromFile(const std::string& filename);

    // �� ������ �׸���
    void Draw(sf::RenderWindow& window);
    inline sf::Vector2f GetPlayerInitPosition() { return m_playerInitPos; }
private:
    int m_width;
    int m_height;

    std::vector<std::vector<ECellType>> m_mapData;

    // �ؽ�ó�� ��������Ʈ
    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;

    void InitializeSprites();

private:
    sf::Vector2f m_playerInitPos;
};

