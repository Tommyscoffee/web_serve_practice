#include "goban.h"
#include <errno.h>
//非公開の変数群
static char goban_my_stone;
static char goban_peer_stone;

//五番の定義と初期化
static char goban_plane[5][6] = {"+123",
								 "a---;",
								 "b---;",
								 "c---;",
								 "+---+"};

static int goban_soc; //ソケットのディスクリプタ

//公開される関数群

//碁盤初期化
void goban_init(int soc, char my_stone, char peer_stone)
{
	goban_soc = soc;
	goban_my_stone = my_stone;
	goban_peer_stone = peer_stone;
}

//碁盤の表示
void goban_show()
{
	int i;
	for(i = 0; i<5; i++)
	{
		printf("%s\n", goban_plane[i]);
	}
}

int goban_peer_turn()
{
	char data[10];
	int x,y;
	int r_count = 0;
	//ソケットから読む
	printf("goban_soc %d\n", goban_soc);
	r_count = read(goban_soc, data, 10);

	printf("r_count : %d\n", r_count);
	printf("errno:  %d\n", errno);

	// data[r_count] = '\0';
	//先頭バイトを見てから終了か判定
	if (data[0] == 'q')
		return (-1);

	printf("%d: \n", __LINE__);
	printf("data[0] = %c\n", data[0]);
	printf("data[2] = %c\n", data[2]);
	printf("%d: \n", __LINE__);
	//座標データの取り出し
	// if (data[0] < 'a' || data[0] > 'c')
	// {
	// 	perror("usage: your input should be like 'a 0'");
	// 	exit(1);
	// }
	printf("%d: \n", __LINE__);
	y = (int)data[0] - (int)'a' + 1;
	x = (int)data[2] - (int)'0';
	printf("%d: \n", __LINE__);
	//データの更新
	goban_plane[y][x] = goban_peer_stone;
	printf("%d: \n", __LINE__);
	return 1;
}

int goban_my_turn()
{
	char data[10];
	int x,y;
	printf("my_turn()\n");
	//キーボード入力
	while(1)
	{
		printf("usage: (a,b,c) (1,2,3)");
		fgets(data, 10, stdin);
		if (data[0] == 'q')
		{
			write(goban_soc, data, 1);
			return (-1);
		}
		if (data[0] < 'a' && data[0] > 'c' && data[1] < '1' && data [1] > '3')
			continue;
		break;
	}

	printf("%d: \n", __LINE__);
	printf("data[0] = %s\n", data);
	printf("%d: \n", __LINE__);
	//データの更新
	y = (int)data[0] - (int)'a' + 1;
	x = (int)data[2] - (int)'0';
	goban_plane[y][x] = goban_my_stone;
	int r_write = 0;
	//送信
	r_write = write(goban_soc, data, 10);// ここでBUS error
	printf("r_write %d\n", r_write);

	return 1;
}

//終了処理

void goban_destroy()
{
	close(goban_soc);
}

