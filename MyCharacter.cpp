#include "MyCharacter.h"

void Mycharacter::SetMyCharacter(const std::string pname, float fnumber, float swidth, float sheight)
{
	mysp = Sprite::create(pname);
	mytex = mysp->getTexture();

	myani = Animation::create();
	myani->setDelayPerUnit(0.03f);

	//이미지 잘라서 프레임마다 저장
	for (int i = 0; i < fnumber; i++)
	{		
		myani->addSpriteFrameWithTexture(mytex, Rect(i * swidth, 0, swidth, sheight));
	}

	//첫 이미지 지정
	mysp = Sprite::createWithTexture(mytex, Rect(0, 0, swidth, sheight));

	//처음 위치
	my_pos_x = 175;
	my_pos_y = 32;
	mysp->setAnchorPoint(Vec2(0.0f, 0.0f));
	mysp->setPosition(Vec2(my_pos_x, my_pos_y));
	

	//첫 방향 설정
	if (sheight > 32)
	{
		move_speed = -4;
		flip_state = true;
	}
	else
	{
		move_speed = 4;
		flip_state = false;
	}

	isground = false;
	isplatform = false;
	
	//점프관련
	jump_max = 12;
	jump_fall_speed = 0.6f;
	jump_middle = false;
	jump_state = false;
	double_jump = 0;

	//Idle 애니메이션
	myanimate = Animate::create(myani);
	repfor = RepeatForever::create(myanimate);
	mysp->runAction(repfor);

	double_jump_animate = Animate::create(myani);
	double_jump_rot = RotateBy::create(0.3f, 360);

	double_jump_add = Spawn::createWithTwoActions(repfor, double_jump_rot);
}

void Mycharacter::SetMyPosition(float x, float y)
{
	my_pos_x = x;
	my_pos_y = y;

	mysp->setPosition(Vec2(my_pos_x, my_pos_y));
}

void Mycharacter::MoveLeftRight()
{
	if (double_jump > 2)
		jump_state = false;
	
	//바닥 뚫기 방지
	if (my_pos_y < 32)
	{
		my_pos_y = 32;
		return;
	}

	//점프
	if (jump_state && double_jump < 3)
	{
		//중력 효과(상승)
		if (jump_hight < jump_max && !jump_middle)
		{
			jump_hight += 2;
			//느려지는 부분 설정
			if (jump_hight == jump_max)
			{
				jump_middle = true;
			}
		}
		//올라가는 속도 점점 느려지게
		else if (jump_middle)
		{			
			jump_hight -= 1;
		}
		//점프 다 하면 떨어지게
		if (jump_hight <= 0)
		{	
			jump_state = false;
		}
	}

	//떨어질때 아무것도 충돌하지 않을때
	if (!jump_state && !isground && !isplatform)
	{	
		jump_hight -= jump_fall_speed;
	}
	//떨어지다가 바닥, 플랫폼과 충돌했을때
	if (!jump_state && (isground || isplatform))
	{
		jump_hight = 0;
		jump_middle = false;
		double_jump = 0;
	}
	
	//move
	if (flip_state)
	{
		if (my_pos_x < 32)
		{
			mysp->setFlippedX(true);
			move_speed = 4;
		}
		else if (my_pos_x > 292)
		{
			mysp->setFlippedX(false);
			move_speed = -4;
		}
	}
	else
	{
		if (my_pos_x < 32)
		{
			mysp->setFlippedX(false);
			move_speed = 4;
		}
		else if (my_pos_x > 292)
		{
			mysp->setFlippedX(true);
			move_speed = -4;
		}
	}

	my_pos_x += move_speed;
	my_pos_y += jump_hight;

	//위치 수정
	mysp->setPosition(Vec2(my_pos_x, my_pos_y));
}

void Mycharacter::Jump()
{
	//점프 활성화
	jump_state = true;
	isground = false;
	isplatform = false;

	jump_middle = false;
	jump_hight = 0;
}