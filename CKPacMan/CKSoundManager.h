#pragma once

#include "SFML/Audio.hpp"
#include <memory>

class CKSoundManager
{
private:
	std::unique_ptr<sf::Sound> m_activatedBGM;
	std::set<std::shared_ptr<sf::Sound>> m_activatedSFX;

	float m_BGMVolume;
	float m_SFXVolume;
public:
	CKSoundManager();
	virtual ~CKSoundManager();

	void PlayBGM(const sf::SoundBuffer& InBGM);
	void PlaySFXOneShoot(const sf::SoundBuffer& InSFX);
	void SetBGMVolume(float volume);
	void SetSFXVolume(float volume);
};

