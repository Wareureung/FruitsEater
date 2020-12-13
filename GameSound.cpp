#include "GameSound.h"
#include "AudioEngine.h"

void GameSound::PlayBGSound()
{
	if (AudioEngine::getState(bg1) != AudioEngine::AudioState::PLAYING)
		bg1 = AudioEngine::play2d("sounds/stage_background.mp3", true, 0.15f);
}

void GameSound::JumpSound()
{
	sjump = AudioEngine::play2d("sounds/player_jump_sound.mp3", false, 0.15f);
}

void GameSound::RunSound()
{
	srun = AudioEngine::play2d("sounds/player_run_sound.mp3", false, 0.07f);
}

void GameSound::EatSound()
{
	seat = AudioEngine::play2d("sounds/player_eat_sound.mp3", false, 0.4f);
}

void GameSound::TimerSound()
{
	tsound = AudioEngine::play2d("sounds/timer_sound.mp3", false, 0.1f);
}

void GameSound::StopAllSound()
{
	AudioEngine::stopAll();
}

void GameSound::TouchSound()
{
	stouch = AudioEngine::play2d("sounds/touch_sound2.mp3", false, 1.0f);
}

void GameSound::ReturnSound()
{
	sreturn = AudioEngine::play2d("sounds/return_sound.mp3", false, 1.0f);
}

void GameSound::PlayMainBGSound()
{
	sound_save.SetMainTitleBG(true);
	main_bg = AudioEngine::play2d("sounds/main_background.mp3", true, 0.1f);
}

void GameSound::StopMainBGSound()
{
	sound_save.SetMainTitleBG(false);
	AudioEngine::stop(main_bg);	
}

void GameSound::UnLockSound()
{
	unlock_sound = AudioEngine::play2d("sounds/unlock_sound.mp3", false, 0.15f);
}

void GameSound::TFPSound()
{
	tfp_sound = AudioEngine::play2d("sounds/tfp_sound.mp3", false, 0.4f);
}

void GameSound::BeforeStartSoundA()
{
	before_start_a = AudioEngine::play2d("sounds/before_start_a.mp3", false, 0.1f);
}

void GameSound::BeforeStartSoundB()
{
	before_start_b = AudioEngine::play2d("sounds/before_start_b.mp3", false, 0.1f);
}
