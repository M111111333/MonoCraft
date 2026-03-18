#include "SoundManager.h"
#include "DxLib.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager::SoundManager()
{
	for (int i = 0; i < BGM_TYPE_SOUND_MAX; i++)
	{
		m_BgmHandle[i] = 0;

	}
	for (int i = 0; i < SE_TYPE_MAX; i++)
	{
		m_SeHandle[i] = 0;

	}
	m_Sound = nullptr;
}

SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::Load()
{
	/*m_BgmHandle[BGM_TYPE_TITLE]   = LoadSoundMem("Resource/Sound/Title_BGM.mp3");
	m_BgmHandle[BGM_TYPE_PLAY]    = LoadSoundMem("Resource/Sound/Stage1_BGM.mp3");
	m_BgmHandle[BGM_TYPE_CRAFT]   = LoadSoundMem("Resource/Sound/Craft_BGM.mp3");



	m_SeHandle[SE_TYPE_JUMP]     = LoadSoundMem("Resource/Sound/Jump.mp3");
	m_SeHandle[SE_TYPE_EXJUMP]   = LoadSoundMem("Resource/Sound/ExJump.mp3");
	m_SeHandle[SE_TYPE_ATTACK]   = LoadSoundMem("Resource/Sound/Attack.mp3");
	m_SeHandle[SE_TYPE_BREAK]    = LoadSoundMem("Resource/Sound/Break.mp3");
	m_SeHandle[SE_TYPE_GET]      = LoadSoundMem("Resource/Sound/Get.mp3");
	m_SeHandle[SE_TYPE_IS_CRAFTING_1]   = LoadSoundMem("Resource/Sound/IsCrafting1.mp3");
	m_SeHandle[SE_TYPE_IS_CRAFTING_2]   = LoadSoundMem("Resource/Sound/IsCrafting2.mp3");


	m_SeHandle[SE_TYPE_SLECT_MOVE] = LoadSoundMem("Resource/Sound/SelctMove.mp3");
	m_SeHandle[SE_TYPE_CRAFT]      = LoadSoundMem("Resource/Sound/Craft.mp3");
	m_SeHandle[SE_TYPE_SELCT]      = LoadSoundMem("Resource/Sound/Selct.mp3");*/




	ChangeVolumeSoundMem(255 * 50 / 100, m_BgmHandle[BGM_TYPE_TITLE]);
	ChangeVolumeSoundMem(255 * 50 / 100, m_BgmHandle[BGM_TYPE_PLAY]);
	ChangeVolumeSoundMem(255 * 50 / 100, m_BgmHandle[BGM_TYPE_CRAFT]);
	ChangeVolumeSoundMem(255 * 45 / 100, m_SeHandle[SE_TYPE_GET]);
	ChangeVolumeSoundMem(255 * 45 / 100, m_SeHandle[SE_TYPE_EXJUMP]);
}

void SoundManager::Fin()
{

}

void SoundManager::CreateSound()
{
	if (!m_Sound)
	{
		m_Sound = new SoundManager;
	}
}

void SoundManager::PlayGBM(BGMType type)
{
	PlaySoundMem(m_BgmHandle[type], DX_PLAYTYPE_LOOP, true);
}

void SoundManager::StopBGM(BGMType type)
{
	StopSoundMem(m_BgmHandle[type]);
}

void SoundManager::PlaySE(SEType type)
{
	PlaySoundMem(m_SeHandle[type], DX_PLAYTYPE_BACK, true);
}

void SoundManager::PlaySEWait(SEType type)
{
	PlaySoundMem(m_SeHandle[type], DX_PLAYTYPE_NORMAL, true);
}
