#include "CKSoundManager.h"

CKSoundManager::CKSoundManager() : m_BGMVolume(100.0f), m_SFXVolume(100.0f)
{

}

CKSoundManager::~CKSoundManager()
{
	if (m_activatedBGM != nullptr)
	{
		m_activatedBGM->stop();
	}
	for (auto& sound : m_activatedSFX)
	{
		sound->stop();
	}
}

void CKSoundManager::PlayBGM(const sf::SoundBuffer& InBGM, bool isLoop)
{
	if (m_activatedBGM != nullptr && m_activatedBGM->Playing)
	{
		m_activatedBGM->stop();
	}
	m_activatedBGM = std::make_unique<sf::Sound>();
	m_activatedBGM->setBuffer(InBGM);
	m_activatedBGM->setLoop(isLoop);
	m_activatedBGM->setVolume(m_BGMVolume);
	m_activatedBGM->play();
}

void CKSoundManager::PlaySFXOneShoot(const sf::SoundBuffer& InSFX)
{
	auto newSFX = std::make_shared<sf::Sound>();
	newSFX->setBuffer(InSFX);
	newSFX->setVolume(m_SFXVolume);
	newSFX->play();
	m_activatedSFX.insert(newSFX);

	std::weak_ptr<sf::Sound> weakSFX = newSFX;

	if (weakSFX.expired())
	{
		m_activatedSFX.erase(newSFX);
	}
}

void CKSoundManager::SetBGMVolume(float volume)
{
	m_BGMVolume = volume;
	if (m_activatedBGM != nullptr)
	{
		m_activatedBGM->setVolume(m_BGMVolume);
	}
}

void CKSoundManager::SetSFXVolume(float volume)
{
	m_SFXVolume = volume;
	for (auto& sound : m_activatedSFX)
	{
		sound->setVolume(m_SFXVolume);
	}
}