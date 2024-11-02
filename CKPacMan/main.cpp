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
    // â ����
    sf::RenderWindow window(sf::VideoMode(700, 700), "PacMan", sf::Style::Close);

    // Input Handler ����
    InputHandler inputHandler;

    // ����� ����
    CKSoundManager soundManager;
    soundManager.SetBGMVolume(30.0f);
    soundManager.SetSFXVolume(30.0f);

    // ���� �޴���
    GameManager gameManager(&soundManager);

    // �� ����
    CKMap map(&soundManager, &gameManager);
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // �÷��̾� ����
    float moveSpeed = 0.15f;
    CKPlayer player(&inputHandler, &map, moveSpeed, &gameManager);
    map.SetActor(EActorType::Player, &player);

    // ���� ����
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
    // �ð� ����
    auto previousTime = std::chrono::high_resolution_clock::now();

    // ���� ����
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // �ð� ����
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        float deltaTime = elapsedTime.count();

        // �Է� ó��
        inputHandler.HandleInput();

        // ���� �޴���
        gameManager.Update(deltaTime);

        // �÷��̾� ������Ʈ (DeltaTime ���)
        const auto actorMap = map.GetActorMap();
        for (auto actor : actorMap)
        {
            actor.second->Update(deltaTime);
        }

        // ȭ�� �׸���
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
