#include "GameShop.h"

USING_NS_CC;

Scene* GameShop::createScene()
{
    return GameShop::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameShop::init()
{
    if (!Scene::init())
    {
        return false;
    }

    AddLayer();
    OnLayer();

    return true;
}

void GameShop::AddLayer()
{
    shop_bglayer = Layer::create();
    this->addChild(shop_bglayer,0);

    shop_objlayer = Layer::create();
    this->addChild(shop_objlayer,1);

    shop_menulayer = Layer::create();
    this->addChild(shop_menulayer,2);
}

void GameShop::OnLayer()
{
    Layer_BG();
    Layer_OBJ();
    Layer_MENU();
}

void GameShop::Layer_BG()
{
    shop_bg = Sprite::create("map/shop_bg.png");
    shop_bg->setAnchorPoint(Vec2(0, 0));
    shop_bg->setPosition(Vec2(-4, 0));
    shop_bglayer->addChild(shop_bg, 0);
}

void GameShop::Layer_OBJ()
{
    //character
    everyone[NORMAL].SetMyCharacter("character/a_idle.png", 11, 32, 32);
    everyone[NORMAL].SetMyPosition(PIXELBLOCK(4.2f), PIXELBLOCK(27.5f));
    everyone[NORMAL].mysp->setScale(1.5f);
    shop_objlayer->addChild(everyone[NORMAL].mysp, 2);

    everyone[FROG].SetMyCharacter("character/frog_idle.png", 11, 32, 32);
    everyone[FROG].SetMyPosition(PIXELBLOCK(15.2f), PIXELBLOCK(27.5f));
    everyone[FROG].mysp->setScale(1.5f);

    everyone[PINK].SetMyCharacter("character/pink_idle.png", 11, 32, 32);
    everyone[PINK].SetMyPosition(PIXELBLOCK(4.2f), PIXELBLOCK(15.5f));
    everyone[PINK].mysp->setScale(1.5f);

    everyone[VGUY].SetMyCharacter("character/vguy_idle.png", 11, 32, 32);
    everyone[VGUY].SetMyPosition(PIXELBLOCK(15.2f), PIXELBLOCK(15.5f));
    everyone[VGUY].mysp->setScale(1.5f);

    everyone[RADISH].SetMyCharacter("character/radish_idle.png", 9, 30, 38);
    everyone[RADISH].SetMyPosition(PIXELBLOCK(4.2f), PIXELBLOCK(3.4f));
    everyone[RADISH].mysp->setScale(1.5f);
    everyone[RADISH].mysp->setFlippedX(true);

    everyone[RABBIT].SetMyCharacter("character/rabbit_idle.png", 8, 34, 44);
    everyone[RABBIT].SetMyPosition(PIXELBLOCK(15.2f), PIXELBLOCK(3.4f));
    everyone[RABBIT].mysp->setScale(1.5f);
    everyone[RABBIT].mysp->setFlippedX(true);

    //select arrow
    if (!mydata.GetShopArrow())
        choice_num = 0;
    else
        choice_num = mydata.GetShopArrow();
    select_arrow = Sprite::create("map/select_arrow.png");
    select_arrow->setAnchorPoint(Vec2(0, 0));
    select_arrow->setPosition(Vec2(everyone[choice_num].my_pos_x + PIXELBLOCK(1), everyone[choice_num].my_pos_y + PIXELBLOCK(5)));
    shop_objlayer->addChild(select_arrow, 4);

    //windows
    for (int i = 0; i < 6; i++)
    {
        windows[i] = Sprite::create("map/shop_window.png");
        windows[i]->setAnchorPoint(Vec2(0, 0));
        if (mydata.GetStageState(i))
        {
            windows[i]->setPosition(Vec2(everyone[i + 1].my_pos_x - PIXELBLOCK(0.5f), everyone[i + 1].my_pos_y - PIXELBLOCK(0.7f)));
            shop_objlayer->addChild(everyone[i + 1].mysp, 2);
            shop_objlayer->addChild(windows[i]);
        }
    }
}

void GameShop::Layer_MENU()
{
    //return touch
    shop_go_back = MenuItemImage::create("map/shop_goback.png", "map/shop_goback.png", CC_CALLBACK_1(GameShop::GoBackMenu, this));
    shop_go_back->setAnchorPoint(Vec2(0, 0));
    shop_go_back->setPosition(Vec2(PIXELBLOCK(19.5f), PIXELBLOCK(36)));
    shop_go_back->setScale(1.5f);

    //character touch
    for (int i = 0; i < 6; i++)
    {
        character_select[i] = MenuItemImage::create("map/character_select2.png", "map/character_select2.png", CC_CALLBACK_1(GameShop::CharacterSelect, this));
        character_select[i]->setTag(i);
        character_select[i]->setAnchorPoint(Vec2(0, 0));
        character_select[i]->setPosition(-200, -200);
    }

    character_select[0]->setPosition(Vec2(PIXELBLOCK(3.8f), PIXELBLOCK(26.5f)));

    if (mydata.GetStageState(0))
        character_select[1]->setPosition(Vec2(PIXELBLOCK(14.8f), PIXELBLOCK(26.5f)));
    if (mydata.GetStageState(1))
        character_select[2]->setPosition(Vec2(PIXELBLOCK(3.8f), PIXELBLOCK(14.5f)));
    if (mydata.GetStageState(2))
        character_select[3]->setPosition(Vec2(PIXELBLOCK(14.8f), PIXELBLOCK(14.5f)));
    if (mydata.GetStageState(3))
        character_select[4]->setPosition(Vec2(PIXELBLOCK(3.8f), PIXELBLOCK(2.5f)));
    if (mydata.GetStageState(4))
        character_select[5]->setPosition(Vec2(PIXELBLOCK(14.8f), PIXELBLOCK(2.5f)));

    shop_menu = Menu::create(shop_go_back, character_select[0], character_select[1], character_select[2], character_select[3], character_select[4], character_select[5], nullptr);
    shop_menu->setAnchorPoint(Vec2(0, 0));
    shop_menu->setPosition(Vec2(0, 0));
    shop_menulayer->addChild(shop_menu);
}

void GameShop::GoBackMenu(Ref* pSender)
{
    shop_sound.ReturnSound();

    menu_scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(GoMenuScene(0.5f, menu_scene));
}

void GameShop::CharacterSelect(Ref* pSender)
{
    shop_sound.TouchSound();

    choice_num = reinterpret_cast<MenuItem*>(pSender)->getTag();

    switch (choice_num)
    {
    case 0:
        choice_name = "character/a_run.png";
        divide_num = 12;
        ch_width = 32;
        ch_height = 32;
        break;
    case 1:
        choice_name = "character/frog_run.png";
        divide_num = 12;
        ch_width = 32;
        ch_height = 32;
        break;
    case 2:
        choice_name = "character/pink_run.png";
        divide_num = 12;
        ch_width = 32;
        ch_height = 32;
        break;
    case 3:
        choice_name = "character/vguy_run.png";
        divide_num = 12;
        ch_width = 32;
        ch_height = 32;
        break;
    case 4:
        choice_name = "character/radish_run.png";
        divide_num = 12;
        ch_width = 30;
        ch_height = 38;
        break;
    case 5:
        choice_name = "character/rabbit_run.png";
        divide_num = 12;
        ch_width = 34;
        ch_height = 44;
        break;
    }

    select_arrow->setPosition(Vec2(everyone[choice_num].my_pos_x + PIXELBLOCK(1), everyone[choice_num].my_pos_y + PIXELBLOCK(5)));
    mydata.SetMyCharacter(choice_name);
    mydata.SetMyCharacterSize(divide_num, ch_width, ch_height);
    mydata.SetShopArrow(choice_num);
}

TransitionScene* GameShop::GoMenuScene(float time, Scene* scene)
{
    return TransitionFlipX::create(time, scene);
}