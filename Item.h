#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

class Item
{
private:
	float item_pos_x;
	float item_pos_y;

	bool item_state;

	float item_effect_pos_x;
	float item_effect_pos_y;

public:
	Sprite* itemsp;	
	Texture2D* itemtex;
	Animation* itemani;
	Animate* itemanimate;
	RepeatForever* irepfor;	

	Sprite* item_effectsp;
	Texture2D* item_effecttex;
	Animation* itemeffectani;
	Animate* itemeffectanimate;
	Repeat* ierep;	

	void SetItem(float x, float y, std::string fruit_name);
	void EatAnimation(float x, float y);	
	void GetItemMove(float x, float y);
	void ItemFall(float y);;
	void SetItemState(bool state);
	void Item_State_Change_True() { item_state = true; }
	void Item_State_Change_False() { item_state = false; }
	float CheckItemPosX() { return item_pos_x; }
	float CheckItemPosY() { return item_pos_y; }	
	float CheckItemEffectPosX() { return item_effect_pos_x; }
	float CheckItemEffectPosY() { return item_effect_pos_y; }
	bool Check_Item_State() { return item_state; }
};
#endif