#include "Stage.h"

USING_NS_CC;

Scene* Stage::createScene()
{    
    return Stage::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Stage::init()
{
    if (!Scene::init())
    {
        return false;
    }

    stage_change = true;    

    AddLayer();
    SetGameSound();
    SetStartValue();
    SetStagePlatForm();
    SetItem(platform);
    SetSchedule();        
    OnLayer();

    return true;
}

//스케쥴
void Stage::SetSchedule()
{
    if (double_jump_unlock_state)
    {
        //캐릭터 이동, 바닥 충돌 확인
        this->schedule(schedule_selector(Stage::EveryFrame));
        //캐릭터 이동 소리
        this->schedule(schedule_selector(Stage::PlayerRunSoundPlay), 0.2f);
        //타이머
        this->schedule(schedule_selector(Stage::GameTimer), 1.0f);
        //스타트 3초후 타이머 생성용
        this->scheduleOnce(schedule_selector(Stage::StartGame), start_timer);
    }
}

//업데이트
void Stage::EveryFrame(float f)
{
    if (start_timer <= 0)
    {
        //캐릭터 이동
        me.MoveLeftRight();
        //바닥 충돌체크
        Ground();

        if (stage_change)
            CrushCheck();
        else
            NextStageGo();
    }
}

//게임 사운드
void Stage::SetGameSound()
{
    gmsound.StopMainBGSound();
    gmsound.StopAllSound();
    gmsound.PlayBGSound();
}

//캐릭터 이동 사운드
void Stage::PlayerRunSoundPlay(float f)
{
    if (me.isground || me.isplatform)
        gmsound.RunSound();
}

//레이어 설정
void Stage::AddLayer()
{
    stage_bglayer = Layer::create();
    this->addChild(stage_bglayer);

    stage_objlayer = Layer::create();
    this->addChild(stage_objlayer);

    stage_timerlayer = Layer::create();
    this->addChild(stage_timerlayer);

    stage_touchlayer = Layer::create();
    this->addChild(stage_touchlayer);
}

//레이어 그리기
void Stage::OnLayer()
{
    Layer_BG();
    Layer_OBJ();
    Layer_TIMER();
    Layer_TOUCH();
}

void Stage::Layer_BG()
{
    //배경
    stage00 = Sprite::create(mydata.GetStageName());
    stage00->setPosition(-4, 0);
    stage00->setAnchorPoint(Vec2(0, 0));
    stage_bglayer->addChild(stage00, 0);
}

void Stage::Layer_OBJ()
{
    //바닥
    stage00_ground = Sprite::create(mydata.GetStageGroundName());
    stage00_ground->setPosition(-4, 0);
    stage00_ground->setAnchorPoint(Vec2(0, 0));
    stage_objlayer->addChild(stage00_ground, 0);

    //캐릭터
    me.SetMyCharacter(mydata.GetMyCharacter(), mydata.GetDivide(), mydata.GetWidth(), mydata.GetHeight());
    stage_objlayer->addChild(me.mysp, 2);

    //플랫폼
    for (int i = 0; i < STAGEPLATFORMMAX; i++)
    {
        stage_objlayer->addChild(platform[i].platsp_middle, 1);
        stage_objlayer->addChild(platform2[i].platsp_middle, 1);
        stage_objlayer->addChild(platform3[i].platsp_middle, 1);
    }

    //사과
    for (int i = 0; i < APPLENUMBER; i++)
        stage_objlayer->addChild(apple[i].itemsp, 1);
}

void Stage::Layer_TIMER()
{
    //캐릭터 잠금해제
    stage_result = Sprite::create("map/stage_result_vertical.png");
    stage_result->setAnchorPoint(Vec2(0, 0));
    stage_result->setPosition(Vec2(-500, -500));
    stage_timerlayer->addChild(stage_result, 3);
}

void Stage::Layer_TOUCH()
{
    AboutTouch();
}


//터치
void Stage::AboutTouch()
{
    //싱글터치
    listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Stage::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

//터치
bool Stage::onTouchBegan(Touch* touch, Event* event)
{
    //터치하면 점프 (바닥, 플랫폼 충돌상태 / 스테이지 바뀌는중 확인)
    if (mydata.GetDoubleJumpUnLock())
    {
        if (stage_change && me.double_jump < 3)
        {
            me.double_jump++;
            me.Jump();
            gmsound.JumpSound();
        }
    }
    else
    {
        if ((me.isground || me.isplatform) && stage_change && me.double_jump < 3)
        {
            me.double_jump++;
            me.Jump();
            gmsound.JumpSound();
        }
    }
    return true;
}

//처음시작시 플랫폼 위치 설정
void Stage::SetStagePlatForm()
{
    stage_gap = 640;

    if (mydata.GetAllocateStageScene() == 0)
    {
        SetStage00();
    }
    if (mydata.GetAllocateStageScene() == 1)
    {

        SetStage01();
    }
    if (mydata.GetAllocateStageScene() == 2)
    {
        RandomStageMaker();
    }
    if (mydata.GetAllocateStageScene() == 3)
    {
        RandomStageMaker();
    }
    if (mydata.GetAllocateStageScene() == 4)
    {
        RandomStageMaker();
    }
    if (mydata.GetAllocateStageScene() == 5)
    {
        RandomStageMaker();
    }
}

//시작값 셋팅
void Stage::SetStartValue()
{
    //스테이지 확인
    stage_number = mydata.GetAllocateStageScene();

    double_jump_unlock_state = false;

    //더블 점프 잠금해제    
    if (mydata.GetAllocateStageScene() == 2 && !mydata.GetDoubleJumpUnLock())
    {
        //이미지 먼저 띄우고
        unlock_double_jump_sp = Sprite::create("map/unlock_double_jump_all.png");
        unlock_double_jump_sp->setAnchorPoint(Vec2(0, 0));
        unlock_double_jump_sp->setPosition(Vec2(0, 0));
        stage_objlayer->addChild(unlock_double_jump_sp, 4);
        //일정 시간후에 스케줄 시작
        this->scheduleOnce(schedule_selector(Stage::DoubleJumpUnLockShow), 5);

        mydata.SetDoubleJumpUnLock();
    }
    else
        double_jump_unlock_state = true;

    //시작 전 타이머
    start_timer = 4;
}

void Stage::DoubleJumpUnLockShow(float f)
{
    double_jump_unlock_state = true;
    stage_objlayer->removeChild(unlock_double_jump_sp);
    SetSchedule();
}

//시작 타이머
void Stage::StartGame(float f)
{
    //시작 전 타이머 마치고 타이머 출력
    stimer[0].SetTimer(182, 600, 0);
    stimer[1].SetTimer(168, 600, 1);
    stage_timerlayer->addChild(stimer[0].numbersp, 2);
    stage_timerlayer->addChild(stimer[1].numbersp, 2);
}

//타이머
void Stage::GameTimer(float f)
{
    if (start_timer > 0)
    {
        start_timer--;
        if (start_timer == 0)
            gmsound.BeforeStartSoundB();
        else
            gmsound.BeforeStartSoundA();
    }
    else if (start_timer <= 0)
    {
        if (stage_change && apple_number > 0)
        {
            if (stage_timer < 1)
            {
                //타이머 제거
                for (int i = 0; i < 3; i++)
                    stage_timerlayer->removeChild(stimer[i].numbersp, true);

                gmsound.StopAllSound();
                this->unscheduleAllSelectors();
                this->schedule(schedule_selector(Stage::NextScene), 2.0f);
            }
            else
            {
                gmsound.TimerSound();
                stage_timer--;
            }

            if (stage_timer < 10 && !ten_time_done)
            {
                ten_time_done = true;
                stimer[0].MoveTimer(-10, -10);
                stimer[1].MoveTimer(-10, -10);
                stimer[2].SetTimer(175, 600, 2);
                stage_timerlayer->addChild(stimer[2].numbersp, 2);
            }
        }
    }
}

//바닥 충돌체크
void Stage::Ground()
{
    //바닥과 충돌
    if (!me.jump_state && me.my_pos_y >= 32 && me.mysp->getBoundingBox().intersectsRect(stage00_ground->getBoundingBox()))
    {
        //stage_change = true;
        me.isground = true;
        me.SetMyPosition(me.my_pos_x, 32);
    }
    else
    {
        me.isground = false;
    }
}

//바닥, 플랫폼, 아이템 충돌
void Stage::CrushCheck()
{
    //아이템 다 먹었을때
    if (apple_number == 0)
    {
        stage_state++;
        platform_down_state = 0;
        stage_change = false;

        me.isground = false;
        me.isplatform = false;
        me.jump_state = false;

        //타이머 관련        
        ten_time_done = false;        

        stage_timerlayer->removeChild(stimer[0].numbersp, true);
        stage_timerlayer->removeChild(stimer[1].numbersp, true);
        stage_timerlayer->removeChild(stimer[2].numbersp, true);
        return;
    }

    //다음 스테이지 넘어갈때 크래쉬 방지(스테이지 변경후 캐릭터가 바닥에 닿아야 충돌체크 시작)
    if (stage_change)
    {
        //플랫폼 1번
        if (stage_state == 0)
        {
            //플랫폼 충돌
            for (int i = 0; i < STAGEPLATFORMMAX; i++)
            {
                if (!me.jump_state && me.my_pos_y >= platform[i].plat_pos_y && me.mysp->getBoundingBox().intersectsRect(platform[i].platsp_middle->getBoundingBox()))
                {                    
                    me.isplatform = true;
                    me.SetMyPosition(me.my_pos_x, platform[i].plat_pos_y + 16);

                    //탈출용
                    i = 18;
                }
                else
                    me.isplatform = false;
            }
        }
        //플랫폼 2번
        if (stage_state == 1)
        {
            for (int i = 0; i < STAGEPLATFORMMAX; i++)
            {
                if (!me.jump_state && me.my_pos_y >= platform2[i].plat_pos_y && me.mysp->getBoundingBox().intersectsRect(platform2[i].platsp_middle->getBoundingBox()))
                {
                    me.isplatform = true;
                    me.SetMyPosition(me.my_pos_x, platform2[i].plat_pos_y + 16);

                    //탈출용
                    i = 18;
                }
                else
                    me.isplatform = false;
            }
        }
        //플랫폼 2번
        if (stage_state == 2)
        {
            for (int i = 0; i < STAGEPLATFORMMAX; i++)
            {
                if (!me.jump_state && me.my_pos_y >= platform3[i].plat_pos_y&& me.mysp->getBoundingBox().intersectsRect(platform3[i].platsp_middle->getBoundingBox()))
                {
                    me.isplatform = true;
                    me.SetMyPosition(me.my_pos_x, platform3[i].plat_pos_y + 16);

                    //탈출용
                    i = 18;
                }
                else
                    me.isplatform = false;

            }
        }

        //아이템 충돌
        if (apple_number > 0)
        {
            for (int i = 0; i < APPLENUMBER; i++)
            {
                if (!apple[i].Check_Item_State() && me.mysp->getBoundingBox().intersectsRect(apple[i].itemsp->getBoundingBox()))
                {
                    //sound
                    gmsound.EatSound();
                    //vibrate
                    Device::vibrate(0.1f);
                    //아이템 이펙트
                    apple[i].EatAnimation(apple[i].CheckItemPosX(), apple[i].CheckItemPosY());
                    apple[i].item_effectsp->setScale(2);
                    stage_objlayer->addChild(apple[i].item_effectsp);
                    remove_item_number = i;
                    this->scheduleOnce(schedule_selector(Stage::ReMoveItemEffect), 0.08f);

                    apple_number--;
                    apple[i].Item_State_Change_True();
                }

                if (apple[i].Check_Item_State())
                {
                    apple[i].GetItemMove(-10, -10);
                }
            }
        }
    }
}

void Stage::ReMoveItemEffect(float f)
{
    stage_objlayer->removeChild(apple[remove_item_number].item_effectsp);
}

//다음 스테이지
void Stage::NextStageGo()
{
    switch (stage_state)
    {
    case 1:
        SetNextStage(platform, platform2);
        break;
    case 2:
        SetNextStage(platform2, platform3);
        break;
    case 3:
        gmsound.StopAllSound();
        this->unscheduleAllSelectors();        

        //클리어한 스테이지 입력해야함
        ShowUnlock(stage_number);
        this->scheduleOnce(schedule_selector(Stage::NextScene), stage_done_timer);
        break;
    }    
}

//다음 씬
void Stage::NextScene(float f)
{
    menu_scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(ChangeScene(1, menu_scene));
}

//씬 전환
TransitionScene* Stage::ChangeScene(float time, Scene* scene)
{
    return TransitionFade::create(time, scene);
}

//다음 스테이지 셋팅
void Stage::SetNextStage(PlatForm* fplat, PlatForm* splat)
{
    //플랫폼이 다 이동했을때 아이템 생성
    if(stage_gap <= 0)
    {
        SetItem(splat);
        PlatFormMove(fplat);

        stage_change = true;
        
        //타이머 관련
        stimer[0].SetTimer(182, 600, 0);
        stimer[1].SetTimer(168, 600, 1);

        stage_timerlayer->addChild(stimer[0].numbersp, 2);
        stage_timerlayer->addChild(stimer[1].numbersp, 2);

        go_down = false;
        return;
    }

    if (stage_state == 1)
    {
        go_down_platform_first = STAGEPLATFORMMAX;
        go_down_platform_second = STAGEPLATFORMMAX;
    }
    if (stage_state == 2)
    {
        go_down_platform_first = STAGEPLATFORMMAX;
        go_down_platform_second = STAGEPLATFORMMAX;
    }

    if(stage_gap == 640)
    {
        go_down = true;
    }
    if (go_down)
    {
        stage_gap -= 6;

        for (int i = 0; i < STAGEPLATFORMMAX; i++)
        {
            if (fplat[i].plat_pos_y > -10)
            {
                fplat[i].GoingDown(0, 6);
            }
            if (fplat[i].plat_pos_y <= -10 && fplat[i].platform_state == false)
            {
                fplat[i].platform_state = true;
                fplat[i].GetPlatFormMove(-100, -100);
                stage_objlayer->removeChild(fplat[i].platsp_middle);
                platform_down_state++;                
            }
        }

        for (int i = 0; i < go_down_platform_second; i++)
            splat[i].GoingDown(0, 6);
    }
}

//다음 위치로 이동
void Stage::PlatFormMove(PlatForm* nextplat)
{
    stage_gap = 640;

    if (stage_state == 1)
    {
        for (int i = 0; i < STAGEPLATFORMMAX; i++)
            this->removeChild(nextplat[i].platsp_middle);
    }
    if (stage_state == 2)
    {
        for (int i = 0; i < STAGEPLATFORMMAX; i++)
            stage_objlayer->removeChild(nextplat[i].platsp_middle);
    }
}

//사과 랜덤 배치
void Stage::SetItem(PlatForm* nplat)
{
    //타이머 초기화
    stage_timer = 15;

    //사과 갯수 초기화
    apple_number = APPLENUMBER;    

    //값이 지정되지 않은 배열에 50값 삽입
    for(int i=0; i<5; i++)
        apple_pos_accum[i] = 50;

	for (int i = 0; i < APPLENUMBER; i++)
	{
		//랜덤 위치  
        random_platform = RandomHelper::random_int(0, STAGEPLATFORMMAX - 1);
        apple_pos_accum[i] = random_platform;

		////중복 위치 방지
        for (int j = 0; j < i; j++)
        {
            if (apple_pos_accum[j] == random_platform)
            {
                i--;
            }
        }        
	}

    //겹치지 않는 난수로 채워진 배열이 완성되면 아이템 셋팅
    if (apple_pos_accum[4] != 50)
    {
        for (int i = 0; i < 5; i++)
        {
            apple[i].Item_State_Change_False();

            if (stage_state == 0)
                apple[i].SetItem(nplat[apple_pos_accum[i]].plat_pos_x + PIXELBLOCK(2.5f), nplat[apple_pos_accum[i]].plat_pos_y + PIXELBLOCK(2), mydata.GetStageFruitName());
            else
                apple[i].GetItemMove(nplat[apple_pos_accum[i]].plat_pos_x + PIXELBLOCK(2.5f), nplat[apple_pos_accum[i]].plat_pos_y + PIXELBLOCK(2));
        }
    }
}

void Stage::ShowUnlock(int stage_num)
{
    //5번이면 Thanks for Player! 해야함
    if (stage_num != 5)
    {
        if (mydata.GetStageState(stage_num) == false)
        {
            mydata.SetStageState(stage_num);            

            switch (stage_num)
            {
            case 0:
                new_character_name = "character/frog_run.png";
                new_character_divide = 12;
                new_character_width = 32;
                new_character_height = 32;
                break;
            case 1:
                new_character_name = "character/pink_run.png";
                new_character_divide = 12;
                new_character_width = 32;
                new_character_height = 32;
                break;
            case 2:
                new_character_name = "character/vguy_run.png";
                new_character_divide = 12;
                new_character_width = 32;
                new_character_height = 32;
                break;
            case 3:
                new_character_name = "character/radish_run.png";
                new_character_divide = 12;
                new_character_width = 30;
                new_character_height = 38;
                break;
            case 4:
                new_character_name = "character/rabbit_run.png";
                new_character_divide = 12;
                new_character_width = 34;
                new_character_height = 44;
                break;
            }            
            gmsound.UnLockSound();
            stage_done_timer = 2;

            unlock_new.SetMyCharacter(new_character_name, new_character_divide, new_character_width, new_character_height);
            unlock_new.mysp->setPosition(Vec2(150, 302));
            unlock_new.mysp->setScale(2);
            stage_timerlayer->addChild(unlock_new.mysp, 4);                       

            stage_result->setPosition(Vec2(108, 286));
        }
    }
    if (stage_num == 5 && !mydata.GetThanksForPlaying())
    {
        gmsound.TFPSound();
        stage_done_timer = 5;
        mydata.SetThanksForPlaying();

        stage_done_thanks = Sprite::create("map/thanks_for_playing.png");
        stage_done_thanks->setAnchorPoint(Vec2(0, 0));
        stage_done_thanks->setPosition(Vec2(0, 0));
        stage_timerlayer->addChild(stage_done_thanks, 4);
    }
    else
        stage_done_timer = 2;
}

void Stage::SetStage00()
{
    //시작할때 플랫폼 설정
    if (stage_state == 0)
    {
        //stage 0-1
        //왼쪽 플랫폼
        for (int i = 0; i < 4; i++)
            platform[i].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(7) + (PIXELBLOCK(7) * i), mydata.GetStagePlatFormName());

        //오른쪽 플랫폼
        for (int i = 0; i < 4; i++)
            platform[i + 4].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(7) + (PIXELBLOCK(7) * i), mydata.GetStagePlatFormName());

        //가운데 플랫폼
        platform[8].SetPlatForm(PIXELBLOCK_X(9), 160, mydata.GetStagePlatFormName());
        platform[9].SetPlatForm(PIXELBLOCK_X(9), 160 + (PIXELBLOCK(7)), mydata.GetStagePlatFormName());

        //stage 0-2        
        platform2[0].SetPlatForm(PIXELBLOCK_X(2), (PIXELBLOCK(7) + (PIXELBLOCK(7) * 0)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[1].SetPlatForm(PIXELBLOCK_X(9), (160 + (PIXELBLOCK(7) * 0)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[2].SetPlatForm(PIXELBLOCK_X(16), (PIXELBLOCK(7) + (PIXELBLOCK(7) * 1)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[3].SetPlatForm(PIXELBLOCK_X(9), (160 + (PIXELBLOCK(7) * 1)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[4].SetPlatForm(PIXELBLOCK_X(2), (PIXELBLOCK(7) + (PIXELBLOCK(7) * 2)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[5].SetPlatForm(PIXELBLOCK_X(9), (60 + (PIXELBLOCK(7) + (PIXELBLOCK(7) * 2))) + stage_gap, mydata.GetStagePlatFormName());
        platform2[6].SetPlatForm(PIXELBLOCK_X(16), (PIXELBLOCK(7) + (PIXELBLOCK(7) * 3)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[7].SetPlatForm(PIXELBLOCK_X(9), (160 + (PIXELBLOCK(7) * 3)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[8].SetPlatForm(PIXELBLOCK_X(2), (PIXELBLOCK(7) + (PIXELBLOCK(7) * 4)) + stage_gap, mydata.GetStagePlatFormName());
        platform2[9].SetPlatForm(PIXELBLOCK_X(16), (PIXELBLOCK(7) + (PIXELBLOCK(7) * 4)) + stage_gap, mydata.GetStagePlatFormName());

        //stage 0-3
        //왼쪽 플랫폼
        for (int i = 0; i < 5; i++)
            platform3[i].SetPlatForm(PIXELBLOCK_X(2), (PIXELBLOCK(7) + (PIXELBLOCK(7) * i)) + stage_gap, mydata.GetStagePlatFormName());

        //오른쪽 플랫폼
        for (int i = 0; i < 5; i++)
            platform3[i + 5].SetPlatForm(PIXELBLOCK_X(16), (PIXELBLOCK(7) + (PIXELBLOCK(7) * i)) + stage_gap, mydata.GetStagePlatFormName());
    }
}

void Stage::SetStage01()
{
    //시작할때 플랫폼 설정
    if (stage_state == 0)
    {
        //stage 1-1
        platform[0].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(6), mydata.GetStagePlatFormName());
        platform[1].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(12), mydata.GetStagePlatFormName());
        platform[2].SetPlatForm(PIXELBLOCK_X(6), PIXELBLOCK(10), mydata.GetStagePlatFormName());
        platform[3].SetPlatForm(PIXELBLOCK_X(10), PIXELBLOCK(14), mydata.GetStagePlatFormName());
        platform[4].SetPlatForm(PIXELBLOCK_X(14), PIXELBLOCK(18), mydata.GetStagePlatFormName());
        platform[5].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(22), mydata.GetStagePlatFormName());
        platform[6].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(22), mydata.GetStagePlatFormName());
        platform[7].SetPlatForm(PIXELBLOCK_X(14), PIXELBLOCK(26), mydata.GetStagePlatFormName());
        platform[8].SetPlatForm(PIXELBLOCK_X(10), PIXELBLOCK(30), mydata.GetStagePlatFormName());
        platform[9].SetPlatForm(PIXELBLOCK_X(6), PIXELBLOCK(34), mydata.GetStagePlatFormName());


        //stage 1-2
        platform2[0].SetPlatForm(PIXELBLOCK_X(4), PIXELBLOCK(6) + stage_gap, mydata.GetStagePlatFormName());
        platform2[1].SetPlatForm(PIXELBLOCK_X(14), PIXELBLOCK(6) + stage_gap, mydata.GetStagePlatFormName());
        platform2[2].SetPlatForm(PIXELBLOCK_X(9), PIXELBLOCK(12) + stage_gap, mydata.GetStagePlatFormName());
        platform2[3].SetPlatForm(PIXELBLOCK_X(4), PIXELBLOCK(18) + stage_gap, mydata.GetStagePlatFormName());
        platform2[4].SetPlatForm(PIXELBLOCK_X(14), PIXELBLOCK(18) + stage_gap, mydata.GetStagePlatFormName());
        platform2[5].SetPlatForm(PIXELBLOCK_X(9), PIXELBLOCK(24) + stage_gap, mydata.GetStagePlatFormName());
        platform2[6].SetPlatForm(PIXELBLOCK_X(4), PIXELBLOCK(30) + stage_gap, mydata.GetStagePlatFormName());
        platform2[7].SetPlatForm(PIXELBLOCK_X(14), PIXELBLOCK(30) + stage_gap, mydata.GetStagePlatFormName());
        platform2[8].SetPlatForm(PIXELBLOCK_X(6), PIXELBLOCK(36) + stage_gap, mydata.GetStagePlatFormName());
        platform2[9].SetPlatForm(PIXELBLOCK_X(11), PIXELBLOCK(36) + stage_gap, mydata.GetStagePlatFormName());

        //stage 1-3        
        platform3[0].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(6) + stage_gap, mydata.GetStagePlatFormName());
        platform3[1].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(12) + stage_gap, mydata.GetStagePlatFormName());
        platform3[2].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(12) + stage_gap, mydata.GetStagePlatFormName());
        platform3[3].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(18) + stage_gap, mydata.GetStagePlatFormName());
        platform3[4].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(20) + stage_gap, mydata.GetStagePlatFormName());
        platform3[5].SetPlatForm(PIXELBLOCK_X(9), PIXELBLOCK(22) + stage_gap, mydata.GetStagePlatFormName());
        platform3[6].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(27) + stage_gap, mydata.GetStagePlatFormName());
        platform3[7].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(27) + stage_gap, mydata.GetStagePlatFormName());
        platform3[8].SetPlatForm(PIXELBLOCK_X(2), PIXELBLOCK(33) + stage_gap, mydata.GetStagePlatFormName());
        platform3[9].SetPlatForm(PIXELBLOCK_X(16), PIXELBLOCK(33) + stage_gap, mydata.GetStagePlatFormName());
    }
}


void Stage::RandomStageMaker()
{
    RePlace(STAGEPLATFORMMAX, random_x, random_y, platform, 1);

    RePlace(STAGEPLATFORMMAX, random_x, random_y, platform2, 2);

    RePlace(STAGEPLATFORMMAX, random_x, random_y, platform3, 3);
}

void Stage::RePlace(int num, int* platform_x, int* platform_y, PlatForm* plat_, int plat_number)
{
    int a_place_num = 0;
    int b_place_num = 0;
    int c_place_num = 0;
    int allock_turn = 0;

    int random_platform_x = 0;
    int random_platform_y = 0;

    for (int i = 0; i < 10; i++)
    {
        platform_x[i] = 0;
        platform_y[i] = 0;
    }

    //random    
    for (int i = 0; i < num;)
    {
        random_platform_x = RandomHelper::random_int(2, 14);

        if ((random_platform_x >= 2 && random_platform_x <= 5) && a_place_num < 4)
        {
            platform_x[i] = random_platform_x;
            a_place_num++;
            allock_turn++;
            i++;
        }
        else if ((random_platform_x >= 6 && random_platform_x <= 10) && b_place_num < 5)
        {
            platform_x[i] = random_platform_x;
            b_place_num++;
            allock_turn++;
            i++;
        }
        else if ((random_platform_x >= 11 && random_platform_x <= 14) && c_place_num < 4)
        {
            platform_x[i] = random_platform_x;
            c_place_num++;
            allock_turn++;
            i++;
        }
        else
            i = allock_turn;
    }

    a_place_num = 0;
    b_place_num = 0;
    c_place_num = 0;
    allock_turn = 0;

    for (int i = 0; i < num; )
    {
        random_platform_y = RandomHelper::random_int(3, 33);

        if ((random_platform_y >= 3 && random_platform_y <= 13) && a_place_num < 4)//11
        {
            platform_y[i] = random_platform_y;
            a_place_num++;
            allock_turn++;
            i++;
        }
        else if ((random_platform_y >= 14 && random_platform_y <= 23) && b_place_num < 5)//10
        {
            platform_y[i] = random_platform_y;
            b_place_num++;
            allock_turn++;
            i++;
        }
        else if ((random_platform_y >= 24 && random_platform_y <= 33) && c_place_num < 4)//10
        {
            platform_y[i] = random_platform_y;
            c_place_num++;
            allock_turn++;
            i++;
        }
        else
            i = allock_turn;
    }
    std::sort(platform_y, platform_y + 10);

    for (int i = 0; i < num; i++)
    {        
        for (int j = i + 1; j > i;)
        {
            if (j > 9)
                j = 0;
            else if ((platform_y[j] - platform_y[i] < 3) && platform_y[i] < 35)
            {
                platform_y[j]++;
                if (i > 0)
                    i--;
                j = 0;
            }
            else if ((platform_y[i] - platform_y[j] < -7) && platform_y[i] > 2)
            {
                platform_y[j]--;
                if (i > 0)
                    i--;
                j = 0;
            }
            else
                j = 0;
        }
        
    }
    std::sort(platform_y, platform_y + 10);

    
    for (int i = 0; i < num; i++)
    {
        if (plat_number == 1)
            plat_[i].SetPlatForm(PIXELBLOCK_X(platform_x[i]), PIXELBLOCK(platform_y[i]), mydata.GetStagePlatFormName());
        else
            plat_[i].SetPlatForm(PIXELBLOCK_X(platform_x[i]), PIXELBLOCK(platform_y[i] + stage_gap), mydata.GetStagePlatFormName());
    }
}