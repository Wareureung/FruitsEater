#ifndef __MYMONSTER_H__
#define __MYMONSTER_H__

#include "cocos2d.h"

USING_NS_CC;

class MyMonster
{
public:
	Sprite* monstersp;
	Texture2D* monstertex;
	Animation* monsterani;
	Animate* monsteranimate;

	RepeatForever* monrepfor;
	Repeat* hitmonster;

	float monster_pos_x;
	float monster_pos_y;

	float monster_move_speed;
	float monster_real_speed;

public:
	void SetSpriteMonster(const std::string name, int spnum, float width, float height, float x, float y, float delay);
	void MoveMonster();
	void HitMonster(float x, float y);
	void SetMonsterSpeed(float speed);
};

#endif