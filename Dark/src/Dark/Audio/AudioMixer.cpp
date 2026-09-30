#include "dpch.h"
#include "AudioMixer.h"

#include <miniaudio.h>

namespace Dark
{

	/******************Audio Data**********************/

	AudioData::AudioData(const std::string& fileName, AudioFlag flag)
	{
		//init stuff
		ma_engine* engine{ AudioMixer::GetAudioMixer()->GetRawAudioEngine() };
		m_Audio = new ma_sound;
		ma_result res{ ma_sound_init_from_file(
			engine,
			fileName.c_str(),
			static_cast<ma_sound_flags>(flag),
			nullptr, nullptr,
			m_Audio
		) };

		DARK_CORE_ASSERT(res == MA_SUCCESS, "Audio Data Failed To Load, check if the filePath is Correct!");

		if (res != MA_SUCCESS)
		{
			DARK_CORE_ERROR("Audio Data Failed To Load, Filepath: {0}", fileName);
			delete m_Audio; m_Audio = nullptr;
		}
	}

	AudioData::~AudioData()
	{
		if (ma_sound_is_playing(m_Audio)) ma_sound_stop(m_Audio);
		ma_sound_uninit(m_Audio);
		if(m_Audio)	delete m_Audio;

	}

	bool AudioData::PlayAudio(float volumeLvl)
	{

		ma_sound_seek_to_pcm_frame(m_Audio, 0);
		ma_sound_set_volume(m_Audio, volumeLvl);
		ma_result res{ ma_sound_start(m_Audio) };

		return res == MA_SUCCESS;
	}

	bool AudioData::StopAudio()
	{

		ma_result res{ ma_sound_stop(m_Audio) };

		return res == MA_SUCCESS;
			
	}

	bool AudioData::LoopAudio()
	{

		ma_sound_set_looping(m_Audio, MA_TRUE);
		ma_result res{ ma_sound_start(m_Audio) };

		return res == MA_SUCCESS;

	}

	bool AudioData::SetVolume(float volumeLvl)
	{

		ma_sound_set_volume(m_Audio, volumeLvl);

		return true;
	}

	bool AudioData::StopLoopAudio()
	{

		ma_sound_set_looping(m_Audio, MA_FALSE);
		ma_result res{ ma_sound_stop(m_Audio) };

		return  res == MA_SUCCESS;
	}

	bool AudioData::isAudioLooping() const{
		return ma_sound_is_looping(m_Audio);
	}

	bool AudioData::isAudioPlaying() const {
		return ma_sound_is_playing(m_Audio);
	}

	Ref<AudioData> AudioData::Create(const std::string& fileName, AudioFlag flag)
	{
		return CreateRef<AudioData>(fileName, flag);
	}

	/******************Audio Mixer**********************/

	Ref<AudioMixer> AudioMixer::s_Instance{ nullptr };

	AudioMixer::AudioMixer()
	{

		//init stuff
		m_Engine = new ma_engine;
		ma_result res{ ma_engine_init(nullptr, m_Engine) };

		DARK_CORE_ASSERT(res == MA_SUCCESS, "Audio Engine Initialization Failed!");

		if (res != MA_SUCCESS)
		{
			DARK_CORE_ERROR("Audio Mixer and Audio Engine Initialization Failed!");
			delete m_Engine;
		}
		else {
			DARK_CORE_INFO("Audio Mixer and Audio Engine Initialization Successful!");
		}
	}

	AudioMixer::~AudioMixer()
	{
		//deinit stuff;
		if (m_Engine) {
			ma_engine_uninit(m_Engine);
			delete m_Engine;
		}

	}

	Ref<AudioMixer> AudioMixer::Create()
	{
		s_Instance = CreateRef<AudioMixer>();
		return s_Instance;
	}

}