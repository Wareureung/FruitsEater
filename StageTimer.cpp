#include "StageTimer.h"

void StageTimer::SetTimer(float x, float y, int order)
{	
	numbersp = Sprite::create("numbers/text_white.png");
	numbertex = numbersp->getTexture();

	numberani = Animation::create();

	switch (order)
	{
	case 0:
		numberani->setDelayPerUnit(1.0f);
		numbersp = Sprite::createWithTexture(numbertex, Rect(0, 30, 8, 10));
		//이미지 잘라서 프레임마다 저장
		for (numfor = 0; numfor < 6; numfor++)
		{
			numreal = numfor;
			if (numfor <= 5)
			{
				//시작 숫자부터 -1
				if (numfor != 0)
					numreal = 5 - numfor;
				else
					numreal = 5;	//시작 숫자
			}
			numberani->addSpriteFrameWithTexture(numbertex, Rect(numreal * 8, 30, 8, 10));
		}

		numberanimate = Animate::create(numberani);
		numrepeat = RepeatForever::create(numberanimate);
		numbersp->runAction(numrepeat);
		break;
	case 1:
		numberani->setDelayPerUnit(10.0f);
		numbersp = Sprite::createWithTexture(numbertex, Rect(8, 30, 8, 10));
		break;	
	case 2:
		numberani->setDelayPerUnit(1.0f);
		numbersp = Sprite::createWithTexture(numbertex, Rect(0, 30, 8, 10));
		//이미지 잘라서 프레임마다 저장
		for (numfor = 0; numfor < 10; numfor++)
		{
			numreal = numfor;
			//시작 숫자부터 -1
			if (numfor != 0)
				numreal = 9 - numfor;
			else
				numreal = 9;	//시작 숫자
			numberani->addSpriteFrameWithTexture(numbertex, Rect(numreal * 8, 30, 8, 10));
		}

		numberanimate = Animate::create(numberani);
		numrepeat = RepeatForever::create(numberanimate);
		numbersp->runAction(numrepeat);
		break;
	}

	num_pos_x = x;
	num_pos_y = y;
	numbersp->setScale(2);
	numbersp->setPosition(Vec2(num_pos_x, num_pos_y));
}

void StageTimer::MoveTimer(float x, float y)
{
	num_pos_x = x;
	num_pos_y = y;
	numbersp->setPosition(Vec2(num_pos_x, num_pos_y));
}