#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CKSoundManager.h"
#include "CKMap.h"
#include "CKPlayer.h"
#include "CKEnemy.h"
#include "InputHandler.h"
#include <chrono>
#include <vector>
#include "GameManager.h"

int main()
{
    // 창 설정
    sf::RenderWindow window(sf::VideoMode(700, 700), "PacMan", sf::Style::Close);

    // Input Handler 설정
    InputHandler inputHandler;

    // 오디오 설정
    CKSoundManager soundManager;
    soundManager.SetBGMVolume(30.0f);
    soundManager.SetSFXVolume(30.0f);

    // 게임 메니저
    GameManager gameManager(&soundManager);

    // 맵 설정
    CKMap map(&soundManager, &gameManager);
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // 플레이어 설정
    float moveSpeed = 0.15f;
    CKPlayer player(&inputHandler, &map, moveSpeed, &gameManager);
    map.SetActor(EActorType::Player, &player);

    // 몬스터 설정
    CKEnemy enemy00(&map, moveSpeed, EActorType::Enemy0, &gameManager, &soundManager);
    map.SetActor(EActorType::Enemy0, &enemy00);
    CKEnemy enemy01(&map, moveSpeed, EActorType::Enemy1, &gameManager, &soundManager);
    map.SetActor(EActorType::Enemy1, &enemy01);
    CKEnemy enemy02(&map, moveSpeed, EActorType::Enemy2, &gameManager, &soundManager);
    map.SetActor(EActorType::Enemy2, &enemy02);
    CKEnemy enemy03(&map, moveSpeed, EActorType::Enemy3, &gameManager, &soundManager);
    map.SetActor(EActorType::Enemy3, &enemy03);
    CKActor inBox(map.GetActorPoint(EActorType::Enemy2).x * CellInfo::CELL_SIZE, map.GetActorPoint(EActorType::Enemy2).y * CellInfo::CELL_SIZE, &gameManager);
    map.SetActor(EActorType::Enemy2, &inBox);
    // 시간 설정
    auto previousTime = std::chrono::high_resolution_clock::now();

    // 게임 루프
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // 시간 설정
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        float deltaTime = elapsedTime.count();

        // 입력 처리
        inputHandler.HandleInput();

        // 게임 메니저
        gameManager.Update(deltaTime);

        // 플레이어 업데이트 (DeltaTime 사용)
        const auto actorMap = map.GetActorMap();
        for (auto actor : actorMap)
        {
            actor.second->Update(deltaTime);
        }

        // 화면 그리기
        window.clear();
        map.Draw(window);
        for (auto actor : actorMap)
        {
            actor.second->Draw(window);
        }
        window.display();
    }

    return 0;
}
