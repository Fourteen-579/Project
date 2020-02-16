#include"main.h"

int pass_num;

//是否使用金钥匙
void useKey()
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
			int h = deal4(t);
			if (h == 0)
				break;
		}
		delay_fps(240);
	}
	return;
}
//退出游戏
int ExitGame()
{
	//退出游戏界面
	return 0;
}
//开始游戏
int startGame()	//选关  
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	mar.hasLife = 1 + atoi(row[3]);
	pass_num = 1;
	while (mar.hasLife > 0)
	{
		updateGame();
		if (pass_num == 1)
			load1();
		else if (pass_num == 2)
			load2();
		else if (pass_num == 3)
			load3();
		else
		{
			putimage(0, 0, gamepass_image);
			getch();
			break;
		}
		while (!mar.isDead || mar.death != 0)
		{
			input();
			update();
			render();
			delay_fps(60);
			if (mar.getDeath == 6)
			{
				++pass_num;
				if (pass_num <= 3)
				{
					useKey();
				}
				break;
			}
		}
		updateSQL();
		cleardevice();
	}
	return 1;
}
//游戏商店
int storeGame()
{
	while (true)
	{
		putimage(0, 0, storeMenu);
		putimage_withalpha(NULL, c[0].currentImage, 17*32, 0);
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
			int h = deal2(t);
			if (h == 0)
				break;
		}
		for (int i = 8; i < 11; ++i)
		{
			putimage_withalpha(NULL, bts[i].current, bts[i].x, bts[i].y);
		}
		delay_fps(240);
	}
	return 1;
}
//游戏说明
int explainGame()
{
	putimage(0, 0, explain_image);
	getch();
	return 1;
}
//游戏商店返回
int returnMain()
{
	return 0;
}
//购买游戏商品1
int buy1()
{	
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (atoi(row[2]) >= 10)
	{
		putimage(160, 160, pur1);
		sprintf(sql, "update user set coin = '%d',mushroom_num='%d' where name = '%s';",atoi(row[2])-10,atoi(row[3])+1, user_current);
		mysql_query(&mysql, sql);
		putimage(160, 160, pur1);
	}
	else
	{
		putimage(160, 160, pur2);
	}
	getch();
	return 1;
}
//购买游戏商品2
int buy2()
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (atoi(row[2]) >= 20)
	{
		putimage(160, 160, pur1);
		char sql[1024];
		sprintf(sql, "update user set coin = '%d', key_num='%d' where name = '%s';", atoi(row[2]) - 20, atoi(row[4]) + 1, user_current);
		mysql_query(&mysql, sql);
		putimage(160, 160, pur1);
	}
	else
	{
		putimage(160, 160, pur2);
	}
	getch();
	return 1;
}
//游戏排名5
int rangkGame()
{
	cleardevice();
	putimage(0, 0, ranking_image);

	setcolor(WHITE);
	setbkmode(TRANSPARENT);			//设置文字背景色为透明(默认为有背景色)

	setfont(35,0 , "幼圆");
	mysql_query(&mysql, "select * from user order by coin desc;");
	mysql_query(&mysql, "select * from user ;");
	res = mysql_store_result(&mysql);
	int i = 0;
	while ((row = mysql_fetch_row(res)) != NULL)
	{
		char a[100];
		sprintf(a, "%s", row[0]);
		outtextxy(70, 150 + i * 70, a);
		sprintf(a, "%s", row[2]);
		outtextxy(350, 150 + i * 70, a);
		++i;
	}
	getch();
	return 1;
}
//使用金钥匙
int yesKey()
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	if (atoi(row[4]) > 0)
	{
		++pass_num;
		sprintf(sql, "update user set key_num = '%d' where name = '%s';", atoi(row[4]) - 1, user_current);
		mysql_query(&mysql, sql);
		putimage(160, 160, useSuccess);
	}
	else
	{
		putimage(160, 160, useFailur);
	}
	getch();
	return 0;
}
//不使用金钥匙
int noKey()
{
	//getch();
	return 0;
}
//游戏主界面
void gameMain()
{
	while (true)
	{
		if (mousemsg())
		{
			mouse_msg t = getmouse();
			int h = deal1(t);
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
//游戏数据
void ini()
{
	bkmusic.OpenFile("I:\\VS\\_project\\超级马里奥\\超级马里奥\\music\\123.mp3"); // 打开音乐文件
	load1Music.OpenFile("I:\\VS\\_project\\超级马里奥\\超级马里奥\\music\\456.mp3");
	bkmusic.Play();
	
	initgraph(640, 640);
	setcaption("Fourteen_579");
	getImage();
	setBotton();
	
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
void gameOver()
{
	putimage(0, 0, gameover_image);
	Sleep(1000);
	return;
}
//用户界面
void userMain()
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
			int h = deal3(t);
			if (h == 0)
				break;
		}
		for (int i = 0; i < 3; ++i)
		{
			putimage(bts[i].x, bts[i].y, bts[i].current);
		}
		delay_fps(240);
	}
}

int main()
{
	ini();
	userMain();
	initgraph(640, 640);
	setcaption("Fourteen_579");
	gameMain();
	gameOver();
	return 0;
}