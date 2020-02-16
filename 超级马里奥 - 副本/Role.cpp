#include"User.h"
//��ʼ�������
Mario::Mario(int a)
{
	offsetX = 0;
	offsetY = 0;
	death = 0;
	getCoin = 0;
	getDeath = 0;
	if (a == 1)
	{
		x = 0;
		y = 18;
		all[0][18] = mario;
	}
	else if (a == 2)
	{
		x = 0;
		y = 1;
		all[0][1] = mario;
	}
	else if (a == 3)
	{
		x = 0;
		y = 18;
		all[0][18] = mario;
	}
}

//�����õİ�����Ϣ
void Mario::dealKey()
{
	//����ָ��
	if (key == 'a')
	{
		//�����ұߣ�ֱ�ӵ�ͷ����
		if (isRight)
		{
			isRight = false;
			currentImage = left;
		}
		//������ߣ���Ҫ�ж��ܷ��ƶ�
		else
		{
			//�����ƶ�
			if (x - 1 >= 0 && all[x - 1][y] == null)
			{
				//����һ������ָ��
				offsetX = 32;
				isMove = true;
				all[x][y] = null;
				x-=1;
				all[x][y] = mario;
			}
		}
	}

	if (key == 'd')
	{
		if (isRight)
		{
			//�����ƶ�
			if (x + 1 < 20 && all[x + 1][y] == null)
			{
				//����һ������ָ��
				offsetX = -32;
				isMove = true;
				//���µ�ͼ
				all[x][y] = null;
				x+=1;
				all[x][y] = mario;
			}
		}
		else
		{
			isRight = true;
			currentImage = right;
		}
	}

	//��Ծ��
	if (key == 'j')
	{
		//һ������3�����ӵĸ߶�
		if (isJump == false && y - 1 >= 0 && all[x][y - 1] == null)
		{
			isJump = true;
			//ʣ����Ҫ�����ĸ���
			h = 2;
			all[x][y] = null;
			y-=1;
			all[x][y] = mario;
			offsetY = 32;
		}
	}
}

void Mario::update(Cold c[], Wugui tor[], Nut n[], Flowers f[])
{
	if (isDead == false)
	{
		updateMar(c, tor, n, f);
	}
	if (isDead && death > 0)
	{
		if (offsetY == 0)
		{
			death -= 1;
			y += 1;
			offsetY = -32;
		}
		else
			offsetY += 4;
	}//������Ϸ
}

//��������µ�λ�õ���Ϣ
void Mario::updateMar(Cold c[], Wugui tor[], Nut n[], Flowers f[])
{
	//�ƶ�״̬�£��������κ�ָ�ֱ������ƶ�
	if (isMove)
	{
		updateMarMove();
	}
	//���ƶ�״̬�����Խ���ָ�������Ծ״̬��
	else
	{
		dealKey();
	}
	//������ֱ����
	if (isJump)
	{
		updateVertical();
	}
	get(c, tor, n);//��ȡ��� ����Ģ���ڹ�
	isDeaded(f, tor, n);//�ж�����
	updateDown();
}

//��������µ��ƶ�״̬
void Mario::updateMarMove()
{
	//����Ϊ�ұ�
	if (isRight)
	{
		++offsetX;
		++counter;
		int t = counter / N;
		if (t % 2)
		{
			currentImage = right;
		}
		else
		{
			currentImage = rightMove;
		}
	}
	else//���
	{
		--offsetX;
		++counter;
		int t = counter / N;
		if (t % 2)
		{
			currentImage = left;
		}
		else
		{
			currentImage = leftMove;
		}
	}

	//�ƶ����
	if (offsetX == 0)
	{
		isMove = false;
		if (isRight)
			currentImage = right;
		else
			currentImage = left;
		offsetX = 0;
		counter = 0;
	}
}

//������ֱ����
void Mario::updateVertical()
{
	if (isRight)
	{
		currentImage = rightJump;
	}
	else
	{
		currentImage = leftJump;
	}
	//����
	if (h >= 0)
	{
		updateVerticalUp();
	}
	//����
	else
	{
		updateVerticalDown();
	}
}

