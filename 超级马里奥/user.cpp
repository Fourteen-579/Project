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
//�û���¼
int sign()
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
int registers()
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
			break;
		}
	}
	return 0;
}