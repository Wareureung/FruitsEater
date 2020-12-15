#ifndef __SAVEDATA_H__
#define __SAVEDATA_H__

#include "cocos2d.h"

USING_NS_CC;

class SaveData
{
private:
	bool stage_data;

	std::string now_my_character;
	int divide_number;
	float width_size;
	float height_size;

	int shop_arrow;

	int allocate_stage;

	std::string now_stage_name;
	std::string now_stage_ground_name;
	std::string now_stage_platform_name;
	std::string now_stage_fruit_name;

public:
	SaveData()
	{
		if (!GetStageState(0))
		{
			UserDefault::getInstance()->setStringForKey("my_name_is", "character/a_run.png");
			UserDefault::getInstance()->setIntegerForKey("my_character_divide", 12);
			UserDefault::getInstance()->setFloatForKey("my_character_width", 32);
			UserDefault::getInstance()->setIntegerForKey("my_character_height", 32);
			UserDefault::getInstance()->setIntegerForKey("shop_arrow", 0);
		}
	}

	//stage state
	void SetStageState(int stage_num) { UserDefault::getInstance()->setBoolForKey("stage" + stage_num, true); }
	bool GetStageState(int stage_num) { return stage_data = UserDefault::getInstance()->getBoolForKey("stage" + stage_num); }

	//character
	void SetMyCharacter(const std::string my_name) { UserDefault::getInstance()->setStringForKey("my_name_is", my_name); }
	std::string GetMyCharacter() { return now_my_character = UserDefault::getInstance()->getStringForKey("my_name_is"); }
		
	void SetMyCharacterSize(int divide_num, float width, float height) 
	{
		UserDefault::getInstance()->setIntegerForKey("my_character_divide", divide_num);
		UserDefault::getInstance()->setFloatForKey("my_character_width", width);
		UserDefault::getInstance()->setIntegerForKey("my_character_height", height);
	}
	int GetDivide() { return divide_number = UserDefault::getInstance()->getIntegerForKey("my_character_divide"); }
	float GetWidth() { return width_size = UserDefault::getInstance()->getIntegerForKey("my_character_width"); }
	float GetHeight() {	return height_size = UserDefault::getInstance()->getIntegerForKey("my_character_height"); }

	//shop arrow
	void SetShopArrow(int arrow_num) { UserDefault::getInstance()->setIntegerForKey("shop_arrow", arrow_num); }
	int GetShopArrow() { return shop_arrow = UserDefault::getInstance()->getIntegerForKey("shop_arrow"); }

	//stage state
	void AllocateStageScene(int stage) { UserDefault::getInstance()->setIntegerForKey("allow_stage", stage); }
	int GetAllocateStageScene() { return allocate_stage = UserDefault::getInstance()->getIntegerForKey("allow_stage");	}

	void SetStageName(std::string stage_name, std::string ground_name, std::string platform_name, std::string fruit_name) 
	{
		UserDefault::getInstance()->setStringForKey("stage_bg_name", stage_name);
		UserDefault::getInstance()->setStringForKey("stage_ground_name", ground_name);
		UserDefault::getInstance()->setStringForKey("stage_platform_name", platform_name);
		UserDefault::getInstance()->setStringForKey("stage_fruit_name", fruit_name);
	}
	std::string GetStageName() {return now_stage_name = UserDefault::getInstance()->getStringForKey("stage_bg_name"); }
	std::string GetStageGroundName() { return now_stage_ground_name = UserDefault::getInstance()->getStringForKey("stage_ground_name"); }
	std::string GetStagePlatFormName() { return now_stage_platform_name = UserDefault::getInstance()->getStringForKey("stage_platform_name"); }
	std::string GetStageFruitName() { return now_stage_fruit_name = UserDefault::getInstance()->getStringForKey("stage_fruit_name"); }

	void SetMainTitleBG(bool state) { UserDefault::getInstance()->setBoolForKey("main_title_bg", state); }
	bool GetMainTitleBG() { return UserDefault::getInstance()->getBoolForKey("main_title_bg"); }

	void SetThanksForPlaying() { UserDefault::getInstance()->setBoolForKey("thanks_for_playing", true); }
	bool GetThanksForPlaying() { return UserDefault::getInstance()->getBoolForKey("thanks_for_playing"); }

	void SetDoubleJumpUnLock() { UserDefault::getInstance()->setBoolForKey("double_jump_unlock", true); }
	bool GetDoubleJumpUnLock() { return UserDefault::getInstance()->getBoolForKey("double_jump_unlock"); }

	void SetStageSelectExplain() { UserDefault::getInstance()->setBoolForKey("stage_select_ex", true); }
	bool GetStageSelectExplain() { return UserDefault::getInstance()->getBoolForKey("stage_select_ex"); }
};
#endif