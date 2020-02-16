#pragma once
#include<mysql.h>
#include<graphics.h>
#include<stdio.h>
#define N 15
#pragma comment(lib,"libmysql")
enum MapsType
{
	null,
	land1,
	land2,
	land3,
	land4,
	mario,
	flower,
	tort,
	nut,
	cold,
};
class Game;
class Mario;
class Maps;
class Game;
class Cold;
class Nut;
class Wugui;
class Flowers;
class Maps;
class Role;
class User;
void getImage();
extern MapsType all[20][20];
extern int nn;
extern int last;
extern int key;

class Music
{
public:
	MUSIC bkmusic;  // ��������
	MUSIC load1Music;
	int isMusic = 1;
	PIMAGE closeMusic;
	PIMAGE openMusic;

	//int musicB(User u);
	Music();
};

class Maps
{
public:
	
	PIMAGE land1_image;
	PIMAGE land2_image;
	PIMAGE land3_image;
	PIMAGE land4_image;
};

class Role
{
public:
	int x = 0;
	int y = 0;
	int counter;
	PIMAGE currentImage;
};

class Mario : public Role
{
public:
	Mario() {};
	
	PIMAGE left;
	PIMAGE leftMove;
	PIMAGE leftJump;
	PIMAGE right;
	PIMAGE rightMove;
	PIMAGE rightJump;
	PIMAGE dead;
	int h;
	int offsetX;
	int offsetY;
	int death;
	int getCoin;
	int getDeath;
	int hasLife;
	bool isDead;
	bool isMove;
	bool isRight;
	bool isJump;
	Mario(int a);
	void update(Cold c[], Wugui tor[], Nut n[], Flowers f[]);
	void updateMar(Cold c[], Wugui tor[], Nut n[], Flowers f[]);//���������λ�õ���Ϣ
	void updateMarMove();//��������µ��ƶ�״̬
	void updateVertical();//�����������ֱ����
	void updateVerticalUp();//���������������Ծ
	void updateVerticalDown();//������������½���
	void get(Cold c[], Wugui tor[], Nut n[]);//��ȡ��� ����Ģ���ڹ�
	void isDeaded(Flowers f[], Wugui tor[], Nut n[]);//�ж�����
	void updateDown();//�ж��Ƿ���Ҫ����;
	void dealKey();
};

class Cold : public Role
{
public:
	Cold() {};
	bool isDead;
};

class Flowers : public Role
{
public:
	Flowers() {};
	int cc;
	PIMAGE open;
	PIMAGE close;

	void updateFlo();
};

class Monster : public Role
{
public:
	int offsetX = 0;
	int leftLimit;
	int rightLimit;
	bool isDead;
	bool isRight;
};

class Wugui : public Monster
{
public:
	Wugui() {};
	PIMAGE left;
	PIMAGE leftMove;
	PIMAGE right;
	PIMAGE rightMove;
	PIMAGE torDead;
	bool isSui;//�ڹ���Ƿ�����

	void updateTor();
};

class Nut : public Monster
{
public:
	Nut() {};
	PIMAGE nutLeft;
	PIMAGE nutRight;
	PIMAGE nutDead;
	int death;

	void updateNut();
};

class Game : public Maps, public Mario
{

public:
	static int pass_num;
	Mario mar;
	Cold c[5];
	Nut n[4];
	Wugui tor[2];
	Flowers f[2];

	PIMAGE land1_image;
	PIMAGE land2_image;
	PIMAGE land3_image;
	PIMAGE land4_image;
	PIMAGE nextPass_image;
	PIMAGE useSuccess;
	PIMAGE useFailur;
	PIMAGE gamepass_image;
	PIMAGE img;
	PIMAGE nums;

	void input();
	void updateGame();

	void render();
	void getImage();

	void set1();
	void set2();
	void set3();
};

struct Button
{
	int x;
	int y;
	int w;
	int h;

	PIMAGE current;

	int(User::*onClick)();
};

int deal1(mouse_msg t, User u);
int deal2(mouse_msg t, User u);
int deal3(mouse_msg t, User u);
int deal4(mouse_msg t, User u);
void setButton();

class User
{
public:

	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char user_current[100];
	int hasCold;
	int hasKey;
	int hasNut;

	Game g;
public:
	struct Button bts[13];

	void userMain();//��¼ע�����
	void getStr(const char *title, char *buffer, int len);
	void updateSQL();//������Ϸ��������ݿ�
	void beginSQL();//��ʼ��Ϸ��ȡ��Ϸ����
	void gameMain();//��Ϸ������
	void getImage();
	void addButton(Button t);
	void useKey(Button b);
	void ini(Button b);
	void gameOver();
	int sign();
	int registers();
	int ExitGame();
	int storeGame();
	int explainGame();
	int returnMain();
	int buy1();
	int buy2();
	int rangkGame();
	int yesKey();
	int noKey();
	int startGame();
};


extern Button start;
extern Button store;
extern Button ranking;
extern Button explain;
extern Button exitGame;
extern Button music;
extern Button goods1;
extern Button goods2;
extern Button goods3;
extern Button sign_button;
extern Button register_button;
extern Button yes;
extern Button no;

extern PIMAGE coin;
extern PIMAGE mainPimage;
extern PIMAGE closeMusic;
extern PIMAGE openMusic;
extern PIMAGE storeMenu;
extern PIMAGE explain_image;
extern PIMAGE pur1;
extern PIMAGE pur2;
extern PIMAGE linkFail;
extern PIMAGE ranking_image;
extern PIMAGE gameover_image;
extern PIMAGE gamepass_image;
extern PIMAGE nextPass_image;
extern PIMAGE useSuccess;
extern PIMAGE useFailur;