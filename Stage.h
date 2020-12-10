#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"
#include "MenuScene.h"
#include "MyCharacter.h"
#include "PlatForm.h"
#include "Item.h"
#include "StageTimer.h"
#include "GameSound.h"
#include "SaveData.h"
//#include <algorithm>

#define STAGEPLATFORMMAX 10
#define APPLENUMBER 5
#define PIXELBLOCK(x) (16 * x)
#define PIXELBLOCK_X(x) ((16 * x) - 4)

class Stage : public Scene
{
public:
    SaveData mydata;

    Scene* menu_scene;    

    Layer* stage_bglayer;
    Layer* stage_objlayer;
    Layer* stage_timerlayer;
    Layer* stage_touchlayer;

    Sprite* stage00;
    Sprite* stage00_ground;
    Sprite* stage_result;
    Sprite* stage_done_thanks;

    Mycharacter me;
    Mycharacter unlock_new;

    PlatForm platform[STAGEPLATFORMMAX];
    PlatForm platform2[STAGEPLATFORMMAX];
    PlatForm platform3[STAGEPLATFORMMAX];

    Item apple[APPLENUMBER];
    StageTimer stimer[3];
    GameSound gmsound;

    //touch
    EventListenerTouchOneByOne* listener;

    //item
	int apple_pos_accum[APPLENUMBER];
	int apple_number = APPLENUMBER;
    int remove_item_number;

    //platform
    int random_platform;
    int platform_down_state;

    int go_down_platform_first;
    int go_down_platform_second;

    float stage_gap;
    bool go_down;

    //stage
    int stage_state;
    int stage_number;
    bool stage_change;

    int plat_number;

    int random_x[10];
    int random_y[10];

    int stage_done_timer;

    //new character
    std::string new_character_name;
    int new_character_divide;
    float new_character_width;
    float new_character_height;

    //timer
    int stage_timer;
    bool ten_time_done;
    bool ten_time_done2;
    int start_timer;

public:
    static Scene* createScene();

    virtual bool init();

    TransitionScene* ChangeScene(float time, Scene* scene);

    void AddLayer();
    void OnLayer();

    void SetGameSound();

    void Layer_BG();
    void Layer_OBJ();
    void Layer_TIMER();
    void Layer_TOUCH();

    void SetStartValue();    
    void SetSchedule();
    void SetStagePlatForm();
    void SetItem(PlatForm* nplat);

    void NextStageGo();
    void PlatFormMove(PlatForm* nextplat);
    
    void SetNextStage(PlatForm* fplat, PlatForm* splat);
    
    void ShowUnlock(int stage_num);

    void NextScene(float f);
    void PlayerRunSoundPlay(float f);
    void EveryFrame(float f);
    void GameTimer(float f);
    void StartGame(float f);
    void ReMoveItemEffect(float f);

    void SetStage00();
    void SetStage01();    

    void RandomStageMaker();
    void RePlace(int num, int* platform_x, int* platform_y, PlatForm* plat_, int plat_number);
    
    void Ground();
    void CrushCheck();
    
    void AboutTouch();
    bool onTouchBegan(Touch* touch, Event* event);

    CREATE_FUNC(Stage);
};

#endif