#include"Game.h"
int key;
int counter;

struct mario mar;
struct wugui tor[2];
struct coin c[5];
struct nut n[4];
struct map m;
struct flowers f[2];

char user_current[100];

//更新游戏数据
void updateGame()
{
	mar.death = 1;
	mar.getCoin = 0;
	mar.getDeath = 0;
	mar.offsetX = 0;
	mar.offsetY = 0;

	mar.isRight = true;
	mar.isJump = false;
	mar.isMove = false;
	mar.isDead = false;
	mar.currentImage = mar.right;

	for (int i = 0; i < 5; ++i)
		c[i].isDead = false;
	for (int i = 0; i < 4; ++i)
		n[i].isDead = false;
	for (int i = 0; i < 2; ++i)
	{
		tor[i].isDead = false;
		tor[i].isSui = false;
	}
}

//获取输入
void input()
{
	key = -1;
	int j = keystate('J');
	int a = keystate('A');
	int d = keystate('D');
	if (!mar.isJump)
	{
		if (j)
			key = 'j';
		else if (a)
			key = 'a';
		else if (d)
			key = 'd';
	}
	else
	{
		if (a)
			key = 'a';
		else if (d)
			key = 'd';
		else if (j)
			key = 'j';
	}
}

void update()
{
	//马里奥存活
	if (!mar.isDead)
	{
		//更新马里奥
		updateMar();
		//更新自动的板栗
		updateNut();
		//更新自动的乌龟
		updateTor();
		//更新食人花
		updateFlo();
	}
	//马里奥死亡
	if (mar.isDead && mar.death > 0)
	{
		if (mar.offsetY == 0)
		{
			mar.death -= 1;
			mar.y += 1;
			mar.offsetY = -32;
		}
		else
			mar.offsetY += 4;
	}//结束游戏
}

//更新马里奥的位置等信息
void updateMar()
{
	//移动状态下，不接受任何指令，直到完成移动
	if (mar.isMove)
	{
		updateMarMove();
	}
	//非移动状态，可以接受指令，包括跳跃状态下
	else
	{
		dealKey();
	}
	//更新竖直方向
	if (mar.isJump)
	{
		updateVertical();
	}
	get();
	isDeaded();
	updateDown();
}

//更新马里奥的移动状态
void updateMarMove()
{
	//朝向为右边
	if (mar.isRight)
	{
		++mar.offsetX;
		++counter;
		int t = counter / N;
		if (t % 2)
		{
			mar.currentImage = mar.right;
		}
		else
		{
			mar.currentImage = mar.rightMove;
		}
	}
	else//左边
	{
		--mar.offsetX;
		++counter;
		int t = counter / N;
		if (t % 2)
		{
			mar.currentImage = mar.left;
		}
		else
		{
			mar.currentImage = mar.leftMove;
		}
	}

	//移动完成
	if (mar.offsetX == 0)
	{
		mar.isMove = false;
		if (mar.isRight)
			mar.currentImage = mar.right;
		else
			mar.currentImage = mar.left;
		mar.offsetX = 0;
		counter = 0;
	}
}

//处理获得的按键信息
void dealKey()
{
	//左移指令
	if (key == 'a')
	{
		//朝向右边，直接掉头即可
		if (mar.isRight)
		{
			mar.isRight = false;
			mar.currentImage = mar.left;
		}
		//朝向左边，需要判断能否移动
		else
		{
			//可以移动
			if (mar.x - 1 >= 0 && m.all[mar.x - 1][mar.y] == null)
			{
				//构造一个左移指令
				mar.offsetX = 32;
				mar.isMove = true;
				m.all[mar.x][mar.y] = null;
				--mar.x;
				m.all[mar.x][mar.y] = mario;
			}
		}
	}

	if (key == 'd')
	{
		if (mar.isRight)
		{
			//可以移动
			if (mar.x + 1 < 20 && m.all[mar.x + 1][mar.y] == null)
			{
				//构造一个右移指令
				mar.offsetX = -32;
				mar.isMove = true;
				//更新地图
				m.all[mar.x][mar.y] = null;
				++mar.x;
				m.all[mar.x][mar.y] = mario;
			}
		}
		else
		{
			mar.isRight = true;
			mar.currentImage = mar.right;
		}
	}

	//跳跃键
	if (key == 'j')
	{
		//一次能跳3个格子的高度
		if (mar.isJump == false && mar.y - 1 >= 0 && m.all[mar.x][mar.y - 1] == null)
		{
			mar.isJump = true;
			//剩余需要上升的格子
			mar.h = 2;
			m.all[mar.x][mar.y] = null;
			--mar.y;
			m.all[mar.x][mar.y] = mario;
			mar.offsetY = 32;
		}
	}
}

