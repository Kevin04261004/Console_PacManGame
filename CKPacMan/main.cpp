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
    // 창 설정
    sf::RenderWindow window(sf::VideoMode(700, 700), "PacMan", sf::Style::Close);

    // Input Handler 설정
    InputHandler inputHandler;

    // 오디오 설정
    sf::SoundBuffer BGMBuffer;
    if (!BGMBuffer.loadFromFile("Resource/Sounds/pacman_ringtone.mp3"))
    {
        return -1;
    }

    CKSoundManager soundManager;
    soundManager.PlayBGM(BGMBuffer);
    soundManager.SetBGMVolume(30.0f);

    // 맵 설정
    CKMap map;
    if (!map.LoadMapFromFile("Resource/Maps/CKGameMap.txt"))
    {
        return -1;
    }

    // 플레이어 설정
    float PlayerSpeed = 0.02f;
    CKPlayer player(map.GetPlayerInitPosition().x, map.GetPlayerInitPosition().y, PlayerSpeed, &inputHandler);


    // 게임 루프
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 입력 처리
        inputHandler.HandleInput();

        // 플레이어 업데이트 (DeltaTime 사용)
        player.Update(0.02f);

        // 화면 그리기
        window.clear();
        map.Draw(window);
        player.Draw(window);
        window.display();
    }

    return 0;
}
