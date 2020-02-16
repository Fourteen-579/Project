#include"Game.h"
int key;
int counter;

struct mario mar;
struct wugui tor[2];
struct coin c[5];
struct nut n[4];
struct map m;
struct flowers f[2];

char user_current[100];

//������Ϸ����
void updateGame()
{
	mar.death = 1;
	mar.getCoin = 0;
	mar.getDeath = 0;
	mar.offsetX = 0;
	mar.offsetY = 0;

	mar.isRight = true;
	mar.isJump = false;
	mar.isMove = false;
	mar.isDead = false;
	mar.currentImage = mar.right;

	for (int i = 0; i < 5; ++i)
		c[i].isDead = false;
	for (int i = 0; i < 4; ++i)
		n[i].isDead = false;
	for (int i = 0; i < 2; ++i)
	{
		tor[i].isDead = false;
		tor[i].isSui = false;
	}
}

//��ȡ����
void input()
{
	key = -1;
	int j = keystate('J');
	int a = keystate('A');
	int d = keystate('D');
	if (!mar.isJump)
	{
		if (j)
			key = 'j';
		else if (a)
			key = 'a';
		else if (d)
			key = 'd';
	}
	else
	{
		if (a)
			key = 'a';
		else if (d)
			key = 'd';
		else if (j)
			key = 'j';
	}
}

void update()
{
	//����´��
	if (!mar.isDead)
	{
		//���������
		updateMar();
		//�����Զ��İ���
		updateNut();
		//�����Զ����ڹ�
		updateTor();
		//����ʳ�˻�
		updateFlo();
	}
	//���������
	if (mar.isDead && mar.death > 0)
	{
		if (mar.offsetY == 0)
		{
			mar.death -= 1;
			mar.y += 1;
			mar.offsetY = -32;
		}
		else
			mar.offsetY += 4;
	}//������Ϸ
}

//��������µ�λ�õ���Ϣ
void updateMar()
{
	//�ƶ�״̬�£��������κ�ָ�ֱ������ƶ�
	if (mar.isMove)
	{
		updateMarMove();
	}
	//���ƶ�״̬�����Խ���ָ�������Ծ״̬��
	else
	{
		dealKey();
	}
	//������ֱ����
	if (mar.isJump)
	{
		updateVertical();
	}
	get();
	isDeaded();
	updateDown();
}

//��������µ��ƶ�״̬
void updateMarMove()
{
	//����Ϊ�ұ�
	if (mar.isRight)
	{
		++mar.offsetX;
		++counter;
		int t = counter / N;
		if (t % 2)
		{
			mar.currentImage = mar.right;
		}
		else
		{
			mar.currentImage = mar.rightMove;
		}
	}
	else//���
	{
		--mar.offsetX;
		++counter;
		int t = counter / N;
		if (t % 2)
		{
			mar.currentImage = mar.left;
		}
		else
		{
			mar.currentImage = mar.leftMove;
		}
	}

	//�ƶ����
	if (mar.offsetX == 0)
	{
		mar.isMove = false;
		if (mar.isRight)
			mar.currentImage = mar.right;
		else
			mar.currentImage = mar.left;
		mar.offsetX = 0;
		counter = 0;
	}
}

//�����õİ�����Ϣ
void dealKey()
{
	//����ָ��
	if (key == 'a')
	{
		//�����ұߣ�ֱ�ӵ�ͷ����
		if (mar.isRight)
		{
			mar.isRight = false;
			mar.currentImage = mar.left;
		}
		//������ߣ���Ҫ�ж��ܷ��ƶ�
		else
		{
			//�����ƶ�
			if (mar.x - 1 >= 0 && m.all[mar.x - 1][mar.y] == null)
			{
				//����һ������ָ��
				mar.offsetX = 32;
				mar.isMove = true;
				m.all[mar.x][mar.y] = null;
				--mar.x;
				m.all[mar.x][mar.y] = mario;
			}
		}
	}

	if (key == 'd')
	{
		if (mar.isRight)
		{
			//�����ƶ�
			if (mar.x + 1 < 20 && m.all[mar.x + 1][mar.y] == null)
			{
				//����һ������ָ��
				mar.offsetX = -32;
				mar.isMove = true;
				//���µ�ͼ
				m.all[mar.x][mar.y] = null;
				++mar.x;
				m.all[mar.x][mar.y] = mario;
			}
		}
		else
		{
			mar.isRight = true;
			mar.currentImage = mar.right;
		}
	}

	//��Ծ��
	if (key == 'j')
	{
		//һ������3�����ӵĸ߶�
		if (mar.isJump == false && mar.y - 1 >= 0 && m.all[mar.x][mar.y - 1] == null)
		{
			mar.isJump = true;
			//ʣ����Ҫ�����ĸ���
			mar.h = 2;
			m.all[mar.x][mar.y] = null;
			--mar.y;
			m.all[mar.x][mar.y] = mario;
			mar.offsetY = 32;
		}
	}
}

