#ifndef __GAMESOUND_H__
#define __GAMESOUND_H__

#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;
using namespace experimental;

class GameSound
{
public:

	SaveData sound_save;
	//background
	int bg1;
	int main_bg;
	static bool main_bg_state;

	//character
	int sjump;
	int srun;
	int seat;

	//touch
	int stouch;
	int sreturn;

	//timer
	int tsound;

	//unlock
	int unlock_sound;

	//tfp
	int tfp_sound;

	float sound_volume;

public:
	void PlayBGSound();
	void PlayMainBGSound();
	void JumpSound();
	void RunSound();
	void EatSound();
	void TimerSound();
	void TouchSound();
	void ReturnSound();
	void UnLockSound();
	void TFPSound();

	void StopMainBGSound();
	void StopAllSound();
};
#endif