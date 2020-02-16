#include"image.h"

PIMAGE img;
PIMAGE nums;
PIMAGE mainPimage;
PIMAGE closeMusic;
PIMAGE openMusic;
PIMAGE storeMenu;
PIMAGE goods1_image;//1
PIMAGE goods2_image;//1
PIMAGE goods3_image;//1
PIMAGE explain_image;
PIMAGE pur1;
PIMAGE pur2;
PIMAGE linkFail;
PIMAGE user_sign;//1
PIMAGE user_register;//1
PIMAGE ranking_image;
PIMAGE gameover_image;
PIMAGE gamepass_image;
PIMAGE yes_image;//1
PIMAGE no_image;//1
PIMAGE nextPass_image;
PIMAGE useSuccess;
PIMAGE useFailur;

//获取图片
void getImage()
{
	yes_image = newimage();
	getimage(yes_image, "image/yes.png");
	//
	no_image = newimage();
	getimage(no_image, "image/no.png");
	//
	nextPass_image = newimage();
	getimage(nextPass_image, "image/下一关.png");

	useSuccess = newimage();
	getimage(useSuccess, "image/使用成功.png");

	useFailur = newimage();
	getimage(useFailur, "image/使用失败.png");
	
	gamepass_image = newimage();
	getimage(gamepass_image, "image/游戏通关.png");

	gameover_image = newimage();
	getimage(gameover_image, "image/游戏结束.png");

	ranking_image = newimage();
	getimage(ranking_image, "image/排名背景.png");

	user_sign = newimage();
	getimage(user_sign, "image/登录.png");

	user_register = newimage();
	getimage(user_register, "image/注册.png");

	linkFail = newimage();
	getimage(linkFail, "image/连接失败.png");

	pur1 = newimage();
	getimage(pur1, "image/购买成功.png");
	pur2 = newimage();
	getimage(pur2, "image/购买失败.png");

	//获取按钮图片
	goods1_image = newimage();
	getimage(goods1_image, "image/商品1.png");
	goods2_image = newimage();
	getimage(goods2_image, "image/商品2.png");
	goods3_image = newimage();
	getimage(goods3_image, "image/商品3.png");
	openMusic = newimage();
	getimage(openMusic, "image/musicOpen.png");
	closeMusic = newimage();
	getimage(closeMusic, "image/musicClose.png");
	exitGame.current = newimage();
	getimage(exitGame.current, "image/exit.png");
	start.current = newimage();
	getimage(start.current, "image/start.png");
	store.current = newimage();
	getimage(store.current, "image/store.png");
	ranking.current = newimage();
	getimage(ranking.current, "image/ranking.png");
	explain.current = newimage();
	getimage(explain.current, "image/explain.png");
	//获取乌龟图片
	for (int i = 0; i < 2; ++i)
	{
		tor[i].left = newimage();
		tor[i].leftMove = newimage();
		tor[i].right = newimage();
		tor[i].rightMove = newimage();
		tor[i].torDead = newimage();
		getimage(tor[i].left, "image/乌龟1f.png");
		getimage(tor[i].leftMove, "image/乌龟2f.png");
		getimage(tor[i].right, "image/乌龟1.png");
		getimage(tor[i].rightMove, "image/乌龟2.png");
		getimage(tor[i].torDead, "image/乌龟3.png");
	}
	//获取硬币图片
	for (int i = 0; i < 5; ++i)
	{
		c[i].currentImage = newimage();
		getimage(c[i].currentImage, "image/硬币0.png");
	}
	//获取马里奥图片
	mar.dead = newimage();
	mar.left = newimage();
	mar.leftMove = newimage();
	mar.leftJump = newimage();
	mar.right = newimage();
	mar.rightMove = newimage();
	mar.rightJump = newimage();
	getimage(mar.dead, "image/dead.png");
	getimage(mar.left, "image/left.png");
	getimage(mar.leftMove, "image/leftMove.png");
	getimage(mar.leftJump, "image/leftJump.png");
	getimage(mar.right, "image/right.png");
	getimage(mar.rightMove, "image/rightMove.png");
	getimage(mar.rightJump, "image/rightJump.png");
	mar.currentImage = mar.right;
	//获取食人花图片
	for (int i = 0; i < 2; ++i)
	{
		m.all[f[i].x][f[i].y] = flower;
		f[i].close = newimage();
		f[i].open = newimage();
		getimage(f[i].open, "image/食人花2.png");
		getimage(f[i].close, "image/食人花1.png");
		f[i].currentImage = f[i].open;
	}
	//获取板栗图片
	for (int i = 0; i < 4; ++i)
	{
		m.all[n[i].x][n[i].y] = nut;
		n[i].nutLeft = newimage();
		n[i].nutRight = newimage();
		n[i].nutDead = newimage();
		getimage(n[i].nutLeft, "image/nutLeft.png");
		getimage(n[i].nutRight, "image/nutRight.png");
		getimage(n[i].nutDead, "image/nutDead.png");
		n[i].currentImage = n[i].nutRight;
	}
	//获取砖块图片
	m.land1 = newimage();
	m.land2 = newimage();
	m.land3 = newimage();
	m.land4 = newimage();
	getimage(m.land1, "image/land1.png");
	getimage(m.land2, "image/land2.png");
	getimage(m.land3, "image/land3.png");
	getimage(m.land4, "image/land4.png");

	//主界面
	mainPimage = newimage();
	getimage(mainPimage, "image/主界面.png");
	//游戏背景
	img = newimage();
	getimage(img, "image/111.png");

	nums = newimage();
	getimage(nums, "image/life.png");

	storeMenu = newimage();
	getimage(storeMenu, "image/storeMenu.png");

	explain_image = newimage();
	getimage(explain_image, "image/explainGame.png");
}