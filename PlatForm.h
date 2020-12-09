#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "cocos2d.h"

USING_NS_CC;

class PlatForm
{
public:
	Sprite* platsp_middle;
	Sprite* platsp_long;
	Texture2D* plattex;

	float plat_pos_x;
	float plat_pos_y;

	bool platform_state;

public:
	void SetPlatForm(float x, float y, std::string platform_name);
	void SetPlatFormLong(float x, float y);
	void GetPlatFormMove(float x, float y);
	void GoingDown(float x, float y);
};
#endif