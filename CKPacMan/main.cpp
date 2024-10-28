#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CKSoundManager.h"
#include "CKMap.h"
#include "CKPlayer.h"
#include "InputHandler.h"
#include <chrono>

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
    soundManager.SetSFXVolume(300.0f);

    // �� ����
    CKMap map(&soundManager);
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // �÷��̾� ����
    float moveSpeed = 0.2f;
    CKPlayer player(&inputHandler, &map, moveSpeed);

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
        player.Update(deltaTime);

        // ȭ�� �׸���
        window.clear();
        map.Draw(window);
        player.Draw(window);
        window.display();
    }

    return 0;
}
