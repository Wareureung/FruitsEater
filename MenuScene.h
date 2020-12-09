#ifndef __MENUSCENE_H__
#define __MENUSCENE_H__

#include "cocos2d.h"
#include "MyMonster.h"
#include "TouchEffect.h"
#include "StageSelectScene.h"
#include "GameShop.h"
#include "GameSound.h"

USING_NS_CC;

class MenuScene : public Scene
{
public:
	SaveData menu_sdata;
	GameSound menu_sound;
	//Stage Scene
	Scene* select_scene;

	//Layer
	Layer* menu_bglayer;
	Layer* menu_objlayer;
	Layer* menu_menulayer;

	//Monster
	MyMonster menu_rabbit;
	MyMonster menu_duck;
	MyMonster menu_bird;

	//sprite
	Sprite* menu_bg_sp;
	Sprite* touch_effect_sp;
	Texture2D* touch_effect_tex;

	//menu
	MenuItemImage* menu_goeat;
	MenuItemImage* menu_goshop;
	MenuItemImage* menu_goexit;

	Menu* all_menu;

public:
	static Scene* createScene();

	virtual bool init();

	void AddLayer();
	void OnLayer();
	void Layer_BG();
	void Layer_OBJ();
	void Layer_MENU();

	TransitionScene* ChangeScene(float time, Scene* scene);

	void SetSpriteMenu();
	void MenuGoEat(Ref* pSender);
	void MenuGoShop(Ref* pSender);
	void MenuGoExit(Ref* pSender);

	void SetMenuSchduelr();
	void MoveBGSprite(float f);

	CREATE_FUNC(MenuScene);
};
#endif