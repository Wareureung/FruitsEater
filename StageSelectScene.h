#ifndef __STAGESELECTSCENE_H__
#define __STAGESELECTSCENE_H__

#include "cocos2d.h"
#include "Stage.h"
#include "MyMonster.h"
#include "SaveData.h"
#include "GameSound.h"
#include "Item.h"
#include "TouchEffect.h"

USING_NS_CC;

class StageSelectScene : public Scene
{
public:
	GameSound stage_select_sound;

	SaveData mydata;
	std::vector<bool> myunlockdata;

	Scene* stage_state;

	bool test[6];

	bool gamestart_state;

	Sprite* stage_select_sp;
	Sprite* loading_sp;
	Sprite* stage_select_hand;
	Sprite* stage_select_hand_bg;

	MoveBy* hand_move_back;
	MoveBy* hand_move_front;
	Repeat* hand_rep;
	Sequence* hand_action_seq;

	TouchEffect boom_effect;

	Item stage_select_fruit[6];
	MenuItemImage* stage_go_sp[6];
	Menu* all_select_menu;

	int stage_allocator;

	MyMonster plant[6];

	//return
	Scene* menu_scene;

	MenuItemImage* back_to_menu;
	Menu* stage_select_menu;

public:
	static Scene* createScene();

	virtual bool init();

	TransitionScene* ChangeScene(float time, Scene* scene);

	void SetSpriteSelect();
	void DrawTouchPlace();
	void ExplainStageSelect();

	void SelectStageMotion(float f);
	void NextStageGo(float f);
	void RemoveEffect(float f);
	void ExplainStageSelect(float f);

	void SelectStage(Ref* pSender);
	void BackToMenu(Ref* pSender);	
	

	CREATE_FUNC(StageSelectScene);
};
#endif