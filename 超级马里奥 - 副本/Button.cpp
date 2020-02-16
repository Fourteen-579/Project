#include"User.h"

Button start;
Button store;
Button ranking;
Button explain;
Button exitGame;
Button music;
Button goods1;
Button goods2;
Button goods3;
Button sign_button;
Button register_button;
Button yes;
Button no;

PIMAGE coin;
PIMAGE mainPimage;
PIMAGE closeMusic;
PIMAGE openMusic;
PIMAGE storeMenu;
PIMAGE explain_image;
PIMAGE pur1;
PIMAGE pur2;
PIMAGE linkFail;
PIMAGE ranking_image;
PIMAGE gameover_image;
PIMAGE gamepass_image;
PIMAGE nextPass_image;
PIMAGE useSuccess;
PIMAGE useFailur;
PIMAGE goods1_image;
PIMAGE goods2_image;
PIMAGE goods3_image;
PIMAGE yes_image;
PIMAGE no_image;
PIMAGE user_sign;
PIMAGE user_register;

void getImage()
{

	coin = newimage();
	getimage(coin, "image/硬币0.png");
	//主界面
	mainPimage = newimage();
	getimage(mainPimage, "image/主界面.png");

	storeMenu = newimage();
	getimage(storeMenu, "image/storeMenu.png");

	explain_image = newimage();
	getimage(explain_image, "image/explainGame.png");

	nextPass_image = newimage();
	getimage(nextPass_image, "image/下一关.png");

	useSuccess = newimage();
	getimage(useSuccess, "image/使用成功.png");

	useFailur = newimage();
	getimage(useFailur, "image/使用失败.png");

	gamepass_image = newimage();
	getimage(gamepass_image, "image/游戏通关.png");

	gameover_image = newimage();
	getimage(gameover_image, "image/游戏结束.png");

	ranking_image = newimage();
	getimage(ranking_image, "image/排名背景.png");

	user_sign = newimage();
	getimage(user_sign, "image/登录.png");

	user_register = newimage();
	getimage(user_register, "image/注册.png");

	yes_image = newimage();
	getimage(yes_image, "image/yes.png");

	no_image = newimage();
	getimage(no_image, "image/no.png");
	openMusic = newimage();
	getimage(openMusic, "image/musicOpen.png");
	closeMusic = newimage();
	getimage(closeMusic, "image/musicClose.png");
	goods1_image = newimage();
	getimage(goods1_image, "image/商品1.png");
	goods2_image = newimage();
	getimage(goods2_image, "image/商品2.png");
	goods3_image = newimage();
	getimage(goods3_image, "image/商品3.png");

	//主界面按钮图片
	exitGame.current = newimage();
	getimage(exitGame.current, "image/exit.png");

	start.current = newimage();
	getimage(start.current, "image/start.png");

	store.current = newimage();
	getimage(store.current, "image/store.png");

	ranking.current = newimage();
	getimage(ranking.current, "image/ranking.png");

	explain.current = newimage();
	getimage(explain.current, "image/explain.png");

	linkFail = newimage();
	getimage(linkFail, "image/连接失败.png");

	pur1 = newimage();
	getimage(pur1, "image/购买成功.png");

	pur2 = newimage();
	getimage(pur2, "image/购买失败.png");
}

