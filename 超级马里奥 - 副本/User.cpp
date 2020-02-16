#include"User.h"

MapsType all[20][20];


void User::getStr(const char *title, char *buffer, int len)
{
	while (true)
	{
		inputbox_getline(NULL, title, buffer, len);
		if (strlen(buffer) != 0)
		{
			break;
		}
	}
}

//用户登录
int User::sign()
{
	initgraph(350, 230);
	setcaption("Fourteen_579");
	char user[129];
	char psw[129];

	while (true)
	{
		getStr("请输入用户名", user, sizeof(user) - 1);
		getStr("请输入密码", psw, sizeof(psw) - 1);

		char sql[1024];
		sprintf(sql, "select * from user where name = '%s';", user);
		mysql_query(&mysql, sql);
		MYSQL_RES *re = mysql_store_result(&mysql);
		MYSQL_ROW row = mysql_fetch_row(re);
		if (row == NULL)
		{
			MessageBoxA(NULL, "未注册的用户", "错误", MB_OK);
		}
		else
		{
			if (strcmp(row[1], psw) == 0)
			{
				strcpy(user_current, user);
				beginSQL();
				gameMain();
				break;
			}
			else
			{
				MessageBoxA(NULL, "密码错误", "错误", MB_OK);
			}
		}
	}
	return 0;
}

//用户注册
int User::registers()
{
	initgraph(350, 230);
	setcaption("Fourteen_579");
	char user[129];
	char psw[129];
	char pswRe[129];

	while (true)
	{
		getStr("请输入用户名", user, sizeof(user) - 1);
		getStr("请输入密码", psw, sizeof(psw) - 1);
		getStr("请确认密码", pswRe, sizeof(pswRe) - 1);

		if (strcmp(psw, pswRe) != 0)
		{
			MessageBoxA(NULL, "两次输入的密码不一致", "错误", MB_OK);
			continue;
		}

		char sql[1024];
		sprintf(sql, "select * from user where name = '%s';", user);
		mysql_query(&mysql, sql);
		MYSQL_RES *res = mysql_store_result(&mysql);
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL)
		{
			MessageBoxA(NULL, "该账号已注册", "错误", MB_OK);
		}
		else
		{
			sprintf(sql, "insert into user values('%s','%s','0','0','0');", user, psw);
			mysql_query(&mysql, sql);
			strcpy(user_current, user);
			beginSQL();
			gameMain();
			break;
		}
	}
	return 0;
}

//用户界面
void User::userMain()
{
	mysql_init(&mysql);
	const char *psw = "2000107ksz";
	if (!mysql_real_connect(&mysql, "localhost", "root", psw, "game", 0, NULL, 0))
	{
		putimage(0, 0, linkFail);
		return;
	}
	putimage(0, 0, mainPimage);
	while (true)
	{
		if (mousemsg())
		{
			mouse_msg t = getmouse();
			if (t.is_down())
			{
				int h = deal3(t, *this);
				if (h == 0)
					break;
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			putimage(bts[i].x, bts[i].y, bts[i].current);
		}
		delay_fps(240);
	}
}

//游戏结束更新数据库的数据
void User::updateSQL()
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	sprintf(sql, "update user set coin = '%d',mushroom_num = '%d',key_num = '%d' where name = '%s';", hasCold, hasNut,hasKey,user_current);
	mysql_query(&mysql, sql);
}

//开始游戏获取游戏数据
void User::beginSQL()
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	hasCold = atoi(row[2]);
	hasNut = atoi(row[3]);
	hasKey = atoi(row[4]);
}

//游戏主界面
void User::gameMain()
{
	initgraph(640, 640);
	setcaption("Fourteen_579");
	while (true)
	{
		if (mousemsg())
		{
			mouse_msg t = getmouse();
			int h = deal1(t,*this);
			if (h == 0)
				break;
		}
		putimage(0, 0, mainPimage);
		for (int i = 2; i < 8; ++i)
		{
			putimage(bts[i].x, bts[i].y, bts[i].current);
		}
		delay_fps(240);
	}
	return;
}

void User::getImage()
{

	gameover_image = newimage();
	getimage(gameover_image, "image/游戏结束.png");

	ranking_image = newimage();
	getimage(ranking_image, "image/排名背景.png");

	linkFail = newimage();
	getimage(linkFail, "image/连接失败.png");

	pur1 = newimage();
	getimage(pur1, "image/购买成功.png");
	pur2 = newimage();
	getimage(pur2, "image/购买失败.png");

	mainPimage = newimage();
	getimage(mainPimage, "image/主界面.png");

	storeMenu = newimage();
	getimage(storeMenu, "image/storeMenu.png");

	explain_image = newimage();
	getimage(explain_image, "image/explainGame.png");
}

void User::addButton(Button t)
{
	bts[nn] = t;
	nn+=1;
}

//是否使用金钥匙
void User::useKey(Button b)
{
	putimage(0, 0, nextPass_image);
	for (int i = 11; i < 13; ++i)
	{
		putimage_withalpha(NULL, bts[i].current, bts[i].x, bts[i].y);
	}
	while (true)
	{
		if (mousemsg())
		{
			mouse_msg t = getmouse();
			int h = deal4(t, *this);
			if (h == 0)
				break;
		}
		delay_fps(240);
	}
	return;
}

