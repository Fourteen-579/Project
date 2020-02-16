#pragma once
#include"mysql.h"
#include"Game.h"
#include"image.h"
#include<graphics.h>
#pragma comment(lib,"libmysql.lib")

extern MYSQL mysql;
extern MYSQL_RES *res;
extern MYSQL_ROW row;

void userMain();
int sign();
int registers();