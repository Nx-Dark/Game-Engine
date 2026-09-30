#pragma once

struct ma_engine;
struct ma_sound;

namespace Dark
{

	enum AudioFlag
	{
		/* Resource manager flags. */
		FLAG_STREAM = 0x00000001,   /* MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_STREAM */
		FLAG_DECODE = 0x00000002,   /* MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_DECODE */
		FLAG_ASYNC = 0x00000004,   /* MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_ASYNC */
		FLAG_WAIT_INIT = 0x00000008,   /* MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_WAIT_INIT */
		FLAG_UNKNOWN_LENGTH = 0x00000010,   /* MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_UNKNOWN_LENGTH */
		FLAG_LOOPING = 0x00000020,   /* MA_RESOURCE_MANAGER_DATA_SOURCE_FLAG_LOOPING */

		/* ma_sound specific flags. */
		FLAG_NO_DEFAULT_ATTACHMENT = 0x00001000,   /* Do not attach to the endpoint by default. Useful for when setting up nodes in a complex graph system. */
		FLAG_NO_PITCH = 0x00002000,   /* Disable pitch shifting with ma_sound_set_pitch() and ma_sound_group_set_pitch(). This is an optimization. */
		FLAG_NO_SPATIALIZATION = 0x00004000    /* Disable spatialization. */
	};

	class DARK_API AudioData
	{

	private:

		ma_sound* m_Audio;

	public:
		AudioData(const std::string& fileName, AudioFlag flag = AudioFlag::FLAG_DECODE);
		~AudioData();

		bool PlayAudio(float volumeLvl = 0.5f);
		bool StopAudio();
		bool LoopAudio();
		bool StopLoopAudio();
		bool SetVolume(float volumeLvl);

		//getters
		bool isAudioPlaying() const;
		bool isAudioLooping() const;

		static Ref<AudioData> Create(const std::string& fileName, AudioFlag flag = AudioFlag::FLAG_DECODE);

	};

	class DARK_API AudioMixer
	{
	private:

		//static instance
		static Ref<AudioMixer> s_Instance;

		ma_engine* m_Engine;

	public:
		AudioMixer();
		~AudioMixer();

		inline ma_engine* GetRawAudioEngine() { return m_Engine; }

		static Ref<AudioMixer> Create();
		inline static Ref<AudioMixer> GetAudioMixer() { return s_Instance; }
	};

}