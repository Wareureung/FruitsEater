#include "StageSelectScene.h"

Scene* StageSelectScene::createScene()
{
	return StageSelectScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool StageSelectScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	SetSpriteSelect();	

	return true;
}

void StageSelectScene::SetSpriteSelect()
{
	gamestart_state = false;

	stage_select_sp = Sprite::create("map/stage_select.png");
	stage_select_sp->setAnchorPoint(Vec2(0, 0));
	stage_select_sp->setPosition(Vec2(0, 0));
	this->addChild(stage_select_sp, 0);

	loading_sp = Sprite::create("map/loading2.png");
	loading_sp->setAnchorPoint(Vec2(0, 0));
	loading_sp->setPosition(Vec2(-1000, -1000));
	this->addChild(loading_sp, 5);

	//select fruit
	stage_select_fruit[0].SetItem(PIXELBLOCK(3), 540, "item/item_apple.png");
	stage_select_fruit[1].SetItem(PIXELBLOCK(17), 540, "item/item_banana.png");
	stage_select_fruit[2].SetItem(PIXELBLOCK(3), 346, "item/item_cherries.png");
	stage_select_fruit[3].SetItem(PIXELBLOCK(17), 346, "item/item_kiwi.png");
	stage_select_fruit[4].SetItem(PIXELBLOCK(3), 136, "item/item_pineapple.png");
	stage_select_fruit[5].SetItem(PIXELBLOCK(17), 136, "item/item_strawberry.png");

	for (int i = 0; i < 6; i++)
	{
		stage_select_fruit[i].itemsp->setAnchorPoint(Vec2(0, 0));
		stage_select_fruit[i].itemsp->setScale(1.5f);
		stage_select_fruit[i].GetItemMove(-200, -200);
		this->addChild(stage_select_fruit[i].itemsp, 3);
	}
	stage_select_fruit[0].GetItemMove(PIXELBLOCK(3), 540);

	for (int i = 0; i < 6; i++)
		test[i] = mydata.GetStageState(i);

	plant[0].SetSpriteMonster("character/plant_idle.png", 11, 44, 42, 4.5f, 30.2f, 0.08f);
	this->addChild(plant[0].monstersp);
	if (mydata.GetStageState(0))
		plant[1].SetSpriteMonster("character/plant_idle.png", 11, 44, 42, 18.5f, 30.2f, 0.08f);
	if (mydata.GetStageState(1))
		plant[2].SetSpriteMonster("character/plant_idle.png", 11, 44, 42, 4.5f, 17.2f, 0.08f);
	if (mydata.GetStageState(2))
		plant[3].SetSpriteMonster("character/plant_idle.png", 11, 44, 42, 18.5f, 17.2f, 0.08f);
	if (mydata.GetStageState(3))
		plant[4].SetSpriteMonster("character/plant_idle.png", 11, 44, 42, 4.5f, 4.2f, 0.08f);
	if (mydata.GetStageState(4))
		plant[5].SetSpriteMonster("character/plant_idle.png", 11, 44, 42, 18.5f, 4.2f, 0.08f);

	for (int i = 1; i < 6; i++)
	{
		if (mydata.GetStageState(i - 1))
			this->addChild(plant[i].monstersp);
	}

	//첫진입 확인
	if (!mydata.GetStageSelectExplain())
	{
		ExplainStageSelect();
		this->scheduleOnce(schedule_selector(StageSelectScene::ExplainStageSelect), 4);
	}
	else
		DrawTouchPlace();
}

void StageSelectScene::ExplainStageSelect()
{
	//스테이지 선택 설명
	stage_select_hand_bg = Sprite::create("map/stage_select_hand_bg.png");
	stage_select_hand_bg->setAnchorPoint(Vec2(0, 0));
	stage_select_hand_bg->setPosition(Vec2(0, 0));
	this->addChild(stage_select_hand_bg, 3);

	stage_select_hand = Sprite::create("map/stage_select_hand.png");
	stage_select_hand->setAnchorPoint(Vec2(0, 0));
	stage_select_hand->setPosition(Vec2(PIXELBLOCK(7), 550));
	stage_select_hand->setFlippedX(true);
	this->addChild(stage_select_hand, 4);

	hand_move_back = MoveBy::create(0.5f, Vec2(-30, 0));
	hand_move_front = MoveBy::create(0.5f, Vec2(30, 0));
	hand_action_seq = Sequence::create(hand_move_back, hand_move_front, nullptr);
	hand_rep = Repeat::create(hand_action_seq, 5);
	stage_select_hand->runAction(hand_rep);
}

