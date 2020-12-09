#include "MenuScene.h"

Scene* MenuScene::createScene()
{
	return MenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	AddLayer();
	OnLayer();

	return true;
}

void MenuScene::AddLayer()
{
	menu_bglayer = Layer::create();
	this->addChild(menu_bglayer);

	menu_objlayer = Layer::create();
	this->addChild(menu_objlayer);

	menu_menulayer = Layer::create();
	this->addChild(menu_menulayer);
}

void MenuScene::OnLayer()
{
	if (!menu_sdata.GetMainTitleBG())
		menu_sound.PlayMainBGSound();

	Layer_BG();
	Layer_OBJ();
	Layer_MENU();
}

void MenuScene::Layer_BG()
{
	menu_bg_sp = Sprite::create("map/menu_bg_empty.png");
	menu_bg_sp->setAnchorPoint(Vec2(0, 0));
	menu_bg_sp->setPosition(Vec2(0, 0));
	menu_bglayer->addChild(menu_bg_sp, 0);
}

void MenuScene::Layer_OBJ()
{
	menu_rabbit.SetSpriteMonster("character/rabbit_run.png", 12, 34, 44, 20, 3.5f, 0.03f);
	menu_rabbit.SetMonsterSpeed(2);
	menu_objlayer->addChild(menu_rabbit.monstersp, 1);

	menu_duck.SetSpriteMonster("character/duck_idle.png", 10, 36, 36, 7, 12, 0.05f);
	menu_objlayer->addChild(menu_duck.monstersp, 1);

	menu_bird.SetSpriteMonster("character/bird_fly.png", 9, 32, 32, 12, 39, 0.05f);
	menu_bird.SetMonsterSpeed(1);
	menu_objlayer->addChild(menu_bird.monstersp, 1);

	SetMenuSchduelr();
}

void MenuScene::Layer_MENU()
{
	menu_goeat = MenuItemImage::create("map/goeat.png", "map/goeat.png", CC_CALLBACK_1(MenuScene::MenuGoEat, this));
	menu_goeat->setAnchorPoint(Vec2(0, 0));
	menu_goeat->setPosition(Vec2(80, 464));

	menu_goshop = MenuItemImage::create("map/goshop.png", "map/goshop.png", CC_CALLBACK_1(MenuScene::MenuGoShop, this));
	menu_goshop->setAnchorPoint(Vec2(0, 0));
	menu_goshop->setPosition(Vec2(80, 272));

	menu_goexit = MenuItemImage::create("map/goexit.png", "map/goexit.png", CC_CALLBACK_1(MenuScene::MenuGoExit, this));
	menu_goexit->setAnchorPoint(Vec2(0, 0));
	menu_goexit->setPosition(Vec2(80, 80));

	all_menu = Menu::create(menu_goeat, menu_goshop, menu_goexit, nullptr);
	all_menu->setAnchorPoint(Vec2(0, 0));
	all_menu->setPosition(Vec2(0, 0));

	menu_menulayer->addChild(all_menu);
}

void MenuScene::MenuGoEat(Ref* pSender)
{
	menu_sound.TouchSound();

	select_scene = StageSelectScene::createScene();
	Director::getInstance()->replaceScene(ChangeScene(0.5f, select_scene));
}

void MenuScene::MenuGoShop(Ref* pSender)
{
	menu_sound.TouchSound();

	select_scene = GameShop::createScene();
	Director::getInstance()->replaceScene(ChangeScene(0.5f, select_scene));
}

void MenuScene::MenuGoExit(Ref* pSender)
{
	menu_sound.TouchSound();
	menu_sound.StopMainBGSound();
	menu_sound.StopAllSound();

	Director::sharedDirector()->end();
}

TransitionScene* MenuScene::ChangeScene(float time, Scene* scene)
{
	return TransitionProgressRadialCCW::create(time, scene);
}

void MenuScene::SetMenuSchduelr()
{
	this->schedule(schedule_selector(MenuScene::MoveBGSprite));	
}

void MenuScene::MoveBGSprite(float f)
{	
	menu_rabbit.MoveMonster();
	menu_bird.MoveMonster();
}