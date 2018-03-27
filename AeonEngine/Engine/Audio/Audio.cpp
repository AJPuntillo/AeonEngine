#include "Audio.h"

using namespace AEON_ENGINE;

void SoundEffect::play(int loops /* =0 */, int volume)
{

	
	Mix_PlayChannel(-1, m_chunk, loops);  //play the sound effect

	Mix_VolumeChunk(m_chunk, volume);     //volume control   Max = 128

	/*if (Mix_PlayChannel(-1, m_chunk, loops) == -1)
	{
		
		//fatalError("Mix_PlayChannel error: " + std::string(Mix_GetError()));
	}*/


	

	
	

	
}

void Music::play(int loops /* =1 */, int volume)
{
	Mix_PlayMusic(m_music, loops); // Play the music
	
	Mix_VolumeMusic(volume);  //Volume control   Max = 128
	
	
}

void Music::pause()
{
	Mix_PauseMusic();
}
void Music::stop()
{
	Mix_HaltMusic();
}
void Music::resume()
{
	Mix_ResumeMusic();
}

Audio::Audio()
{
	//Empty
}


Audio::~Audio()
{
	destroy();
}

void Audio::init()
{
	// parameter can be a bitwise combination of MIX_INIT_FAC,
	// MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG
	if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == -1)
	{
		//fatalError("Mix_Init error: " + std::string(Mix_GetError()));
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
	{
		//fatalError("Mix_OpenAudio error: " + std::string(Mix_GetError()));
	}

	m_isInitialized = true;
}
void Audio::destroy()
{
	if (m_isInitialized)
	{
		m_isInitialized = false;
		Mix_Quit();
	}
}

SoundEffect Audio::loadSoundEffect(const std::string& filePath)
{
	// Try to find audio in the cache
	auto it = m_effectMap.find(filePath);

	SoundEffect effect;

	if (it == m_effectMap.end())
	{
		//failed to find it, must load
		Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());

		// Check for Errors
		if (chunk == nullptr)
		{
			//fatalError("Mix_LoadWAV error: " + std::string(Mix_GetError())); 
		}

		effect.m_chunk = chunk;

		m_effectMap[filePath] = chunk;
	}
	else
	{
		//Its already cached
		effect.m_chunk = it->second;
	}

	return effect;
}
Music Audio::loadMusic(const std::string& filePath)
{
	// Try to find audio in the cache
	auto it = m_musicMap.find(filePath);

	Music music;

	if (it == m_musicMap.end())
	{
		//failed to find it, must load
		Mix_Music* mixMusic = Mix_LoadMUS(filePath.c_str());

		// Check for Errors
		if (mixMusic == nullptr)
		{
			//fatalError("Mix_LoadMUS error: " + std::string(Mix_GetError())); 
		}

		music.m_music = mixMusic;

		m_musicMap[filePath] = mixMusic;
	}
	else
	{
		//Its already cached
		music.m_music = it->second;
	}

	return music;
}