void setButton()
{
	yes.x = 70;
	yes.y = 300;
	yes.w = 258;
	yes.h = 129;
	yes.onClick = &User::yesKey;
	yes.current = yes_image;

	no.x = 330;
	no.y = 300;
	no.w = 258;
	no.h = 129;
	no.onClick = &User::noKey;
	no.current = no_image;

	sign_button.x = 40;
	sign_button.y = 300;
	sign_button.w = 250;
	sign_button.h = 100;
	sign_button.onClick = &User::sign;
	sign_button.current = user_sign;

	register_button.x = 330;
	register_button.y = 300;
	register_button.w = 250;
	register_button.h = 100;
	register_button.onClick = &User::registers;
	register_button.current = user_register;

	goods1.x = 180;
	goods1.y = 100;
	goods1.w = 268;
	goods1.h = 100;
	goods1.onClick = &User::buy1;
	goods1.current = goods1_image;

	goods2.x = 180;
	goods2.y = 250;
	goods2.w = 268;
	goods2.h = 100;
	goods2.onClick = &User::buy2;
	goods2.current = goods2_image;

	goods3.x = 180;
	goods3.y = 400;
	goods3.w = 268;
	goods3.h = 100;
	goods3.onClick = &User::returnMain;
	goods3.current = goods3_image;

	music.x = 0;
	music.y = 0;
	music.h = 32;
	music.w = 32;
	music.onClick = NULL;
	music.current = closeMusic;

	start.x = 160;
	start.y = 185;
	start.w = 320;
	start.h = 80;
	start.onClick = &User::startGame;

	store.x = 160;
	store.y = 265;
	store.w = 320;
	store.h = 80;
	store.onClick = &User::storeGame;

	ranking.x = 160;
	ranking.y = 345;
	ranking.w = 320;
	ranking.h = 80;
	ranking.onClick = &User::rangkGame;

	explain.x = 160;
	explain.y = 425;
	explain.w = 320;
	explain.h = 80;
	explain.onClick = &User::explainGame;

	exitGame.x = 160;
	exitGame.y = 505;
	exitGame.w = 320;
	exitGame.h = 80;
	exitGame.onClick = &User::ExitGame;
}

int deal1(mouse_msg t,User u)//游戏主界面
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 2; r < 8; ++r)
	{
		if (x >= u.bts[r].x && x <= u.bts[r].x + u.bts[r].w&&y >= u.bts[r].y && y <= u.bts[r].y + u.bts[r].h)
		{
			key = r;
		}
	}
	if (key == -1)
	{
		last = -1;
		return 1;
	}
	if (t.is_down() && t.is_left())
	{
		last = key;
	}
	if (t.is_up() && t.is_left())
	{
		if (last == key)
		{
			int h = (u.*(u.bts[key].onClick))();
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
		}
	}
	return 1;
}
int deal2(mouse_msg t,User u)//游戏商店
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 8; r < 11; ++r)
	{
		if (x >= u.bts[r].x && (x <= (u.bts[r].x + u.bts[r].w))&&y >= u.bts[r].y && (y <= (u.bts[r].y + u.bts[r].h)))
		{
			key = r;
		}
	}
	if (key == -1)
	{
		last = -1;
		return 1;
	}

	if (t.is_down() && t.is_left())
	{
		last = key;
	}

	if (t.is_left())
	{
		if (last == key)
		{
			int h = (u.*(u.bts[key].onClick))();
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
		}
	}
	return 1;
}
int deal3(mouse_msg t,User u)
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 0; r < 3; ++r)
	{
		if (x >= u.bts[r].x && x <= u.bts[r].x + u.bts[r].w&&y >= u.bts[r].y && y <= u.bts[r].y + u.bts[r].h)
		{
			key = r;
			break;
		}
	}
	if (key == -1)
	{
		last = -1;
		return 1;
	}

	if (t.is_down() && t.is_left())
	{
		last = key;
	}

	if (t.is_left())
	{
		if (last == key)
		{
			int h = (u.*(u.bts[key].onClick))();
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
		}
	}
	
	return 1;
}
int deal4(mouse_msg t,User u)
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 11; r < 13; ++r)
	{
		if (x >= u.bts[r].x && x <= u.bts[r].x + u.bts[r].w&&y >= u.bts[r].y && y <= u.bts[r].y + u.bts[r].h)
		{
			key = r;
		}
	}
	if (key == -1)
	{
		last = -1;
		return 1;
	}

	if (t.is_down() && t.is_left())
	{
		last = key;
	}
	if (t.is_left())
	{
		if (last == key)
		{
			int h = (u.*(u.bts[key].onClick))();
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
		}
	}
	return 1;
}
