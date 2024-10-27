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
    if (!BGMBuffer.loadFromFile("Resource/Sounds/pacman_ringtone.mp3"))
    {
        return -1;
    }

    CKSoundManager soundManager;
    soundManager.PlayBGM(BGMBuffer);
    soundManager.SetBGMVolume(30.0f);

    // �� ����
    CKMap map;
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // �÷��̾� ����
    float PlayerSpeed = 0.02f;
    CKPlayer player(map.GetPlayerInitPosition().x, map.GetPlayerInitPosition().y, PlayerSpeed, &inputHandler);


    // ���� ����
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // �Է� ó��
        inputHandler.HandleInput();

        // �÷��̾� ������Ʈ (DeltaTime ���)
        player.Update(0.02f);

        // ȭ�� �׸���
        window.clear();
        map.Draw(window);
        player.Draw(window);
        window.display();
    }

    return 0;
}
