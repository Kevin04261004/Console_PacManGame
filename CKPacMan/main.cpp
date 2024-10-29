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

int main()
{
    // 창 설정
    sf::RenderWindow window(sf::VideoMode(700, 700), "PacMan", sf::Style::Close);

    // Input Handler 설정
    InputHandler inputHandler;

    // 오디오 설정
    sf::SoundBuffer BGMBuffer;
    if (!BGMBuffer.loadFromFile("Resource/Sounds/siren0.wav"))
    {
        return -1;
    }

    CKSoundManager soundManager;
    soundManager.PlayBGM(BGMBuffer);
    soundManager.SetBGMVolume(30.0f);
    soundManager.SetSFXVolume(30.0f);

    // 맵 설정
    CKMap map(&soundManager);
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // Actor에 추가.
    std::vector<class CKActor*> actors;

    // 플레이어 설정
    float moveSpeed = 0.15f;
    CKPlayer player(&inputHandler, &map, moveSpeed);
    actors.push_back(&player);

    // 몬스터 설정
    CKEnemy enemy00(&map, moveSpeed, EActorType::Enemy0);
    actors.push_back(&enemy00);
    CKEnemy enemy01(&map, moveSpeed, EActorType::Enemy1);
    actors.push_back(&enemy01);
    CKEnemy enemy02(&map, moveSpeed, EActorType::Enemy2);
    actors.push_back(&enemy02);
    CKEnemy enemy03(&map, moveSpeed, EActorType::Enemy3);
    actors.push_back(&enemy03);


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

        // 플레이어 업데이트 (DeltaTime 사용)
        for (auto actor : actors)
        {
            actor->Update(deltaTime);
        }

        // 화면 그리기
        window.clear();
        map.Draw(window);
        for (auto actor : actors)
        {
            actor->Draw(window);
        }
        window.display();
    }

    return 0;
}