//���������������Ծ
void Mario::updateVerticalUp()
{
	offsetY -= 2;

	//һ���ƶ����
	if (offsetY == 0)
	{
		--h;
		if (h >= 0)
		{
			//�Ϸ�û����ײ
			if (y - 1 >= 0 && all[x][y - 1] == null)
			{
				all[x][y] = null;
				--y;
				all[x][y] = mario;
				offsetY = 32;
			}
			else
			{
				//���ȼ���Ƿ��Ѿ�����ˣ��ڿ��з�����λ�Ƶ�������ܻ�������������
				if (all[x][y + 1] == land1 || all[x][y + 1] == land2 || all[x][y + 1] == land3 || all[x][y] == land4)
				{
					isJump = false;
					h = 0;
					if (isRight)
					{
						currentImage = right;
					}
					else
					{
						currentImage = left;
					}
				}
				else
				{
					h = -1;//����ײ��������������״̬����������һЩ�߼�
					all[x][y] = null;
					++y;
					all[x][y] = mario;
					offsetY = -32;
				}
			}
		}
		else
		{
			if (all[x][y + 1] == land1 || all[x][y + 1] == land2 || all[x][y + 1] == land3 || all[x][y + 1] == land4)
			{
				isJump = false;
				h = 0;
				if (isRight)
				{
					currentImage = right;
				}
				else
				{
					currentImage = left;
				}
			}
			else
			{
				all[x][y] = null;
				++y;
				all[x][y] = mario;
				offsetY = -32;
			}
		}
	}
}

//������������½���
void Mario::updateVerticalDown()
{
	Mario::offsetY += 2;
	//һ���ƶ����
	if (offsetY == 0)
	{
		//���ȼ���Ƿ��Ѿ������
		if (all[x][y + 1] != null)
		{
			Mario::isJump = false;
			Mario::h = 0;
			if (Mario::isRight)
			{
				Mario::currentImage = Mario::right;
			}
			else
			{
				Mario::currentImage = Mario::left;
			}
		}
		else
		{
			if (all[x][y + 1] == land1 || all[x][y + 1] == land2 || all[x][y + 1] == land3 || all[x][y + 1] == land4)
			{
				Mario::isJump = false;
				Mario::h = 0;
				if (Mario::isRight)
				{
					Mario::currentImage = Mario::right;
				}
				else
				{
					Mario::currentImage = Mario::left;
				}
			}
			else
			{
				all[x][y] = null;
				++y;
				all[x][y] = mario;
				offsetY = -32;
			}
		}
	}
}

//��ȡ��� ����Ģ���ڹ�
void Mario::get(Cold c[], Wugui tor[], Nut n[])
{
	//�ȵ��ڹ�
	for (int i = 0; i < 2; ++i)
	{
		if (x == tor[i].x && (y + 1) == tor[i].y && !tor[i].isSui)
		{
			if (tor[i].isDead)
			{
				tor[i].isSui = true;
				all[tor[i].x][tor[i].y] = null;
			}
			else
			{
				tor[i].isDead = true;
				Mario::getDeath+=1;
				tor[i].currentImage = tor[i].torDead;
			}
			Mario::isJump = true;
			Mario::h = 1;
			all[x][y] = null;
			y-=1;
			all[x][y] = mario;
			offsetY = 32;
		}
	}
	//��ý��
	for (int i = 0; i < 5; ++i)
	{
		if (Mario::x == c[i].x && Mario::y == c[i].y && !c[i].isDead)
		{
			c[i].isDead = true;
			Mario::getCoin += 1;
		}
	}
	//��������
	for (int i = 0; i < 4; ++i)
	{
		if (Mario::x == n[i].x && (y + 1) == n[i].y && !n[i].isDead)
		{
			n[i].isDead = true;
			Mario::getDeath+=1;
			Mario::isJump = true;
			Mario::h = 1;
			all[x][y] = null;
			--y;
			all[x][y] = mario;
			offsetY = 32;
			n[i].currentImage = n[i].nutDead;
			n[i].death = 32;
		}
	}
}

