#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <SDL/SDL_mixer.h>
#include <map>

//*****************************************************************************************************************************************//
//                                                                AUDIO                                                                    //
//*****************************************************************************************************************************************//
// This is the AUDIO class, this class handle music and sound effects.       
// This header file consist of 3 class namely SoundEffect, Music and Audio.
// The SoundEffect class play the sound effects of the game.
// The Music class play the music for the game and have basic functions like play(), pause(), stop() and resume().
// Both play() functions takes in 2 parameters, 1st parameter is number of loops to play, the 2nd parameter is volume control.
// The Audio class is the sound manager, here you can load in Sound effects using the loadSoundEffect(filePath) and music using loadMusic(filePath).
// audio needs SDL2_mixer.lib, inorder for this to work, you need to update SDL to the latest version SDL2-2.0.7.
// When using, do not forget to initialize the audio engine in the initialize function of the engine using m_audioEngine.init() or else no sound will be played.

namespace AEON_ENGINE {

	class SoundEffect
	{
	public:
		friend class Audio;


		/// Plays the effect file
		/// @param loops: if loops == -1, Loop forever, 
		/// otherwise play it loops + 1 times; 
		void play(int loops, int volume);

	private:
		Mix_Chunk* m_chunk = nullptr;
	};

	class Music
	{
	public:
		friend class Audio;

		
		/// Plays the music file
		/// @param loops: if loops == -1, Loop forever, otherwise play it loop times; 
		void play(int loops , int volume);  

		static void pause();
		static void stop();
		static void resume();

	private:
		Mix_Music* m_music = nullptr;
	};

	class Audio
	{
	public:
		Audio();
		~Audio();

		void init();
		void destroy();

		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string& filePath);

	private:

		std::map<std::string, Mix_Chunk*> m_effectMap;
		std::map<std::string, Mix_Music*> m_musicMap;

		bool m_isInitialized = false;
	};
}

#endif