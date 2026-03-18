#pragma once


enum BGMType
{
	BGM_TYPE_TITLE,
	BGM_TYPE_PLAY,
	BGM_TYPE_OVER,
	BGM_TYPE_CRAFT,
	BGM_TYPE_SOUND_MAX
};

enum SEType
{
	SE_TYPE_JUMP,
	SE_TYPE_EXJUMP,
	SE_TYPE_ATTACK,
	SE_TYPE_BREAK,
	SE_TYPE_GET,

	SE_TYPE_SLECT_MOVE,
	SE_TYPE_SELCT,
	SE_TYPE_CRAFT,
	SE_TYPE_IS_CRAFTING_1,
	SE_TYPE_IS_CRAFTING_2,
	SE_TYPE_MAX,
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new SoundManager; }
	static SoundManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance)delete m_Instance; m_Instance = nullptr; }

public:
	void Load();
	void Fin();

	void CreateSound();

	void PlayGBM(BGMType type);

	void StopBGM(BGMType type);

	void PlaySE(SEType type);

	void PlaySEWait(SEType type);

private:
	static SoundManager* m_Instance;

	SoundManager* m_Sound;

	int m_BgmHandle[BGM_TYPE_SOUND_MAX];

	int m_SeHandle[SE_TYPE_MAX];
};
