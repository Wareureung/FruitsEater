#include "PlatForm.h"

void PlatForm::SetPlatForm(float x, float y, std::string platform_name)
{
	platsp_middle = Sprite::create(platform_name);
	plattex = platsp_middle->getTexture();

	plat_pos_x = x;
	plat_pos_y = y;

	platsp_middle->setAnchorPoint(Vec2(0, 0));
	platsp_middle->setPosition(plat_pos_x, plat_pos_y);
}

void PlatForm::SetPlatFormLong(float x, float y)
{
	platsp_long = Sprite::create("map/stage00_platform_long.png");
	plattex = platsp_middle->getTexture();

	plat_pos_x = x;
	plat_pos_y = y;

	platsp_long->setAnchorPoint(Vec2(0, 0));
	platsp_long->setPosition(plat_pos_x, plat_pos_y);
}

void PlatForm::GetPlatFormMove(float x, float y)
{
	plat_pos_x = x;
	plat_pos_y = y;
	platsp_middle->setPosition(Vec2(plat_pos_x, plat_pos_y));
}

void PlatForm::GoingDown(float x, float y)
{
	plat_pos_x -= x;
	plat_pos_y -= y;
	platsp_middle->setPosition(Vec2(plat_pos_x, plat_pos_y));
}