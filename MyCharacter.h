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

	RepeatForever* repfor;

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
	void ExplainJump(float ground_pos);
};
#endif