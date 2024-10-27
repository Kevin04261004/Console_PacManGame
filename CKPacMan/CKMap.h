#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellInfo.h"

class CKMap
{
public:
    CKMap();

    // 맵 파일 읽기
    bool LoadMapFromFile(const std::string& filename);

    // 맵 데이터 그리기
    void Draw(sf::RenderWindow& window);
    inline sf::Vector2f GetPlayerInitPosition() { return m_playerInitPos; }
private:
    int m_width;
    int m_height;

    std::vector<std::vector<ECellType>> m_mapData;

    // 텍스처와 스프라이트
    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;

    void InitializeSprites();

private:
    sf::Vector2f m_playerInitPos;
};

