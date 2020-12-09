#ifndef __STAGETIMER_H__
#define __STAGETIMER_H__

#include "cocos2d.h"

USING_NS_CC;

class StageTimer
{
private:
	float num_pos_x;
	float num_pos_y;

	int numfor;
	int numreal;

	bool timer_state;
public:
	Sprite* numbersp;
	Texture2D* numbertex;
	Animation* numberani;
	Animate* numberanimate;

	RepeatForever* numrepeat;
	ScaleTo* numscale;
	Sequence* numaction;

	void SetTimer(float x, float y, int order);
	void MoveTimer(float x, float y);
};
#endif