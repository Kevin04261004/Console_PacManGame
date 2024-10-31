#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "CellInfo.h"
#include <map>
#include "SFML/Audio.hpp"

class CKMap
{
public:
    CKMap(class CKSoundManager* SoundManager);

    // 맵 파일 읽기
    bool LoadMapFromFile(const std::string& filename);

    // 맵 데이터 그리기
    void Draw(sf::RenderWindow& window);
    inline sf::Vector2f GetActorPoint(EActorType type) { return m_actorPoint[type]; }

    bool IsWall(int x, int y) const;
    bool IsWall(sf::Vector2f pos) const;
    void ActorMove(EActorType actorType, int beforeX, int beforeY, int x, int y, bool getPellet, bool useGate);
    void ActorMove(EActorType actorType, sf::Vector2f before, sf::Vector2f pos, bool getPellet, bool useGate);
    inline int getWidth() { return m_width; }
    inline int getHeight() { return m_height; }

    inline ECellType getMapData(int x, int y) { return m_mapData[y][x]; }
private:
    int m_width;
    int m_height;

    std::vector<std::vector<ECellType>> m_mapData;

    // 텍스처와 스프라이트
    sf::Texture m_mapTexture;
    sf::Sprite m_mapSprite;

    void InitializeSprites();

private:
    std::map<EActorType, sf::Vector2f> m_actorPoint;

/* Sound */
private:
    CKSoundManager* m_soundManager;
    sf::SoundBuffer m_pellet01SoundBuffer;
    sf::SoundBuffer m_pellet02SoundBuffer;
    bool m_pelletTrigger;
};