//退出游戏
int User::ExitGame()
{
	//退出游戏界面
	putimage(0, 0, gameover_image);
	Sleep(1000);
	return 0;
}

//游戏说明
int User::explainGame()
{
	putimage(0, 0, explain_image);
	getch();
	return 1;
}

//游戏商店返回
int User::returnMain()
{
	return 0;
}

//不使用金钥匙
int User::noKey()
{
	//getch();
	return 0;
}

//游戏数据
void User::ini(Button b)
{
	initgraph(640, 640);
	setcaption("Fourteen_579");

	setButton();

	addButton(sign_button);
	addButton(register_button);
	addButton(music);
	addButton(start);
	addButton(store);
	addButton(ranking);
	addButton(explain);
	addButton(exitGame);
	addButton(goods1);
	addButton(goods2);
	addButton(goods3);
	addButton(yes);
	addButton(no);

}

//游戏结束
void User::gameOver()
{
	putimage(0, 0, gameover_image);
	Sleep(1000);
	return;
}

//游戏商店
int User::storeGame()
{
	while (true)
	{
		putimage(0, 0,storeMenu);
		putimage_withalpha(NULL,coin , 17 * 32, 0);
		setcolor(BLACK);
		setbkmode(TRANSPARENT);			//设置文字背景色为透明(默认为有背景色)
		setfont(32, 0, "幼圆");
		char sql[1024];
		sprintf(sql, "select * from user where name = '%s';", user_current);
		mysql_query(&mysql, sql);
		res = mysql_store_result(&mysql);
		row = mysql_fetch_row(res);
		char a[10];
		sprintf(a, " *%s", row[2]);
		outtextxy(18 * 32, 0, a);
		if (mousemsg())
		{
			mouse_msg t = getmouse();
			if (t.is_down())
			{
				int h = deal2(t, *this);
				if (h == 0)
					break;
			}
		}
		for (int i = 8; i < 11; ++i)
		{
			putimage_withalpha(NULL, bts[i].current, bts[i].x, bts[i].y);
		}
		delay_fps(240);
	}
	return 1;
}

//购买游戏商品1
int User::buy1()
{
	if (hasCold >= 10)
	{
		putimage(160, 160, pur1);
		hasCold -= 10;
		hasNut += 1;
	}
	else
	{
		putimage(160, 160, pur2);
	}
	getch();
	return 1;
}

//购买游戏商品2
int User::buy2()
{
	if (hasCold >= 20)
	{
		putimage(160, 160, pur1);
		hasCold -= 20;
		hasKey += 1;
	}
	else
	{
		putimage(160, 160, pur2);
	}
	getch();
	return 1;
}

//游戏排名
int User::rangkGame()
{
	cleardevice();
	putimage(0, 0, ranking_image);

	setcolor(WHITE);
	setbkmode(TRANSPARENT);			//设置文字背景色为透明(默认为有背景色)

	setfont(35, 0, "幼圆");
	mysql_query(&mysql, "select * from user order by coin desc;");
	mysql_query(&mysql, "select * from user ;");
	res = mysql_store_result(&mysql);
	int num = 0;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		char a[100];
		sprintf(a, "%s", row[0]);
		outtextxy(70, 150 + num * 70, a);
		sprintf(a, "%s", row[2]);
		outtextxy(350, 150 + num * 70, a);
		++num;
	}
	getch();
	return 1;
}

//使用金钥匙
int User::yesKey()
{
	if (hasKey > 0)
	{
		//Game::pass_num+=1;
		hasKey -= 1;
		putimage(160, 160, useSuccess);
	}
	else
	{
		putimage(160, 160, useFailur);
	}
	getch();
	return 0;
}

//开始游戏
int User::startGame()	//选关  
{
	g.mar.hasLife = 1 + hasNut;
	g.pass_num = 1;
	while (g.mar.hasLife > 0)
	{
		g.updateGame();
		if (g.pass_num == 1)
		{
			g.set1();
		}
		else if (g.pass_num == 2)
		{
			g.set2();
		}
		else if (g.pass_num == 3)
		{
			g.set3();
		}
		else
		{
			putimage(0, 0, gamepass_image);
			getch();
			break;
		}
		while (!g.mar.isDead || g.mar.death != 0)
		{
			key = -1;
			if (kbhit())
			{
				g.input();
			}

			g.mar.update(g.c, g.tor, g.n, g.f);

			//更新自动的板栗
			for(int i=0;i<4;++i)
			g.n[i].updateNut();
			//更新自动的乌龟
			for(int i=0;i<2;++i)
			g.tor[i].updateTor();
			//更新食人花
			for(int i=0;i<2;++i)
			g.f[i].updateFlo();

			g.render();
			delay_fps(60);
			if (g.mar.getDeath == 6)
			{
				break;
			}
		}
		updateSQL();
		cleardevice();
	}
	return 1;
}