//更新竖直方向
void updateVertical()
{
	if (mar.isRight)
	{
		mar.currentImage = mar.rightJump;
	}
	else
	{
		mar.currentImage = mar.leftJump;
	}
	//上升
	if (mar.h >= 0)
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
void updateVerticalUp()
{
	mar.offsetY -= 2;

	//一格移动完成
	if (mar.offsetY == 0)
	{
		--mar.h;
		if (mar.h >= 0)
		{
			//上方没有碰撞
			if (mar.y - 1 >= 0 && m.all[mar.x][mar.y - 1] == null)
			{
				m.all[mar.x][mar.y] = null;
				--mar.y;
				m.all[mar.x][mar.y] = mario;
				mar.offsetY = 32;
			}
			else
			{
				//首先检测是否已经落地了（在空中发生了位移的情况可能会造成这种情况）
				if (m.all[mar.x][mar.y + 1] == land1 || m.all[mar.x][mar.y + 1] == land2 || m.all[mar.x][mar.y + 1] == land3 || m.all[mar.x][mar.y] == land4)
				{
					mar.isJump = false;
					mar.h = 0;
					if (mar.isRight)
					{
						mar.currentImage = mar.right;
					}
					else
					{
						mar.currentImage = mar.left;
					}
				}
				else
				{
					mar.h = -1;//有碰撞，立即进入下落状态，或者其它一些逻辑
					m.all[mar.x][mar.y] = null;
					++mar.y;
					m.all[mar.x][mar.y] = mario;
					mar.offsetY = -32;
				}
			}
		}
		else
		{
			if (m.all[mar.x][mar.y + 1] == land1 || m.all[mar.x][mar.y + 1] == land2 || m.all[mar.x][mar.y + 1] == land3 || m.all[mar.x][mar.y + 1] == land4)
			{
				mar.isJump = false;
				mar.h = 0;
				if (mar.isRight)
				{
					mar.currentImage = mar.right;
				}
				else
				{
					mar.currentImage = mar.left;
				}
			}
			else
			{
				m.all[mar.x][mar.y] = null;
				++mar.y;
				m.all[mar.x][mar.y] = mario;
				mar.offsetY = -32;
			}
		}
	}
}

//更新马里奥向下降落
void updateVerticalDown()
{
	mar.offsetY += 2;
	//一格移动完成
	if (mar.offsetY == 0)
	{
		//首先检测是否已经落地了
		if (m.all[mar.x][mar.y + 1] != null)
		{
			mar.isJump = false;
			mar.h = 0;
			if (mar.isRight)
			{
				mar.currentImage = mar.right;
			}
			else
			{
				mar.currentImage = mar.left;
			}
		}
		else
		{
			if (m.all[mar.x][mar.y + 1] == land1 || m.all[mar.x][mar.y + 1] == land2 || m.all[mar.x][mar.y + 1] == land3 || m.all[mar.x][mar.y + 1] == land4)
			{
				mar.isJump = false;
				mar.h = 0;
				if (mar.isRight)
				{
					mar.currentImage = mar.right;
				}
				else
				{
					mar.currentImage = mar.left;
				}
			}
			else
			{
				m.all[mar.x][mar.y] = null;
				++mar.y;
				m.all[mar.x][mar.y] = mario;
				mar.offsetY = -32;
			}
		}
	}
}

//获取金币 踩死蘑菇乌龟
void get()
{
	//踩到乌龟
	for (int i = 0; i < 2; ++i)
	{
		if (mar.x == tor[i].x && (mar.y + 1) == tor[i].y && !tor[i].isSui)
		{
			if (tor[i].isDead)
			{
				tor[i].isSui = true;
				m.all[tor[i].x][tor[i].y] = null;
			}
			else
			{
				tor[i].isDead = true;
				++mar.getDeath;
				tor[i].currentImage = tor[i].torDead;
			}
			mar.isJump = true;
			mar.h = 1;
			m.all[mar.x][mar.y] = null;
			--mar.y;
			m.all[mar.x][mar.y] = mario;
			mar.offsetY = 32;
		}
	}

	for (int i = 0; i < 5; ++i)		//获得金币
	{
		if (mar.x == c[i].x && mar.y == c[i].y && !c[i].isDead)
		{
			c[i].isDead = true;
			mar.getCoin += 1;
		}
	}

	for (int i = 0; i < 4; ++i)		//踩死板栗
	{
		if (mar.x == n[i].x && (mar.y + 1) == n[i].y && !n[i].isDead)
		{
			n[i].isDead = true;
			++mar.getDeath;
			mar.isJump = true;
			mar.h = 1;
			m.all[mar.x][mar.y] = null;
			--mar.y;
			m.all[mar.x][mar.y] = mario;
			mar.offsetY = 32;
			n[i].currentImage = n[i].nutDead;
			n[i].death = 32;
		}
	}
}

//判断死亡
void isDeaded()
{
	for (int i = 0; i < 4; ++i)		//撞到板栗
	{
		if (mar.x == n[i].x && mar.y == n[i].y && !mar.isDead && !n[i].isDead)
		{
			mar.isDead = true;
			--mar.hasLife;
			mar.offsetY = -32;
			mar.currentImage = mar.dead;
			mar.death = 5;
			break;
		}
	}
	for (int i = 0; i < 2; ++i)		//撞到食人花
	{
		if ((mar.x == f[i].x && mar.y == f[i].y) || (mar.x == f[i].x && (mar.y + 1) == f[i].y))
		{
			mar.isDead = true;
			--mar.hasLife;
			mar.offsetY = -32;
			mar.currentImage = mar.dead;
			mar.death = 5;
			break;
		}
	}
	for (int i = 0; i < 2; ++i)		//撞到乌龟
	{
		if (mar.x == tor[i].x && mar.y == tor[i].y && !tor[i].isSui)
		{
			mar.isDead = true;
			--mar.hasLife;
			mar.offsetY = -32;
			mar.currentImage = mar.dead;
			mar.death = 5;
			break;
		}
	}
	if (mar.y == 19 && mar.h < 0)
	{
		mar.isDead = true;
		--mar.hasLife;
		mar.offsetY = -32;
		mar.currentImage = mar.dead;
		mar.death = 5;
	}
}

//判断是否需要下落
void updateDown()
{
	//判断是否需要下落
	if (!mar.isJump && !mar.isMove)
	{
		if (m.all[mar.x][mar.y + 1] == null)
		{
			mar.isJump = true;
			mar.offsetY -= 32;
			mar.h = -1;//表示在下降
			m.all[mar.x][mar.y] = null;
			mar.y++;
			m.all[mar.x][mar.y] = mario;
		}
	}
}

//更新乌龟
void updateTor()
{
	for (int i = 0; i < 2; ++i)
	{
		if (!tor[i].isSui)
		{
			if (tor[i].x <= tor[i].rightLimit && tor[i].x >= tor[i].leftLimit)//没有在边界
			{
				if (tor[i].x == tor[i].leftLimit)
				{
					tor[i].isRight = true;
				}
				else if (tor[i].x == tor[i].rightLimit)
				{
					tor[i].isRight = false;
				}
				if (tor[i].isRight)
				{
					++tor[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].right;
					}
					else
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].rightMove;
					}
					if (tor[i].offsetX == 32)
					{
						m.all[tor[i].x][tor[i].y] = null;
						++tor[i].x;
						m.all[tor[i].x][tor[i].y] = nut;
						tor[i].offsetX = 0;
					}
				}
				else
				{
					--tor[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].left;
					}
					else
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].leftMove;
					}
					if (tor[i].offsetX == -32)
					{
						m.all[tor[i].x][tor[i].y] = null;
						--tor[i].x;
						m.all[tor[i].x][tor[i].y] = nut;
						tor[i].offsetX = 0;
					}
				}
			}
		}
	}
}

