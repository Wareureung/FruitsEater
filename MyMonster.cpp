#include "MyMonster.h"

void MyMonster::SetSpriteMonster(const std::string name, int spnum, float width, float height, float x, float y, float delay)
{
	monstersp = Sprite::create(name);
	monstertex = monstersp->getTexture();
	
	monsterani = Animation::create();
	monsterani->setDelayPerUnit(delay);

	for (int i = 0; i < spnum; i++)
	{
		monsterani->addSpriteFrameWithTexture(monstertex, Rect(i * width, 0, width, height));
	}

	monstersp = Sprite::createWithTexture(monstertex, Rect(0, 0, width, height));

	monster_pos_x = 16 * x;
	monster_pos_y = 16 * y;
	monstersp->setPosition(Vec2(monster_pos_x, monster_pos_y));

	monsteranimate = Animate::create(monsterani);
	monrepfor = RepeatForever::create(monsteranimate);
	monstersp->runAction(monrepfor);

	
}

void MyMonster::MoveMonster()
{
	if (monster_pos_x < -20)
	{
		monstersp->setFlippedX(true);
		monster_move_speed = monster_real_speed;
	}
	else if (monster_pos_x > 380)
	{
		monstersp->setFlippedX(false);
		monster_move_speed = -monster_real_speed;
	}

	monster_pos_x += monster_move_speed;
	monstersp->setPosition(Vec2(monster_pos_x, monster_pos_y));
}

void MyMonster::HitMonster(float x, float y)
{
	monstersp = Sprite::create("character/plant_hit.png");
	monstertex = monstersp->getTexture();

	monsterani = Animation::create();
	monsterani->setDelayPerUnit(0.08f);

	for (int i = 0; i < 5; i++)
	{
		monsterani->addSpriteFrameWithTexture(monstertex, Rect(i * 44, 0, 44, 42));
	}
	monstersp = Sprite::createWithTexture(monstertex, Rect(0, 0, 44, 42));

	monster_pos_x = x;
	monster_pos_y = y;
	monstersp->setPosition(Vec2(monster_pos_x, monster_pos_y));

	monsteranimate = Animate::create(monsterani);
	hitmonster = Repeat::create(monsteranimate, 1);
	monstersp->runAction(hitmonster);
}

void MyMonster::SetMonsterSpeed(float speed)
{
	monster_real_speed = speed;

	monster_move_speed = -monster_real_speed;
}