//�ж�����
void Mario::isDeaded(Flowers f[], Wugui tor[], Nut n[])
{
	for (int i = 0; i < 4; ++i)		//ײ������
	{
		if (Mario::x == n[i].x && y == n[i].y && !Mario::isDead && !n[i].isDead)
		{
			Mario::isDead = true;
			hasLife -= 1;
			Mario::offsetY = -32;
			Mario::currentImage = dead;
			Mario::death = 5;
			break;
		}
	}
	for (int i = 0; i < 2; ++i)		//ײ��ʳ�˻�
	{
		if ((Mario::x == f[i].x && Mario::y == f[i].y) || (Mario::x == f[i].x && (Mario::y + 1) == f[i].y))
		{
			Mario::isDead = true;
			--Mario::hasLife;
			Mario::offsetY = -32;
			Mario::currentImage = dead;
			Mario::death = 5;
			break;
		}
	}
	for (int i = 0; i < 2; ++i)		//ײ���ڹ�
	{
		if (x == tor[i].x && y == tor[i].y && !tor[i].isSui)
		{
			isDead = true;
			hasLife -= 1;
			offsetY = -32;
			currentImage = dead;
			death = 5;
			break;
		}
	}
	if (y == 19 && h < 0)
	{
		isDead = true;
		hasLife -= 1;
		offsetY = -32;
		currentImage = dead;
		death = 5;
	}
}

//�ж��Ƿ���Ҫ����
void Mario::updateDown()
{
	//�ж��Ƿ���Ҫ����
	if (!isJump && !isMove)
	{
		if (all[x][y + 1] == null)
		{
			isJump = true;
			offsetY -= 32;
			h = -1;//��ʾ���½�
			all[x][y] = null;
			y++;
			all[x][y] = mario;
		}
	}
}

//����ʳ�˻�
void Flowers::updateFlo()
{
	int cun = cc / 10;
	if (cun % 2)
		currentImage = open;
	else
		currentImage = close;
	++cc;
}

//�����ڹ�
void Wugui::updateTor()
{
	if (!isSui)
	{
		if (x <= rightLimit && x >= leftLimit)//û���ڱ߽�
		{
			if (x == leftLimit)
			{
				isRight = true;
			}
			else if (x == rightLimit)
			{
				isRight = false;
			}
			if (isRight)
			{
				++offsetX;
				++counter;
				int t = counter / N;
				if (t % 2)
				{
					if (isDead)
						currentImage = torDead;
					else
						currentImage = right;
				}
				else
				{
					if (isDead)
						currentImage = torDead;
					else
						currentImage = rightMove;
				}
				if (offsetX == 32)
				{
					all[x][y] = null;
					++x;
					all[x][y] = nut;
					offsetX = 0;
				}
			}
			else
			{
				--offsetX;
				++counter;
				int t = counter / N;
				if (t % 2)
				{
					if (isDead)
						currentImage = torDead;
					else
						currentImage = left;
				}
				else
				{
					if (isDead)
						currentImage = torDead;
					else
						currentImage = leftMove;
				}
				if (offsetX == -32)
				{
					all[x][y] = null;
					--x;
					all[x][y] = nut;
					offsetX = 0;
				}
			}
		}
	}
}

//���°���
void Nut::updateNut()
{
	if (!isDead)
	{
		if (x <= rightLimit && x >= leftLimit)//û���ڱ߽�
		{
			if (x == leftLimit)
			{
				isRight = true;
			}
			else if (x == rightLimit)
			{
				isRight = false;
			}
			if (isRight)
			{
				++offsetX;
				++counter;
				int t = counter / N;
				if (t % 2)
				{
					currentImage = nutRight;
				}
				else
				{
					currentImage = nutLeft;
				}
				if (offsetX == 32)
				{
					all[x][y] = null;
					++x;
					all[x][y] = nut;
					offsetX = 0;
				}
			}
			else
			{
				--offsetX;
				++counter;
				int t = counter / N;
				if (t % 2)
				{
					currentImage = nutRight;
				}
				else
				{
					currentImage = nutLeft;
				}
				if (offsetX == -32)
				{
					all[x][y] = null;
					--x;
					all[x][y] = nut;
					offsetX = 0;
				}
			}
		}
	}
	

	//��������
	if (isDead && death > 0)
	{
		--death;
	}
	else if (isDead && death == 0)
	{
		all[x][y] = null;
	}
}