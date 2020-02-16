#include"music.h"

MUSIC bkmusic;  // ±≥æ∞“Ù¿÷
MUSIC load1Music;
int isMusic = 1;

int musicB()
{
	if (bts[2].current == openMusic)
	{
		isMusic = 0;
		bkmusic.Stop();
		load1Music.Stop();
		bts[2].current = closeMusic;
	}
	else
	{
		isMusic = 1;
		bts[2].current = openMusic;
	}
	return 1;
}