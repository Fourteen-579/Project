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

//�û���¼
int User::sign()
{
	initgraph(350, 230);
	setcaption("Fourteen_579");
	char user[129];
	char psw[129];

	while (true)
	{
		getStr("�������û���", user, sizeof(user) - 1);
		getStr("����������", psw, sizeof(psw) - 1);

		char sql[1024];
		sprintf(sql, "select * from user where name = '%s';", user);
		mysql_query(&mysql, sql);
		MYSQL_RES *re = mysql_store_result(&mysql);
		MYSQL_ROW row = mysql_fetch_row(re);
		if (row == NULL)
		{
			MessageBoxA(NULL, "δע����û�", "����", MB_OK);
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
				MessageBoxA(NULL, "�������", "����", MB_OK);
			}
		}
	}
	return 0;
}

//�û�ע��
int User::registers()
{
	initgraph(350, 230);
	setcaption("Fourteen_579");
	char user[129];
	char psw[129];
	char pswRe[129];

	while (true)
	{
		getStr("�������û���", user, sizeof(user) - 1);
		getStr("����������", psw, sizeof(psw) - 1);
		getStr("��ȷ������", pswRe, sizeof(pswRe) - 1);

		if (strcmp(psw, pswRe) != 0)
		{
			MessageBoxA(NULL, "������������벻һ��", "����", MB_OK);
			continue;
		}

		char sql[1024];
		sprintf(sql, "select * from user where name = '%s';", user);
		mysql_query(&mysql, sql);
		MYSQL_RES *res = mysql_store_result(&mysql);
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row != NULL)
		{
			MessageBoxA(NULL, "���˺���ע��", "����", MB_OK);
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

//�û�����
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

//��Ϸ�����������ݿ������
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

//��ʼ��Ϸ��ȡ��Ϸ����
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

//��Ϸ������
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
	getimage(gameover_image, "image/��Ϸ����.png");

	ranking_image = newimage();
	getimage(ranking_image, "image/��������.png");

	linkFail = newimage();
	getimage(linkFail, "image/����ʧ��.png");

	pur1 = newimage();
	getimage(pur1, "image/����ɹ�.png");
	pur2 = newimage();
	getimage(pur2, "image/����ʧ��.png");

	mainPimage = newimage();
	getimage(mainPimage, "image/������.png");

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

//�Ƿ�ʹ�ý�Կ��
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

//�˳���Ϸ
int User::ExitGame()
{
	//�˳���Ϸ����
	putimage(0, 0, gameover_image);
	Sleep(1000);
	return 0;
}

//��Ϸ˵��
int User::explainGame()
{
	putimage(0, 0, explain_image);
	getch();
	return 1;
}

//��Ϸ�̵귵��
int User::returnMain()
{
	return 0;
}

//��ʹ�ý�Կ��
int User::noKey()
{
	//getch();
	return 0;
}

//��Ϸ����
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

//��Ϸ����
void User::gameOver()
{
	putimage(0, 0, gameover_image);
	Sleep(1000);
	return;
}

//��Ϸ�̵�
int User::storeGame()
{
	while (true)
	{
		putimage(0, 0,storeMenu);
		putimage_withalpha(NULL,coin , 17 * 32, 0);
		setcolor(BLACK);
		setbkmode(TRANSPARENT);			//�������ֱ���ɫΪ͸��(Ĭ��Ϊ�б���ɫ)
		setfont(32, 0, "��Բ");
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

//������Ϸ��Ʒ1
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

//������Ϸ��Ʒ2
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

//��Ϸ����
int User::rangkGame()
{
	cleardevice();
	putimage(0, 0, ranking_image);

	setcolor(WHITE);
	setbkmode(TRANSPARENT);			//�������ֱ���ɫΪ͸��(Ĭ��Ϊ�б���ɫ)

	setfont(35, 0, "��Բ");
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

//ʹ�ý�Կ��
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

//��ʼ��Ϸ
int User::startGame()	//ѡ��  
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

			//�����Զ��İ���
			for(int i=0;i<4;++i)
			g.n[i].updateNut();
			//�����Զ����ڹ�
			for(int i=0;i<2;++i)
			g.tor[i].updateTor();
			//����ʳ�˻�
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