//������ֱ����
void updateVertical()
{
	if (mar.isRight)
	{
		mar.currentImage = mar.rightJump;
	}
	else
	{
		mar.currentImage = mar.leftJump;
	}
	//����
	if (mar.h >= 0)
	{
		updateVerticalUp();
	}
	//����
	else
	{
		updateVerticalDown();
	}
}

//���������������Ծ
void updateVerticalUp()
{
	mar.offsetY -= 2;

	//һ���ƶ����
	if (mar.offsetY == 0)
	{
		--mar.h;
		if (mar.h >= 0)
		{
			//�Ϸ�û����ײ
			if (mar.y - 1 >= 0 && m.all[mar.x][mar.y - 1] == null)
			{
				m.all[mar.x][mar.y] = null;
				--mar.y;
				m.all[mar.x][mar.y] = mario;
				mar.offsetY = 32;
			}
			else
			{
				//���ȼ���Ƿ��Ѿ�����ˣ��ڿ��з�����λ�Ƶ�������ܻ�������������
				if (m.all[mar.x][mar.y + 1] == land1 || m.all[mar.x][mar.y + 1] == land2 || m.all[mar.x][mar.y + 1] == land3 || m.all[mar.x][mar.y] == land4)
				{
					mar.isJump = false;
					mar.h = 0;
					if (mar.isRight)
					{
						mar.currentImage = mar.right;
					}
					else
					{
						mar.currentImage = mar.left;
					}
				}
				else
				{
					mar.h = -1;//����ײ��������������״̬����������һЩ�߼�
					m.all[mar.x][mar.y] = null;
					++mar.y;
					m.all[mar.x][mar.y] = mario;
					mar.offsetY = -32;
				}
			}
		}
		else
		{
			if (m.all[mar.x][mar.y + 1] == land1 || m.all[mar.x][mar.y + 1] == land2 || m.all[mar.x][mar.y + 1] == land3 || m.all[mar.x][mar.y + 1] == land4)
			{
				mar.isJump = false;
				mar.h = 0;
				if (mar.isRight)
				{
					mar.currentImage = mar.right;
				}
				else
				{
					mar.currentImage = mar.left;
				}
			}
			else
			{
				m.all[mar.x][mar.y] = null;
				++mar.y;
				m.all[mar.x][mar.y] = mario;
				mar.offsetY = -32;
			}
		}
	}
}

//������������½���
void updateVerticalDown()
{
	mar.offsetY += 2;
	//һ���ƶ����
	if (mar.offsetY == 0)
	{
		//���ȼ���Ƿ��Ѿ������
		if (m.all[mar.x][mar.y + 1] != null)
		{
			mar.isJump = false;
			mar.h = 0;
			if (mar.isRight)
			{
				mar.currentImage = mar.right;
			}
			else
			{
				mar.currentImage = mar.left;
			}
		}
		else
		{
			if (m.all[mar.x][mar.y + 1] == land1 || m.all[mar.x][mar.y + 1] == land2 || m.all[mar.x][mar.y + 1] == land3 || m.all[mar.x][mar.y + 1] == land4)
			{
				mar.isJump = false;
				mar.h = 0;
				if (mar.isRight)
				{
					mar.currentImage = mar.right;
				}
				else
				{
					mar.currentImage = mar.left;
				}
			}
			else
			{
				m.all[mar.x][mar.y] = null;
				++mar.y;
				m.all[mar.x][mar.y] = mario;
				mar.offsetY = -32;
			}
		}
	}
}

