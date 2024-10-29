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
    // â ����
    sf::RenderWindow window(sf::VideoMode(700, 700), "PacMan", sf::Style::Close);

    // Input Handler ����
    InputHandler inputHandler;

    // ����� ����
    sf::SoundBuffer BGMBuffer;
    if (!BGMBuffer.loadFromFile("Resource/Sounds/siren0.wav"))
    {
        return -1;
    }

    CKSoundManager soundManager;
    soundManager.PlayBGM(BGMBuffer);
    soundManager.SetBGMVolume(30.0f);
    soundManager.SetSFXVolume(30.0f);

    // �� ����
    CKMap map(&soundManager);
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // Actor�� �߰�.
    std::vector<class CKActor*> actors;

    // �÷��̾� ����
    float moveSpeed = 0.15f;
    CKPlayer player(&inputHandler, &map, moveSpeed);
    actors.push_back(&player);

    // ���� ����
    CKEnemy enemy00(&map, moveSpeed, EActorType::Enemy0);
    actors.push_back(&enemy00);
    CKEnemy enemy01(&map, moveSpeed, EActorType::Enemy1);
    actors.push_back(&enemy01);
    CKEnemy enemy02(&map, moveSpeed, EActorType::Enemy2);
    actors.push_back(&enemy02);
    CKEnemy enemy03(&map, moveSpeed, EActorType::Enemy3);
    actors.push_back(&enemy03);


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

        // �÷��̾� ������Ʈ (DeltaTime ���)
        for (auto actor : actors)
        {
            actor->Update(deltaTime);
        }

        // ȭ�� �׸���
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
