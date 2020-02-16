#include<mysql.h>
#include<graphics.h>
#include<stdio.h>
#include"User.h"
#pragma comment(lib,"libmysql")

int last;
int nn;

int main()
{
	initgraph(640, 640);
	setcaption("Fourteen_579");
	User u;
	Button b;
	getImage();
	setButton();
	u.g.getImage();
	u.addButton(sign_button);
	u.addButton(register_button);
	u.addButton(music);
	u.addButton(start);
	u.addButton(store);
	u.addButton(ranking);
	u.addButton(explain);
	u.addButton(exitGame);
	u.addButton(goods1);
	u.addButton(goods2);
	u.addButton(goods3);
	u.addButton(yes);
	u.addButton(no);
	
	u.userMain();
	u.updateSQL();
	return 0;
}