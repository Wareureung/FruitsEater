#include "item.h"

void Item::SetItem(float x, float y, std::string fruit_name)
{
	itemsp = Sprite::create(fruit_name);
	itemtex = itemsp->getTexture();

	itemani = Animation::create();
	itemani->setDelayPerUnit(0.03f);

	//�̹��� �߶� �����Ӹ��� ����
	for (int i = 0; i < 17; i++)
	{
		itemani->addSpriteFrameWithTexture(itemtex, Rect(i * 32, 0, 32, 32));
	}

	//ù �̹��� ����
	itemsp = Sprite::createWithTexture(itemtex, Rect(0, 0, 32, 32));

	//�ִϸ��̼�	
	itemanimate = Animate::create(itemani);	
	irepfor = RepeatForever::create(itemanimate);
	itemsp->runAction(irepfor);

	//��ġ ����
	item_pos_x = x;
	item_pos_y = y;
	itemsp->setPosition(Vec2(item_pos_x, item_pos_y));
}

void Item::GetItemMove(float x, float y)
{	
	item_pos_x = x;
	item_pos_y = y;
	itemsp->setPosition(Vec2(item_pos_x, item_pos_y));
}

void Item::ItemFall(float y)
{	
	item_pos_y -= y;
	itemsp->setPosition(Vec2(item_pos_x, item_pos_y));
}

void Item::EatAnimation(float x, float y)
{
	item_effectsp = Sprite::create("item/item_effect.png");
	item_effecttex = item_effectsp->getTexture();

	itemeffectani = Animation::create();
	itemeffectani->setDelayPerUnit(0.02f);

	//�̹��� �߶� �����Ӹ��� ����
	for (int i = 0; i < 6; i++)
	{
		itemeffectani->addSpriteFrameWithTexture(item_effecttex, Rect(i * 32, 0, 32, 32));
	}

	item_effectsp = Sprite::createWithTexture(item_effecttex, Rect(0, 0, 32, 32));

	itemeffectanimate = Animate::create(itemeffectani);
	ierep = Repeat::create(itemeffectanimate, 1);	
	item_effectsp->runAction(ierep);

	item_effect_pos_x = x;
	item_effect_pos_y = y;

	item_effectsp->setPosition(Vec2(item_effect_pos_x, item_effect_pos_y));

	
}
