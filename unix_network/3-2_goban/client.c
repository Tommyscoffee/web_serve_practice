#include "goban.h"

int main()
{
	int soc;//ソケットディスクりぷた
	char my_stone='o';
	char peer_stone='x';
	char hostname[64];//後手のサーバーのホスト名が入る

	//サーバーのホスト名の入力
	printf("input server's hostname: 127.0.0.1 ");
	fgets(hostname, HOSTNAME_LENGTH, stdin);
	chop_newline(hostname, HOSTNAME_LENGTH);

	//接続完了まで
	printf("\n===\n");
	soc = setup_client(hostname, PORT);
	printf("===\n");

	if( soc == -1)
	{
		exit(1);
	}

	//碁盤の初期化
	goban_init(soc, my_stone, peer_stone);

	while(1)
	{
		//自分の番
		goban_show();
		printf("Go ahead\n");
		if (goban_my_turn() == -1)
			break;
		 //相手の番
		 printf("Wait\n");
		 if (goban_peer_turn() == -1)
		 	break;

	}

	//終了処理
	goban_destroy();
	return (0);
}