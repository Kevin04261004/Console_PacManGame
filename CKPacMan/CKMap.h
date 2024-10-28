#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellInfo.h"
#include <map>

class CKMap
{
public:
    CKMap();

    // �� ���� �б�
    bool LoadMapFromFile(const std::string& filename);

    // �� ������ �׸���
    void Draw(sf::RenderWindow& window);
    inline sf::Vector2f GetActorPos(EActorType type) { return m_actorPos[type]; }

    bool IsWall(int x, int y) const;
    bool IsWall(sf::Vector2f pos) const;
    void ActorMove(EActorType actorType, int beforeX, int beforeY, int x, int y, bool getPellet, bool useGate);
    void ActorMove(EActorType actorType, sf::Vector2f before, sf::Vector2f pos, bool getPellet, bool useGate);
    inline int getWidth() { return m_width; }
    inline int getHeight() { return m_height; }
private:
    int m_width;
    int m_height;

    std::vector<std::vector<ECellType>> m_mapData;

    // �ؽ�ó�� ��������Ʈ
    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;

    void InitializeSprites();

private:
    std::map<EActorType, sf::Vector2f> m_actorPos;
};