//更新板栗
void updateNut()
{
	for (int i = 0; i < 4; ++i)
	{
		if (!n[i].isDead)
		{
			if (n[i].x <= n[i].rightLimit && n[i].x >= n[i].leftLimit)//没有在边界
			{
				if (n[i].x == n[i].leftLimit)
				{
					n[i].isRight = true;
				}
				else if (n[i].x == n[i].rightLimit)
				{
					n[i].isRight = false;
				}
				if (n[i].isRight)
				{
					++n[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						n[i].currentImage = n[i].nutRight;
					}
					else
					{
						n[i].currentImage = n[i].nutLeft;
					}
					if (n[i].offsetX == 32)
					{
						m.all[n[i].x][n[i].y] = null;
						++n[i].x;
						m.all[n[i].x][n[i].y] = nut;
						n[i].offsetX = 0;
					}
				}
				else
				{
					--n[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						n[i].currentImage = n[i].nutRight;
					}
					else
					{
						n[i].currentImage = n[i].nutLeft;
					}
					if (n[i].offsetX == -32)
					{
						m.all[n[i].x][n[i].y] = null;
						--n[i].x;
						m.all[n[i].x][n[i].y] = nut;
						n[i].offsetX = 0;
					}
				}
			}
		}
	}

	//板栗死亡
	for (int i = 0; i < 4; ++i)
	{
		if (n[i].isDead && n[i].death > 0)
		{
			--n[i].death;
		}
		else if (n[i].isDead && n[i].death == 0)
		{
			m.all[n[i].x][n[i].y] = null;
		}
	}
}