//��ȡ��� ����Ģ���ڹ�
void get()
{
	//�ȵ��ڹ�
	for (int i = 0; i < 2; ++i)
	{
		if (mar.x == tor[i].x && (mar.y + 1) == tor[i].y && !tor[i].isSui)
		{
			if (tor[i].isDead)
			{
				tor[i].isSui = true;
				m.all[tor[i].x][tor[i].y] = null;
			}
			else
			{
				tor[i].isDead = true;
				++mar.getDeath;
				tor[i].currentImage = tor[i].torDead;
			}
			mar.isJump = true;
			mar.h = 1;
			m.all[mar.x][mar.y] = null;
			--mar.y;
			m.all[mar.x][mar.y] = mario;
			mar.offsetY = 32;
		}
	}

	for (int i = 0; i < 5; ++i)		//��ý��
	{
		if (mar.x == c[i].x && mar.y == c[i].y && !c[i].isDead)
		{
			c[i].isDead = true;
			mar.getCoin += 1;
		}
	}

	for (int i = 0; i < 4; ++i)		//��������
	{
		if (mar.x == n[i].x && (mar.y + 1) == n[i].y && !n[i].isDead)
		{
			n[i].isDead = true;
			++mar.getDeath;
			mar.isJump = true;
			mar.h = 1;
			m.all[mar.x][mar.y] = null;
			--mar.y;
			m.all[mar.x][mar.y] = mario;
			mar.offsetY = 32;
			n[i].currentImage = n[i].nutDead;
			n[i].death = 32;
		}
	}
}

//�ж�����
void isDeaded()
{
	for (int i = 0; i < 4; ++i)		//ײ������
	{
		if (mar.x == n[i].x && mar.y == n[i].y && !mar.isDead && !n[i].isDead)
		{
			mar.isDead = true;
			--mar.hasLife;
			mar.offsetY = -32;
			mar.currentImage = mar.dead;
			mar.death = 5;
			break;
		}
	}
	for (int i = 0; i < 2; ++i)		//ײ��ʳ�˻�
	{
		if ((mar.x == f[i].x && mar.y == f[i].y) || (mar.x == f[i].x && (mar.y + 1) == f[i].y))
		{
			mar.isDead = true;
			--mar.hasLife;
			mar.offsetY = -32;
			mar.currentImage = mar.dead;
			mar.death = 5;
			break;
		}
	}
	for (int i = 0; i < 2; ++i)		//ײ���ڹ�
	{
		if (mar.x == tor[i].x && mar.y == tor[i].y && !tor[i].isSui)
		{
			mar.isDead = true;
			--mar.hasLife;
			mar.offsetY = -32;
			mar.currentImage = mar.dead;
			mar.death = 5;
			break;
		}
	}
	if (mar.y == 19 && mar.h < 0)
	{
		mar.isDead = true;
		--mar.hasLife;
		mar.offsetY = -32;
		mar.currentImage = mar.dead;
		mar.death = 5;
	}
}

//�ж��Ƿ���Ҫ����
void updateDown()
{
	//�ж��Ƿ���Ҫ����
	if (!mar.isJump && !mar.isMove)
	{
		if (m.all[mar.x][mar.y + 1] == null)
		{
			mar.isJump = true;
			mar.offsetY -= 32;
			mar.h = -1;//��ʾ���½�
			m.all[mar.x][mar.y] = null;
			mar.y++;
			m.all[mar.x][mar.y] = mario;
		}
	}
}

//�����ڹ�
void updateTor()
{
	for (int i = 0; i < 2; ++i)
	{
		if (!tor[i].isSui)
		{
			if (tor[i].x <= tor[i].rightLimit && tor[i].x >= tor[i].leftLimit)//û���ڱ߽�
			{
				if (tor[i].x == tor[i].leftLimit)
				{
					tor[i].isRight = true;
				}
				else if (tor[i].x == tor[i].rightLimit)
				{
					tor[i].isRight = false;
				}
				if (tor[i].isRight)
				{
					++tor[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].right;
					}
					else
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].rightMove;
					}
					if (tor[i].offsetX == 32)
					{
						m.all[tor[i].x][tor[i].y] = null;
						++tor[i].x;
						m.all[tor[i].x][tor[i].y] = nut;
						tor[i].offsetX = 0;
					}
				}
				else
				{
					--tor[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].left;
					}
					else
					{
						if (tor[i].isDead)
							tor[i].currentImage = tor[i].torDead;
						else
							tor[i].currentImage = tor[i].leftMove;
					}
					if (tor[i].offsetX == -32)
					{
						m.all[tor[i].x][tor[i].y] = null;
						--tor[i].x;
						m.all[tor[i].x][tor[i].y] = nut;
						tor[i].offsetX = 0;
					}
				}
			}
		}
	}
}

