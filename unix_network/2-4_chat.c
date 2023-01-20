#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT (in_port_t)50000
#define BUF_LEN 512

int main()
{
	struct sockaddr_in me;//サーバーの情報
	int soc_waiting;//listenするソケット

	int soc;
	char buf[BUF_LEN];

	//さーばのアドレスをsockaddr_int構造体に格納
	memset((char *)&me,  0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	me.sin_port = htons(PORT);

	if ((soc_waiting = socket(AF_INET, SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(1);
	}

		//ソケットで待ち受けることを設定
	listen(soc_waiting, 1);

	//接続要求が車でブロックする
	soc = accept(soc_waiting, NULL, NULL);

	//接続待ちのためのソケットを閉じる
	close(soc_waiting);
	write(1, "Go ahead!\n", 10);

	//通信ループ
	while( strncmp(buf, "quit",4) != 0)
	{
		int n;
		n = read(0, buf, BUF_LEN);//通常、readはカーネルの中で一行分バッファされる。ツアμりキーボードのキーを１つ叩くダビにその文字がプロ
		write(soc, buf,n);
		n = read(soc, buf, BUF_LEN);
		write(1, buf, n);
	}

	close(soc);
}