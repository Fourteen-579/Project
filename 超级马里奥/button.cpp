#include"button.h"
button bts[100];
int nn=0;
int last;
button start;
button store;
button ranking;
button explain;
button exitGame;
button music;
button goods1;
button goods2;
button goods3;
button sign_button;
button register_button;
button yes;
button no;

void setBotton()
{
	yes.x = 70;
	yes.y = 300;
	yes.w = 258;
	yes.h = 129;
	yes.onClick = yesKey;
	yes.current = yes_image;

	no.x = 330;
	no.y = 300;
	no.w = 258;
	no.h = 129;
	no.onClick = noKey;
	no.current = no_image;

	sign_button.x = 40;
	sign_button.y = 300;
	sign_button.w = 250;
	sign_button.h = 100;
	sign_button.onClick = sign;
	sign_button.current = user_sign;

	register_button.x = 330;
	register_button.y = 300;
	register_button.w = 250;
	register_button.h = 100;
	register_button.onClick = registers;
	register_button.current = user_register;

	goods1.x = 180;
	goods1.y = 100;
	goods1.w = 268;
	goods1.h = 100;
	goods1.onClick = buy1;
	goods1.current = goods1_image;

	goods2.x = 180;
	goods2.y = 250;
	goods2.w = 268;
	goods2.h = 100;
	goods2.onClick = buy2;
	goods2.current = goods2_image;

	goods3.x = 180;
	goods3.y = 400;
	goods3.w = 268;
	goods3.h = 100;
	goods3.onClick = returnMain;
	goods3.current = goods3_image;

	music.x = 0;
	music.y = 0;
	music.h = 32;
	music.w = 32;
	music.onClick = musicB;
	music.current = openMusic;

	start.x = 160;
	start.y = 185;
	start.w = 320;
	start.h = 80;
	start.onClick = startGame;

	store.x = 160;
	store.y = 265;
	store.w = 320;
	store.h = 80;
	store.onClick = storeGame;

	ranking.x = 160;
	ranking.y = 345;
	ranking.w = 320;
	ranking.h = 80;
	ranking.onClick = rangkGame;

	explain.x = 160;
	explain.y = 425;
	explain.w = 320;
	explain.h = 80;
	explain.onClick = explainGame;

	exitGame.x = 160;
	exitGame.y = 505;
	exitGame.w = 320;
	exitGame.h = 80;
	exitGame.onClick = ExitGame;
}
void addButton(button t)
{
	bts[nn] = t;
	++nn;
}
int deal1(mouse_msg t)
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 2; r < 8; ++r)
	{
		if (key == -1 && x >= bts[r].x && x <= bts[r].x + bts[r].w&&y >= bts[r].y && y <= bts[r].y + bts[r].h)
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
			bkmusic.Stop();
			if (isMusic == 1)
				load1Music.Play();

			int h = bts[key].onClick();//进行游戏
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
			load1Music.Stop();
			if (isMusic == 1)
				bkmusic.Play();
		}
	}
	return 1;
}
int deal2(mouse_msg t)
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 8; r < 11; ++r)
	{
		if (key == -1 && x >= bts[r].x && x <= bts[r].x + bts[r].w&&y >= bts[r].y && y <= bts[r].y + bts[r].h)
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
			bkmusic.Stop();
			if (isMusic == 1)
				load1Music.Play();
			
			int h = bts[key].onClick();//进行游戏
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
			load1Music.Stop();
			if (isMusic == 1)
				bkmusic.Play();
		}
	}
	return 1;
}
int deal3(mouse_msg t)
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 0; r < 3; ++r)
	{
		if (key == -1 && x >= bts[r].x && x <= bts[r].x + bts[r].w&&y >= bts[r].y && y <= bts[r].y + bts[r].h)
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
			bkmusic.Stop();
			if (isMusic == 1)
				load1Music.Play();

			int h = bts[key].onClick();//进行游戏
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
			load1Music.Stop();
			if (isMusic == 1)
				bkmusic.Play();
		}
	}
	return 1;
}
int deal4(mouse_msg t)
{
	int x = t.x;
	int y = t.y;
	int key = -1;
	for (int r = 11; r < 13; ++r)
	{
		if (key == -1 && x >= bts[r].x && x <= bts[r].x + bts[r].w&&y >= bts[r].y && y <= bts[r].y + bts[r].h)
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
			bkmusic.Stop();
			if (isMusic == 1)
				load1Music.Play();

			int h = bts[key].onClick();//进行游戏
			while (mousemsg())
				getmouse();
			if (h == 0)
				return 0;
			load1Music.Stop();
			if (isMusic == 1)
				bkmusic.Play();
		}
	}
	return 1;
}
