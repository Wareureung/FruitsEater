#ifndef __GAMESHOP_H__
#define __GAMESHOP_H__

#include "cocos2d.h"
#include "MyCharacter.h"
#include "MenuScene.h"
#include "SaveData.h"
#include "GameSound.h"
#include "TouchEffect.h"


#define PIXELBLOCK(x) (16 * x)

USING_NS_CC;

enum
{
	NORMAL,
	FROG,
	PINK,
	VGUY,
	RADISH,
	RABBIT
};

class GameShop : public Scene
{
public:
	GameSound shop_sound;

	SaveData mydata;

	Scene* menu_scene;

	Layer* shop_bglayer;
	Layer* shop_objlayer;
	Layer* shop_menulayer;

	TouchEffect teffect;

	Sprite* shop_bg;
	Sprite* windows[6];
	Sprite* select_arrow;

	MenuItemImage* shop_go_back;
	MenuItemImage* character_select[6];
	Menu* shop_menu;	

	Mycharacter everyone[6];

	int choice_num;
	std::string choice_name;
	
	int divide_num;
	float ch_width;
	float ch_height;

public:
	static Scene* createScene();

	virtual bool init();

	void AddLayer();
	void OnLayer();

	void Layer_BG();
	void Layer_OBJ();
	void Layer_MENU();

	TransitionScene* GoMenuScene(float time, Scene* scene);

	void GoBackMenu(Ref* pSender);
	void CharacterSelect(Ref* pSender);
	CREATE_FUNC(GameShop);
};
#endif