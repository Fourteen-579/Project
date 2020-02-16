#pragma once
#include"image.h"
#include<graphics.h>
#include<stdio.h>
#define N 50
enum MapType
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
struct mario
{
	PIMAGE left;
	PIMAGE leftMove;
	PIMAGE leftJump;
	PIMAGE right;
	PIMAGE rightMove;
	PIMAGE rightJump;
	PIMAGE dead;
	PIMAGE currentImage;
	int h;
	int x;
	int y;
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
};
struct wugui
{
	PIMAGE left;
	PIMAGE leftMove;
	PIMAGE right;
	PIMAGE rightMove;
	PIMAGE torDead;
	PIMAGE currentImage;
	int x;
	int y;
	int offsetX;
	bool isSui;//ÎÚ¹ê¿ÇÊÇ·ñÆÆËé
	bool isDead;
	bool isRight;
	int leftLimit;
	int rightLimit;
};
struct coin
{
	PIMAGE currentImage;
	bool isDead;
	int x;
	int y;
};
struct nut
{
	PIMAGE nutLeft;
	PIMAGE nutRight;
	PIMAGE nutDead;
	PIMAGE currentImage;
	int x;
	int y;
	int offsetX;
	int leftLimit;
	int rightLimit;
	int death;
	bool isDead;
	bool isRight;
};
struct map
{
	MapType all[20][20];
	PIMAGE land1;
	PIMAGE land2;
	PIMAGE land3;
	PIMAGE land4;
};
struct flowers
{
	int x;
	int y;
	int cc;
	PIMAGE currentImage;
	PIMAGE open;
	PIMAGE close;
};

void updateGame();
void get();
void isDeaded();
void input();
void updateTor();
void updateNut();
void updateFlo();
void updateMarMove();
void dealKey();
void updateVerticalUp();
void updateVerticalDown();
void updateVertical();
void updateDown();
void updateMar();
void update();
void render();
void updateSQL();

extern struct mario mar;
extern struct wugui tor[2];
extern struct coin c[5];
extern struct nut n[4];
extern struct map m;
extern struct flowers f[2];
extern char user_current[100];