#include "TouchEffect.h"

void TouchEffect::SetTouchEffect(float x, float y)
{
	touch_effect_sp = Sprite::create("particle/touch_effect.png");
	touch_effect_tex = touch_effect_sp->getTexture();

	touchani = Animation::create();
	touchani->setDelayPerUnit(0.02f);

	for (int i = 0; i < 7; i++)
	{
		touchani->addSpriteFrameWithTexture(touch_effect_tex, Rect(i * 96, 0, 96, 96));
	}

	touch_effect_sp = Sprite::createWithTexture(touch_effect_tex, Rect(0, 0, 96, 96));

	touch_effect_sp->setAnchorPoint(Vec2(0.5f, 0.5f));		
	touch_effect_sp->setPosition(Vec2(touch_pos_x, touch_pos_y));

	touchanimate = Animate::create(touchani);
	touchrep = Repeat::create(touchanimate, 1);
	touch_effect_sp->runAction(touchrep);

	touch_pos_x = x;
	touch_pos_y = y;
	touch_effect_sp->setPosition(touch_pos_x, touch_pos_y);
}