//���°���
void updateNut()
{
	for (int i = 0; i < 4; ++i)
	{
		if (!n[i].isDead)
		{
			if (n[i].x <= n[i].rightLimit && n[i].x >= n[i].leftLimit)//û���ڱ߽�
			{
				if (n[i].x == n[i].leftLimit)
				{
					n[i].isRight = true;
				}
				else if (n[i].x == n[i].rightLimit)
				{
					n[i].isRight = false;
				}
				if (n[i].isRight)
				{
					++n[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						n[i].currentImage = n[i].nutRight;
					}
					else
					{
						n[i].currentImage = n[i].nutLeft;
					}
					if (n[i].offsetX == 32)
					{
						m.all[n[i].x][n[i].y] = null;
						++n[i].x;
						m.all[n[i].x][n[i].y] = nut;
						n[i].offsetX = 0;
					}
				}
				else
				{
					--n[i].offsetX;
					++counter;
					int t = counter / N;
					if (t % 2)
					{
						n[i].currentImage = n[i].nutRight;
					}
					else
					{
						n[i].currentImage = n[i].nutLeft;
					}
					if (n[i].offsetX == -32)
					{
						m.all[n[i].x][n[i].y] = null;
						--n[i].x;
						m.all[n[i].x][n[i].y] = nut;
						n[i].offsetX = 0;
					}
				}
			}
		}
	}

	//��������
	for (int i = 0; i < 4; ++i)
	{
		if (n[i].isDead && n[i].death > 0)
		{
			--n[i].death;
		}
		else if (n[i].isDead && n[i].death == 0)
		{
			m.all[n[i].x][n[i].y] = null;
		}
	}
}

//����ʳ�˻�
void updateFlo()
{
	for (int i = 0; i < 2; ++i)
	{
		int cun = f[i].cc / 10;
		if (cun % 2)
			f[i].currentImage = f[i].open;
		else
			f[i].currentImage = f[i].close;
		++f[i].cc;
	}
}

//���ͼƬ
void render()
{
	cleardevice();
	putimage(0, 0, img);
	putimage(13 * 32, 0, nums);


	setcolor(BLACK);
	setbkmode(TRANSPARENT);			//�������ֱ���ɫΪ͸��(Ĭ��Ϊ�б���ɫ)
	setfont(32, 0, "��Բ");
	char a[10];
	sprintf(a, "%c", mar.getCoin + 48);
	outtextxy(18 * 32, 0, a);
	sprintf(a, "%c", mar.hasLife + 48);
	outtextxy(15 * 32 + 10, 0, a);

	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			if (m.all[x][y] == land1)
			{
				putimage_withalpha(NULL, m.land1, x * 32, y * 32);
			}
			else if (m.all[x][y] == land2)
			{
				putimage_withalpha(NULL, m.land2, x * 32, y * 32);
			}
			else if (m.all[x][y] == land3)
			{
				putimage_withalpha(NULL, m.land3, x * 32, y * 32);
			}
			else if (m.all[x][y] == land4)
			{
				putimage_withalpha(NULL, m.land4, x * 32, y * 32);
			}
		}
	}
	//�������
	putimage_withalpha(NULL, mar.currentImage, mar.x * 32 + mar.offsetX, mar.y * 32 + mar.offsetY);
	//�ڹ�����
	for (int i = 0; i < 2; ++i)
	{
		if (!tor[i].isSui)
			putimage_withalpha(NULL, tor[i].currentImage, tor[i].x * 32 + tor[i].offsetX, tor[i].y * 32);
	}
	//�����ĸ�
	for (int i = 0; i < 4; ++i)
	{
		if (n[i].isDead && n[i].death == 0)
			continue;
		putimage_withalpha(NULL, n[i].currentImage, n[i].x * 32 + n[i].offsetX, n[i].y * 32);
	}
	//ʳ�˻�����
	for (int i = 0; i < 2; ++i)
	{
		putimage_withalpha(NULL, f[i].currentImage, f[i].x * 32, f[i].y * 32);
	}
	//������
	for (int i = 0; i < 5; ++i)
	{
		if (!c[i].isDead)
		{
			putimage_withalpha(NULL, c[i].currentImage, c[i].x * 32, c[i].y * 32);
		}
	}
}

//��Ϸ�����������ݿ������
void updateSQL()
{
	char sql[1024];
	sprintf(sql, "select * from user where name = '%s';", user_current);
	mysql_query(&mysql, sql);
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	sprintf(sql, "update user set coin = '%d' where name = '%s';", atoi(row[2]) + mar.getCoin, user_current);
	mysql_query(&mysql, sql);
}