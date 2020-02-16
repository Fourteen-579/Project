#include"User.h"
int key;
int Game::pass_num = 1;

//获取输入
void Game::input()
{
	char a = getch();
	if(a=='j'||a=='J')
		key = 'j';
	else if(a=='d'||a=='D')
		key = 'd';
	else if(a=='a'||a=='A')
		key = 'a';
}

//更新游戏数据
void Game::updateGame()
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

//输出图片
void Game::render()
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

	for (int xx = 0; xx < 20; ++xx)
	{
		for (int yy = 0; yy < 20; ++yy)
		{
			if (all[xx][yy] == land1)
			{
				putimage_withalpha(NULL, land1_image, xx * 32, yy * 32);
			}
			else if (all[xx][yy] == land2)
			{
				putimage_withalpha(NULL, land2_image, xx * 32, yy * 32);
			}
			else if (all[xx][yy] == land3)
			{
				putimage_withalpha(NULL, land3_image, xx * 32, yy * 32);
			}
			else if (all[xx][yy] == land4)
			{
				putimage_withalpha(NULL, land4_image, xx * 32, yy * 32);
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

void Game::set1()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			all[i][j] = null;
		}
	}
	//更新乌龟
	tor[0].x = 12;
	tor[0].y = 14;
	tor[0].leftLimit = 12;
	tor[0].rightLimit = 17;
	tor[1].x = 0;
	tor[1].y = 5;
	tor[1].leftLimit = 0;
	tor[1].rightLimit = 3;

	//金币位置
	c[0].x = 9;
	c[0].y = 16;

	c[1].x = 0;
	c[1].y = 13;

	c[2].x = 17;
	c[2].y = 7;

	c[3].x = 0;
	c[3].y = 4;

	c[4].x = 19;
	c[4].y = 1;



	//食人花更新
	f[0].x = 11;
	f[0].y = 14;

	f[1].x = 4;
	f[1].y = 5;

	//板栗更新
	n[0].x = 17;
	n[0].y = 18;
	n[0].leftLimit = 0;
	n[0].rightLimit = 17;

	n[1].x = 2;
	n[1].y = 14;
	n[1].leftLimit = 0;
	n[1].rightLimit = 3;

	n[2].x = 11;
	n[2].y = 8;
	n[2].leftLimit = 11;
	n[2].rightLimit = 17;

	n[3].x = 18;
	n[3].y = 2;
	n[3].leftLimit = 7;
	n[3].rightLimit = 19;

	//马里奥更新
	mar.x = 0;
	mar.y = 18;
	all[0][18] = mario;
	//地图更新


	all[0][19] = land1;
	for (int i = 1; i < 19; ++i)
		all[i][19] = land2;
	all[19][19] = land3;

	for (int i = 0; i < 17; ++i)
		all[i][15] = land2;
	all[17][15] = land3;

	all[19][18] = land4;
	all[19][17] = land4;
	all[18][18] = land4;

	for (int i = 4; i < 7; ++i)
	{
		all[i][14] = land4;
	}
	all[5][13] = land4;
	all[4][13] = land4;

	for (int i = 0; i < 2; ++i)
		all[i][12] = land2;
	all[2][12] = land3;
	all[1][11] = land4;

	all[3][9] = land1;
	for (int i = 4; i < 9; ++i)
		all[i][9] = land2;
	all[9][9] = land3;

	all[11][9] = land1;
	for (int i = 12; i < 17; ++i)
		all[i][9] = land2;
	all[17][9] = land3;

	all[7][3] = land1;
	for (int i = 8; i <= 19; ++i)
		all[i][3] = land2;
	all[6][4] = land4;

	for (int i = 0; i < 6; ++i)
		all[i][6] = land2;
	all[6][6] = land3;
	all[7][7] = land4;
}
void Game::set2()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			all[i][j] = null;
		}
	}
	//更新乌龟
	tor[0].x = 7;
	tor[0].y = 9;
	tor[0].leftLimit = 7;
	tor[0].rightLimit = 19;
	tor[1].x = 19;
	tor[1].y = 18;
	tor[1].leftLimit = 14;
	tor[1].rightLimit = 19;

	//金币位置
	c[0].x = 10;
	c[0].y = 3;

	c[1].x = 19;
	c[1].y = 5;

	c[2].x = 19;
	c[2].y = 8;

	c[3].x = 0;
	c[3].y = 15;

	c[4].x = 19;
	c[4].y = 15;


	//马里奥更新
	mar.x = 0;
	mar.y = 1;
	all[0][1] = mario;

	//食人花更新
	f[0].x = 0;
	f[0].y = 18;

	f[1].x = 4;
	f[1].y = 3;

	//板栗更新
	n[0].x = 17;
	n[0].y = 6;
	n[0].leftLimit = 17;
	n[0].rightLimit = 19;

	n[1].x = 0;
	n[1].y = 7;
	n[1].leftLimit = 0;
	n[1].rightLimit = 3;

	n[2].x = 0;
	n[2].y = 13;
	n[2].leftLimit = 0;
	n[2].rightLimit = 3;

	n[3].x = 17;
	n[3].y = 13;
	n[3].leftLimit = 14;
	n[3].rightLimit = 17;

	//地图更新
	for (int i = 0; i < 2; ++i)
		all[i][2] = land2;
	all[2][2] = land3;
	for (int i = 4; i <= 16; i += 3)
		all[i][4] = land4;
	for (int i = 0; i < 3; ++i)
		all[i][8] = land2;
	all[3][8] = land3;
	all[4][9] = land4;
	for (int i = 0; i < 3; ++i)
		all[i][14] = land2;
	all[3][14] = land3;
	all[4][15] = land4;
	all[5][16] = land4;
	all[17][7] = land1;
	for (int i = 18; i <= 19; ++i)
		all[i][7] = land2;
	all[7][10] = land1;
	for (int i = 8; i <= 19; ++i)
		all[i][10] = land2;
	all[7][14] = land1;
	for (int i = 8; i <= 9; ++i)
		all[i][14] = land2;
	all[10][14] = land3;
	all[14][14] = land1;
	for (int i = 15; i < 17; ++i)
		all[i][14] = land2;
	all[17][14] = land3;
	all[0][19] = land1;
	for (int i = 1; i < 19; ++i)
		all[i][19] = land2;
	all[19][19] = land3;
	for (int i = 11; i <= 13; ++i)
		all[i][18] = land4;
	for (int i = 11; i <= 13; ++i)
		all[i][17] = land4;
	for (int i = 11; i <= 12; ++i)
		all[i][16] = land4;
	all[11][15] = land4;
}
void Game::set3()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			all[i][j] = null;
		}
	}
	//更新乌龟
	tor[0].x = 16;
	tor[0].y = 7;
	tor[0].leftLimit = 15;
	tor[0].rightLimit = 18;
	tor[1].x = 11;
	tor[1].y = 18;
	tor[1].leftLimit = 11;
	tor[1].rightLimit = 18;

	//金币位置
	c[0].x = 3;
	c[0].y = 14;
	
	c[1].x = 19;
	c[1].y = 18;

	c[2].x = 1;
	c[2].y = 7;

	c[3].x = 11;
	c[3].y = 4;

	c[4].x = 0;
	c[4].y = 1;

	//马里奥更新
	mar.x = 0;
	mar.y = 18;
	all[0][18] = mario;

	//食人花更新
	f[0].x = 7;
	f[0].y = 3;

	f[1].x = 1;
	f[1].y = 11;

	//板栗更新
	n[0].x = 3;
	n[0].y = 18;
	n[0].leftLimit = 0;
	n[0].rightLimit = 3;

	n[1].x = 0;
	n[1].y = 2;
	n[1].leftLimit = 0;
	n[1].rightLimit = 6;

	n[2].x = 9;
	n[2].y = 2;
	n[2].leftLimit = 9;
	n[2].rightLimit = 15;

	n[3].x = 4;
	n[3].y = 7;
	n[3].leftLimit = 2;
	n[3].rightLimit = 4;

	//地图更新
	for (int i = 0; i < 3; ++i)
		all[i][19] = land2;
	all[3][19] = land3;
	all[11][19] = land1;
	for (int i = 12; i <= 19; ++i)
		all[i][19] = land2;
	for (int i = 5; i <= 17; i += 3)
		all[i][17] = land4;
	all[18][17] = land4;
	all[19][17] = land4;
	all[18][16] = land4;
	all[19][16] = land4;
	all[19][15] = land4;
	all[19][14] = land4;
	all[16][13] = land4;
	for (int i = 5; i <= 14; i += 3)
		all[i][13] = land4;
	for (int i = 0; i < 3; ++i)
		all[i][13] = land2;
	all[3][13] = land3;
	for (int i = 0; i < 3; ++i)
		all[i][12] = land4;
	all[0][11] = land4;
	all[0][10] = land4;
	all[2][8] = land4;
	for (int i = 3; i <= 11; i += 4)
	{
		all[i][8] = land4;
		all[i + 1][8] = land4;
	}
	all[15][8] = land1;
	for (int i = 16; i <= 19; ++i)
		all[i][8] = land2;
	for (int i = 7; i >= 5; --i)
		all[19][i] = land4;
	all[17][3] = land4;
