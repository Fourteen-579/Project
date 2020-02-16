#include"User.h"
//初始化马里奥
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

//处理获得的按键信息
void Mario::dealKey()
{
	//左移指令
	if (key == 'a')
	{
		//朝向右边，直接掉头即可
		if (isRight)
		{
			isRight = false;
			currentImage = left;
		}
		//朝向左边，需要判断能否移动
		else
		{
			//可以移动
			if (x - 1 >= 0 && all[x - 1][y] == null)
			{
				//构造一个左移指令
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
			//可以移动
			if (x + 1 < 20 && all[x + 1][y] == null)
			{
				//构造一个右移指令
				offsetX = -32;
				isMove = true;
				//更新地图
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

	//跳跃键
	if (key == 'j')
	{
		//一次能跳3个格子的高度
		if (isJump == false && y - 1 >= 0 && all[x][y - 1] == null)
		{
			isJump = true;
			//剩余需要上升的格子
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
	}//结束游戏
}

//更新马里奥的位置等信息
void Mario::updateMar(Cold c[], Wugui tor[], Nut n[], Flowers f[])
{
	//移动状态下，不接受任何指令，直到完成移动
	if (isMove)
	{
		updateMarMove();
	}
	//非移动状态，可以接受指令，包括跳跃状态下
	else
	{
		dealKey();
	}
	//更新竖直方向
	if (isJump)
	{
		updateVertical();
	}
	get(c, tor, n);//获取金币 踩死蘑菇乌龟
	isDeaded(f, tor, n);//判断死亡
	updateDown();
}

//更新马里奥的移动状态
void Mario::updateMarMove()
{
	//朝向为右边
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
	else//左边
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

	//移动完成
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

//更新竖直方向
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
	//上升
	if (h >= 0)
	{
		updateVerticalUp();
	}
	//下落
	else
	{
		updateVerticalDown();
	}
}

//更新马里奥向上跳跃
void Mario::updateVerticalUp()
{
	offsetY -= 2;

	//一格移动完成
	if (offsetY == 0)
	{
		--h;
		if (h >= 0)
		{
			//上方没有碰撞
			if (y - 1 >= 0 && all[x][y - 1] == null)
			{
				all[x][y] = null;
				--y;
				all[x][y] = mario;
				offsetY = 32;
			}
			else
			{
				//首先检测是否已经落地了（在空中发生了位移的情况可能会造成这种情况）
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
					h = -1;//有碰撞，立即进入下落状态，或者其它一些逻辑
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

//更新马里奥向下降落
void Mario::updateVerticalDown()
{
	Mario::offsetY += 2;
	//一格移动完成
	if (offsetY == 0)
	{
		//首先检测是否已经落地了
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

//获取金币 踩死蘑菇乌龟
void Mario::get(Cold c[], Wugui tor[], Nut n[])
{
	//踩到乌龟
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
	//获得金币
	for (int i = 0; i < 5; ++i)
	{
		if (Mario::x == c[i].x && Mario::y == c[i].y && !c[i].isDead)
		{
			c[i].isDead = true;
			Mario::getCoin += 1;
		}
	}
	//踩死板栗
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

//判断死亡
void Mario::isDeaded(Flowers f[], Wugui tor[], Nut n[])
{
	for (int i = 0; i < 4; ++i)		//撞到板栗
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
	for (int i = 0; i < 2; ++i)		//撞到食人花
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
	for (int i = 0; i < 2; ++i)		//撞到乌龟
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

//判断是否需要下落
void Mario::updateDown()
{
	//判断是否需要下落
	if (!isJump && !isMove)
	{
		if (all[x][y + 1] == null)
		{
			isJump = true;
			offsetY -= 32;
			h = -1;//表示在下降
			all[x][y] = null;
			y++;
			all[x][y] = mario;
		}
	}
}

//更新食人花
void Flowers::updateFlo()
{
	int cun = cc / 10;
	if (cun % 2)
		currentImage = open;
	else
		currentImage = close;
	++cc;
}

//更新乌龟
void Wugui::updateTor()
{
	if (!isSui)
	{
		if (x <= rightLimit && x >= leftLimit)//没有在边界
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

//更新板栗
void Nut::updateNut()
{
	if (!isDead)
	{
		if (x <= rightLimit && x >= leftLimit)//没有在边界
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
	

	//板栗死亡
	if (isDead && death > 0)
	{
		--death;
	}
	else if (isDead && death == 0)
	{
		all[x][y] = null;
	}
}