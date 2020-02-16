#pragma once
#include"main.h"
#include"music.h"
#include"image.h"
#include"user.h"
#include<graphics.h>
struct button
{
	int x;
	int y;
	int w;
	int h;
	PIMAGE current;
	int(*onClick)();
};

extern button bts[100];
extern int nn;
extern int last;
extern button start;
extern button store;
extern button ranking;
extern button explain;
extern button exitGame;
extern button music;
extern button goods1;
extern button goods2;
extern button goods3;
extern button sign_button;
extern button register_button;
extern button yes;
extern button no;

void setBotton();
void addButton(button t);
int deal1(mouse_msg t);
int deal2(mouse_msg t);
int deal3(mouse_msg t);
int deal4(mouse_msg t);