//更新食人花
void updateFlo()
{
	for (int i = 0; i < 2; ++i)
	{
		int cun = f[i].cc / 10;
		if (cun % 2)
			f[i].currentImage = f[i].open;
		else
			f[i].currentImage = f[i].close;
		++f[i].cc;
	}
}

//输出图片
void render()
{
	cleardevice();
	putimage(0, 0, img);
	putimage(13 * 32, 0, nums);


	setcolor(BLACK);
	setbkmode(TRANSPARENT);			//设置文字背景色为透明(默认为有背景色)
	setfont(32, 0, "幼圆");
	char a[10];
	sprintf(a, "%c", mar.getCoin + 48);
	outtextxy(18 * 32, 0, a);
	sprintf(a, "%c", mar.hasLife + 48);
	outtextxy(15 * 32 + 10, 0, a);

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			if (m.all[x][y] == land1)
			{
				putimage_withalpha(NULL, m.land1, x * 32, y * 32);
			}
			else if (m.all[x][y] == land2)
			{
				putimage_withalpha(NULL, m.land2, x * 32, y * 32);
			}
			else if (m.all[x][y] == land3)
			{
				putimage_withalpha(NULL, m.land3, x * 32, y * 32);
			}
			else if (m.all[x][y] == land4)
			{
				putimage_withalpha(NULL, m.land4, x * 32, y * 32);
			}
		}
	}
	//画马里奥
	putimage_withalpha(NULL, mar.currentImage, mar.x * 32 + mar.offsetX, mar.y * 32 + mar.offsetY);
	//乌龟两个
	for (int i = 0; i < 2; ++i)
	{
		if (!tor[i].isSui)
			putimage_withalpha(NULL, tor[i].currentImage, tor[i].x * 32 + tor[i].offsetX, tor[i].y * 32);
	}
	//板栗四个
	for (int i = 0; i < 4; ++i)
	{
		if (n[i].isDead && n[i].death == 0)
			continue;
		putimage_withalpha(NULL, n[i].currentImage, n[i].x * 32 + n[i].offsetX, n[i].y * 32);
	}
	//食人花俩个
	for (int i = 0; i < 2; ++i)
	{
		putimage_withalpha(NULL, f[i].currentImage, f[i].x * 32, f[i].y * 32);
	}
	//金币五个
	for (int i = 0; i < 5; ++i)
	{
		if (!c[i].isDead)
		{
			putimage_withalpha(NULL, c[i].currentImage, c[i].x * 32, c[i].y * 32);
		}
	}
}

//游戏结束更新数据库的数据
void updateSQL()
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	sprintf(sql, "update user set coin = '%d' where name = '%s';", atoi(row[2]) + mar.getCoin, user_current);
	mysql_query(&mysql, sql);
}