void StageSelectScene::DrawTouchPlace()
{
	//select menu
	for (int i = 0; i < 6; i++)
	{
		stage_go_sp[i] = MenuItemImage::create("map/go1.png", "map/go1.png", CC_CALLBACK_1(StageSelectScene::SelectStage, this));
		stage_go_sp[i]->setAnchorPoint(Vec2(0, 0));
		stage_go_sp[i]->setPosition(Vec2(-200, -200));
		stage_go_sp[i]->setTag(i);
	}

	stage_go_sp[0]->setPosition(Vec2(PIXELBLOCK(3), 540));
	if (mydata.GetStageState(0))
	{
		stage_go_sp[1]->setPosition(Vec2(PIXELBLOCK(17), 540));
		stage_select_fruit[1].GetItemMove(PIXELBLOCK(17), 540);
	}
	if (mydata.GetStageState(1))
	{
		stage_go_sp[2]->setPosition(Vec2(PIXELBLOCK(3), 346));
		stage_select_fruit[2].GetItemMove(PIXELBLOCK(3), 346);
	}
	if (mydata.GetStageState(2))
	{
		stage_go_sp[3]->setPosition(Vec2(PIXELBLOCK(17), 346));
		stage_select_fruit[3].GetItemMove(PIXELBLOCK(17), 346);
	}
	if (mydata.GetStageState(3))
	{
		stage_go_sp[4]->setPosition(Vec2(PIXELBLOCK(3), 136));
		stage_select_fruit[4].GetItemMove(PIXELBLOCK(3), 136);
	}
	if (mydata.GetStageState(4))
	{
		stage_go_sp[5]->setPosition(Vec2(PIXELBLOCK(17), 136));
		stage_select_fruit[5].GetItemMove(PIXELBLOCK(17), 136);
	}

	all_select_menu = Menu::create(stage_go_sp[0], stage_go_sp[1], stage_go_sp[2], stage_go_sp[3], stage_go_sp[4], stage_go_sp[5], nullptr);
	all_select_menu->setAnchorPoint(Vec2(0, 0));
	all_select_menu->setPosition(Vec2(0, 0));
	this->addChild(all_select_menu);

	//bakc to menu
	back_to_menu = MenuItemImage::create("map/shop_goback.png", "map/shop_goback.png", CC_CALLBACK_1(StageSelectScene::BackToMenu, this));
	back_to_menu->setAnchorPoint(Vec2(0, 0));
	back_to_menu->setPosition(Vec2(PIXELBLOCK(10.5f), PIXELBLOCK(1)));
	back_to_menu->setScale(1.5f);

	stage_select_menu = Menu::create(back_to_menu, nullptr);
	stage_select_menu->setAnchorPoint(Vec2(0, 0));
	stage_select_menu->setPosition(Vec2(0, 0));
	this->addChild(stage_select_menu);
}

void StageSelectScene::ExplainStageSelect(float f)
{
	//첫진입 확인후 상태변경
	mydata.SetStageSelectExplain();

	//배경, 손가락 제거
	this->removeChild(stage_select_hand_bg);
	this->removeChild(stage_select_hand);

	//터치 영역 그리기
	DrawTouchPlace();
}

void StageSelectScene::SelectStage(Ref* pSender)
{
	if (!gamestart_state)
	{
		gamestart_state = true;
		stage_select_sound.TouchSound();

		stage_allocator = reinterpret_cast<MenuItem*>(pSender)->getTag();

		switch (stage_allocator)
		{
		case 0:
			mydata.SetStageName("map/stage00.png", "map/stage00_ground.png", "map/stage00_platform_middle.png", "item/item_apple.png");
			mydata.AllocateStageScene(0);
			break;
		case 1:
			mydata.SetStageName("map/stage01.png", "map/stage01_ground.png", "map/stage01_platform_middle.png", "item/item_banana.png");
			mydata.AllocateStageScene(1);
			break;
		case 2:
			mydata.SetStageName("map/stage02.png", "map/stage02_ground.png", "map/stage02_platform_middle.png", "item/item_cherries.png");
			mydata.AllocateStageScene(2);
			break;
		case 3:
			mydata.SetStageName("map/stage03.png", "map/stage03_ground.png", "map/stage03_platform_middle.png", "item/item_kiwi.png");
			mydata.AllocateStageScene(3);
			break;
		case 4:
			mydata.SetStageName("map/stage04.png", "map/stage04_ground.png", "map/stage04_platform_middle.png", "item/item_pineapple.png");
			mydata.AllocateStageScene(4);
			break;
		case 5:
			mydata.SetStageName("map/stage05.png", "map/stage05_ground.png", "map/stage05_platform_middle.png", "item/item_strawberry.png");
			mydata.AllocateStageScene(5);
			break;
		}

		this->schedule(schedule_selector(StageSelectScene::SelectStageMotion));
		this->scheduleOnce(schedule_selector(StageSelectScene::NextStageGo), 1.5f);
	}
}

void StageSelectScene::SelectStageMotion(float f)
{	
	if (plant[stage_allocator].monstersp->getBoundingBox().intersectsRect(stage_select_fruit[stage_allocator].itemsp->getBoundingBox()))
	{
		//기존 plant 위치 저장 및 스프라이트 제거
		int tx = plant[stage_allocator].monster_pos_x;
		int ty = plant[stage_allocator].monster_pos_y;
		this->removeChild(plant[stage_allocator].monstersp);

		//Hit plant 설정 및 그리기
		plant[stage_allocator].HitMonster(tx, ty);
		this->addChild(plant[stage_allocator].monstersp, 2);

		//이펙트 그리기 및 제거
		boom_effect.SetTouchEffect(tx, ty);
		this->addChild(boom_effect.touch_effect_sp);
		this->scheduleOnce(schedule_selector(StageSelectScene::RemoveEffect), 0.3f);

		//사과 스프라이트 제거
		this->removeChild(stage_select_fruit[stage_allocator].itemsp);

		//스케줄 정지
		unschedule(schedule_selector(StageSelectScene::SelectStageMotion));
	}
	else
	{
		stage_select_fruit[stage_allocator].ItemFall(1.2f);
	}
}

void StageSelectScene::NextStageGo(float f)
{
	stage_state = Stage::createScene();
	Director::getInstance()->replaceScene(ChangeScene(1, stage_state));	//1
}

void StageSelectScene::RemoveEffect(float f)
{
	loading_sp->setPosition(Vec2(0, 0));
	this->removeChild(boom_effect.touch_effect_sp);
}

TransitionScene* StageSelectScene::ChangeScene(float time, Scene* scene)
{	
	return TransitionFade::create(time, scene);
}

void StageSelectScene::BackToMenu(Ref* pSender)
{
	stage_select_sound.ReturnSound();

	menu_scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(ChangeScene(0.5f, menu_scene));
}