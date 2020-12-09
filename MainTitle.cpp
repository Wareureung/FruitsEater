#include "MainTitle.h"

Scene* MainTitle::createScene()
{
	return MainTitle::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainTitle::init()
{
	if (!Scene::init())
	{
		return false;
	}

	AddLayer();
	OnLayer();

	return true;
}

void MainTitle::AddLayer()
{
	main_bglayer = Layer::create();
	this->addChild(main_bglayer);

	main_touchlayer = Layer::create();
	this->addChild(main_touchlayer);
}

void MainTitle::OnLayer()
{
	title_save.SetMainTitleBG(true);	
	title_sound.PlayMainBGSound();

	Layer_BG();
	Layer_TOUCH();
}

void MainTitle::Layer_BG()
{
	maintitle_sp = Sprite::create("map/maintitle_bg_long.png");
	maintitle_sp->setAnchorPoint(Vec2(0, 0));
	maintitle_sp->setPosition(Vec2(-80, 0));
	main_bglayer->addChild(maintitle_sp, 0);

	mainbg_moveby_left = MoveBy::create(1, Vec2(-200, 0));
	mainbg_moveby_right = MoveBy::create(1, Vec2(200, 0));	
	mainbg_seq = Sequence::create(mainbg_moveby_left, mainbg_moveby_right, nullptr);
	mainbg_repfor = RepeatForever::create(mainbg_seq);
	maintitle_sp->runAction(mainbg_repfor);

	maintitle_titlesp = Sprite::create("map/maintitle_title.png");
	maintitle_titlesp->setAnchorPoint(Vec2(0, 0));
	maintitle_titlesp->setPosition(Vec2(0, 0));
	main_bglayer->addChild(maintitle_titlesp, 1);

	//title_sound.SetSound();
}

void MainTitle::Layer_TOUCH()
{
	main_item.SetItem(180, 260, "item/item_apple.png");
	main_item.itemsp->setScale(3);
	main_touchlayer->addChild(main_item.itemsp);

	touch_to_start = Sprite::create("map/touch_to_start.png");
	touch_to_start->setAnchorPoint(Vec2(0, 0));
	touch_to_start->setPosition(Vec2(PIXELBLOCK(4), PIXELBLOCK(13)));
	//main_touchlayer->addChild(touch_to_start, 1);

	touch_blink = Blink::create(1, 1);
	touch_repfor = RepeatForever::create(touch_blink);
	touch_to_start->runAction(touch_repfor);

	AboutTouchMain();
	TouchToStart();
}

void MainTitle::MainTitleFadeOut(float f)
{
	if (start_check && !sch_one)
	{
		sch_one = true;

		menu_scene = MenuScene::createScene();
		Director::getInstance()->replaceScene(ChangeScene(0.5f, menu_scene));
	}
}

void MainTitle::TouchToStart()
{
	this->schedule(schedule_selector(MainTitle::MainTitleFadeOut));
}

TransitionScene* MainTitle::ChangeScene(float time, Scene* scene)
{
	return TransitionProgressRadialCCW::create(time, scene);
}

void MainTitle::AboutTouchMain()
{
	//½Ì±ÛÅÍÄ¡
	main_listener = EventListenerTouchOneByOne::create();
	main_listener->setSwallowTouches(true);
	main_listener->onTouchBegan = CC_CALLBACK_2(MainTitle::OnTouchBeganMain, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(main_listener, this);

}

bool MainTitle::OnTouchBeganMain(Touch* touch, Event* event)
{	
	title_sound.EatSound();

	start_check = true;

	return true;
}