 #include"user.h"
MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;

void getStr(const char *title, char *buffer, int len)
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
int sign()
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
int registers()
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
			break;
		}
	}
	return 0;
}