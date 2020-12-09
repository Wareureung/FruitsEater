#ifndef __MYCHARACTER_H__
#define __MYCHARACTER_H__

#include "cocos2d.h"
#include "GameSound.h"

USING_NS_CC;

class Mycharacter
{
public:

	Sprite* mysp;
	Texture2D* mytex;
	Animation* myani;
	Animate* myanimate;

	Animation* double_jump_ani;
	Animate* double_jump_animate;

	RepeatForever* repfor;
	RotateBy* double_jump_rot;
	Spawn* double_jump_add;

	float my_pos_x;
	float my_pos_y;

	float move_speed;

	bool flip_state;

	bool isground;
	bool isplatform;

	float jump_hight;
	float jump_max;
	float jump_fall_speed;
	bool jump_state;
	bool jump_middle;

	int double_jump;


public:
	void SetMyCharacter(const std::string pname, float fnumber, float swidth, float sheight);
	void SetMyPosition(float x, float y);
	void MoveLeftRight();
	void Jump();
};
#endif