#ifndef __TOUCHEFFECT_H__
#define __TOUCHEFFECT_H__

#include "cocos2d.h"

USING_NS_CC;

class TouchEffect
{
public:
	Sprite* touch_effect_sp;
	Texture2D* touch_effect_tex;

	Animation* touchani;
	Animate* touchanimate;
	Repeat* touchrep;

	float touch_pos_x;
	float touch_pos_y;

public:
	void SetTouchEffect(float x, float y);

	//test_test
};

#endif