#include "mylib.h"

int setup_server(in_port_t port)
{
	struct sockaddr_in me;
	int soc_waiting = 1;
	int soc;

	//自分のアドレスをsockaddr_in構造体に設定
	memset((char *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	me.sin_port = htons(port);

	//ipv4でストリーム型のソケット作成
	printf("before socket_waiting = %d\n", soc_waiting);
	soc_waiting = socket(AF_INET, SOCK_STREAM, 0);
	if (soc_waiting < 0)
	{
		perror("socket");
		perror("socket");
		return (-1);
	}
	int optval = 1;
	setsockopt(soc_waiting, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

	printf("after socket_waiting = %d\n", soc_waiting);
	//ソケットに自分のアドレスを設定
	if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1)
	{
		perror("bind");
		perror("bind");
		return (-1);
	}

	//ソケットで接続待ち
	listen(soc_waiting, 1);
	fprintf(stderr, "successfully bound, now waiting\n");

	//接続要求があるまでブロック
	soc = accept(soc_waiting, NULL, NULL);
	printf("soc : %d\n", soc);
	//接続待ちに使ったソケットを閉じる
	close(soc_waiting);

	return soc;
}