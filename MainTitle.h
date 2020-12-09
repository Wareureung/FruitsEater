#ifndef __MAINTITLE_H__
#define __MAINTITLE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "SaveData.h"
#include "GameSound.h"
#include "Item.h"

USING_NS_CC;

class MainTitle : public Scene
{
public:
	SaveData title_save;
	//menu Scene
	Scene* menu_scene;

	//Layer
	Layer* main_bglayer;
	Layer* main_touchlayer;

	GameSound title_sound;

	Item main_item;

	Sprite* maintitle_sp;
	Sprite* maintitle_titlesp;
	Sprite* touch_to_start;

	MoveBy* mainbg_moveby_left;
	MoveBy* mainbg_moveby_right;
	RepeatForever* mainbg_repfor;
	Sequence* mainbg_seq;

	Blink* touch_blink;
	RepeatForever* touch_repfor;
	FadeOut* maintitle_out;

	EventListenerTouchOneByOne* main_listener;

	bool start_check;
	bool sch_one;

public:
	static Scene* createScene();

	virtual bool init();

	void AddLayer();
	void OnLayer();
	void Layer_BG();
	void Layer_TOUCH();

	TransitionScene* ChangeScene(float time, Scene* scene);

	void TouchToStart();
	void MainTitleFadeOut(float f);

	void AboutTouchMain();
	bool OnTouchBeganMain(Touch* touch, Event* event);
	
	CREATE_FUNC(MainTitle);
};
#endif