all[18][3] = land4;
	all[7][4] = land4;
	all[8][4] = land4;
	all[9][3] = land1;
	for (int i = 10; i < 15; ++i)
		all[i][3] = land2;
	all[15][3] = land3;
	all[6][3] = land3;
	for (int i = 0; i < 6; ++i)
		all[i][3] = land2;
}

void Game::getImage()
{
	img = newimage();
	getimage(img, "image/111.png");

	nums = newimage();
	getimage(nums, "image/life.png");
	//获取乌龟图片
	for (int i = 0; i < 2; ++i)
	{
		tor[i].left = newimage();
		tor[i].leftMove = newimage();
		tor[i].right = newimage();
		tor[i].rightMove = newimage();
		tor[i].torDead = newimage();
		getimage(tor[i].left, "image/乌龟1f.png");
		getimage(tor[i].leftMove, "image/乌龟2f.png");
		getimage(tor[i].right, "image/乌龟1.png");
		getimage(tor[i].rightMove, "image/乌龟2.png");
		getimage(tor[i].torDead, "image/乌龟3.png");
		tor[i].currentImage = tor[i].left;
	}
	//获取硬币图片
	for (int i = 0; i < 5; ++i)
	{
		c[i].currentImage = newimage();
		getimage(c[i].currentImage, "image/硬币0.png");
	}
	//获取马里奥图片
	mar.dead = newimage();
	mar.left = newimage();
	mar.leftMove = newimage();
	mar.leftJump = newimage();
	mar.right = newimage();
	mar.rightMove = newimage();
	mar.rightJump = newimage();
	getimage(mar.dead, "image/dead.png");
	getimage(mar.left, "image/left.png");
	getimage(mar.leftMove, "image/leftMove.png");
	getimage(mar.leftJump, "image/leftJump.png");
	getimage(mar.right, "image/right.png");
	getimage(mar.rightMove, "image/rightMove.png");
	getimage(mar.rightJump, "image/rightJump.png");
	mar.currentImage = mar.right;
	//获取食人花图片
	for (int i = 0; i < 2; ++i)
	{
		all[f[i].x][f[i].y] = flower;
		f[i].close = newimage();
		f[i].open = newimage();
		getimage(f[i].open, "image/食人花2.png");
		getimage(f[i].close, "image/食人花1.png");
		f[i].currentImage = f[i].open;
	}
	//获取板栗图片
	for (int i = 0; i < 4; ++i)
	{
		all[n[i].x][n[i].y] = nut;
		n[i].nutLeft = newimage();
		n[i].nutRight = newimage();
		n[i].nutDead = newimage();
		getimage(n[i].nutLeft, "image/nutLeft.png");
		getimage(n[i].nutRight, "image/nutRight.png");
		getimage(n[i].nutDead, "image/nutDead.png");
		n[i].currentImage = n[i].nutRight;
	}
	//获取砖块图片
	land1_image = newimage();
	land2_image = newimage();
	land3_image = newimage();
	land4_image = newimage();
	getimage(land1_image, "image/land1.png");
	getimage(land2_image, "image/land2.png");
	getimage(land3_image, "image/land3.png");
	getimage(land4_image, "image/land4.png");
}