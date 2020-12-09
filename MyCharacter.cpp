#include "MyCharacter.h"

void Mycharacter::SetMyCharacter(const std::string pname, float fnumber, float swidth, float sheight)
{
	mysp = Sprite::create(pname);
	mytex = mysp->getTexture();

	myani = Animation::create();
	myani->setDelayPerUnit(0.03f);

	//�̹��� �߶� �����Ӹ��� ����
	for (int i = 0; i < fnumber; i++)
	{		
		myani->addSpriteFrameWithTexture(mytex, Rect(i * swidth, 0, swidth, sheight));
	}

	//ù �̹��� ����
	mysp = Sprite::createWithTexture(mytex, Rect(0, 0, swidth, sheight));

	//ó�� ��ġ
	my_pos_x = 175;
	my_pos_y = 32;
	mysp->setAnchorPoint(Vec2(0.0f, 0.0f));
	mysp->setPosition(Vec2(my_pos_x, my_pos_y));
	

	//ù ���� ����
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
	
	//��������
	jump_max = 12;
	jump_fall_speed = 0.6f;
	jump_middle = false;
	jump_state = false;
	double_jump = 0;

	//Idle �ִϸ��̼�
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
	
	//�ٴ� �ձ� ����
	if (my_pos_y < 32)
	{
		my_pos_y = 32;
		return;
	}

	//����
	if (jump_state && double_jump < 3)
	{
		//�߷� ȿ��(���)
		if (jump_hight < jump_max && !jump_middle)
		{
			jump_hight += 2;
			//�������� �κ� ����
			if (jump_hight == jump_max)
			{
				jump_middle = true;
			}
		}
		//�ö󰡴� �ӵ� ���� ��������
		else if (jump_middle)
		{			
			jump_hight -= 1;
		}
		//���� �� �ϸ� ��������
		if (jump_hight <= 0)
		{	
			jump_state = false;
		}
	}

	//�������� �ƹ��͵� �浹���� ������
	if (!jump_state && !isground && !isplatform)
	{	
		jump_hight -= jump_fall_speed;
	}
	//�������ٰ� �ٴ�, �÷����� �浹������
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

	//��ġ ����
	mysp->setPosition(Vec2(my_pos_x, my_pos_y));
}

void Mycharacter::Jump()
{
	//���� Ȱ��ȭ
	jump_state = true;
	isground = false;
	isplatform = false;

	jump_middle = false;
	jump_hight = 0;
}