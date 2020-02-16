#include"load.h"

//地图1
void load1()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			m.all[i][j] = null;
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

	//马里奥更新
	mar.x = 0;
	mar.y = 18;
	m.all[0][18] = mario;

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

	//地图更新


	m.all[0][19] = land1;
	for (int i = 1; i < 19; ++i)
		m.all[i][19] = land2;
	m.all[19][19] = land3;

	for (int i = 0; i < 17; ++i)
		m.all[i][15] = land2;
	m.all[17][15] = land3;

	m.all[19][18] = land4;
	m.all[19][17] = land4;
	m.all[18][18] = land4;

	for (int i = 4; i < 7; ++i)
	{
		m.all[i][14] = land4;
	}
	m.all[5][13] = land4;
	m.all[4][13] = land4;

	for (int i = 0; i < 2; ++i)
		m.all[i][12] = land2;
	m.all[2][12] = land3;
	m.all[1][11] = land4;

	m.all[3][9] = land1;
	for (int i = 4; i < 9; ++i)
		m.all[i][9] = land2;
	m.all[9][9] = land3;

	m.all[11][9] = land1;
	for (int i = 12; i < 17; ++i)
		m.all[i][9] = land2;
	m.all[17][9] = land3;

	m.all[7][3] = land1;
	for (int i = 8; i <= 19; ++i)
		m.all[i][3] = land2;
	m.all[6][4] = land4;

	for (int i = 0; i < 6; ++i)
		m.all[i][6] = land2;
	m.all[6][6] = land3;
	m.all[7][7] = land4;
}
//地图2
void load2()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			m.all[i][j] = null;
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
	m.all[0][1] = mario;

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
		m.all[i][2] = land2;
	m.all[2][2] = land3;
	for (int i = 4; i <= 16; i += 3)
		m.all[i][4] = land4;
	for (int i = 0; i < 3; ++i)
		m.all[i][8] = land2;
	m.all[3][8] = land3;
	m.all[4][9] = land4;
	for (int i = 0; i < 3; ++i)
		m.all[i][14] = land2;
	m.all[3][14] = land3;
	m.all[4][15] = land4;
	m.all[5][16] = land4;
	m.all[17][7] = land1;
	for (int i = 18; i <= 19; ++i)
		m.all[i][7] = land2;
	m.all[7][10] = land1;
	for (int i = 8; i <= 19; ++i)
		m.all[i][10] = land2;
	m.all[7][14] = land1;
	for (int i = 8; i <= 9; ++i)
		m.all[i][14] = land2;
	m.all[10][14] = land3;
	m.all[14][14] = land1;
	for (int i = 15; i < 17; ++i)
		m.all[i][14] = land2;
	m.all[17][14] = land3;
	m.all[0][19] = land1;
	for (int i = 1; i < 19; ++i)
		m.all[i][19] = land2;
	m.all[19][19] = land3;
	for (int i = 11; i <= 13; ++i)
		m.all[i][18] = land4;
	for (int i = 11; i <= 13; ++i)
		m.all[i][17] = land4;
	for (int i = 11; i <= 12; ++i)
		m.all[i][16] = land4;
	m.all[11][15] = land4;

}
//地图3
void load3()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			m.all[i][j] = null;
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
	m.all[0][18] = mario;

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
		m.all[i][19] = land2;
	m.all[3][19] = land3;
	m.all[11][19] = land1;
	for (int i = 12; i <= 19; ++i)
		m.all[i][19] = land2;
	for (int i = 5; i <= 17; i += 3)
		m.all[i][17] = land4;
	m.all[18][17] = land4;
	m.all[19][17] = land4;
	m.all[18][16] = land4;
	m.all[19][16] = land4;
	m.all[19][15] = land4;
	m.all[19][14] = land4;
	m.all[16][13] = land4;
	for (int i = 5; i <= 14; i += 3)
		m.all[i][13] = land4;
	for (int i = 0; i < 3; ++i)
		m.all[i][13] = land2;
	m.all[3][13] = land3;
	for (int i = 0; i < 3; ++i)
		m.all[i][12] = land4;
	m.all[0][11] = land4;
	m.all[0][10] = land4;
	m.all[2][8] = land4;
	for (int i = 3; i <= 11; i += 4)
	{
		m.all[i][8] = land4;
		m.all[i + 1][8] = land4;
	}
	m.all[15][8] = land1;
	for (int i = 16; i <= 19; ++i)
		m.all[i][8] = land2;
	for (int i = 7; i >= 5; --i)
		m.all[19][i] = land4;
	m.all[17][3] = land4;
	m.all[18][3] = land4;
	m.all[7][4] = land4;
	m.all[8][4] = land4;
	m.all[9][3] = land1;
	for (int i = 10; i < 15; ++i)
		m.all[i][3] = land2;
	m.all[15][3] = land3;
	m.all[6][3] = land3;
	for (int i = 0; i < 6; ++i)
		m.all[i][3] = land2;
}
