#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT (in_port_t)5512
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
	me.sin_addr.s_addr = htonl(INADDR_ANY);//IPv4アドレスをしてする
	me.sin_port = htons(PORT);//ネットワークバイトオーダーの問題を解決するため。このフィールドはそのままIPヘッダにコピーされるので、バイトオーダーの問題を避けて通れない。
	//インターネットでのバイトオーダーはBig-endian方針。それを指定してくれるのがhtons(PORT)
	if ((soc_waiting = socket(AF_INET, SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(1);
	}
	printf("soc_waiting %d\n", soc_waiting);

	int bind_res = bind(soc_waiting, (struct sockaddr *)&me, sizeof(me));
	if (bind_res == -1)
	{
		perror("bind");
		exit(1);
	}

	//ソケットで待ち受けることを設定
	listen(soc_waiting, 1);
	printf("before accept\n");
	//接続要求が車でブロックする
	soc = accept(soc_waiting, NULL, NULL);
	printf("soc %d\n", soc);
	//接続待ちのためのソケットを閉じる
	close(soc_waiting);
	write(1, "Go ahead!\n", 10);

	//通信ループ
	while( strncmp(buf, "quit",4) != 0)
	{
		int n;
		n = read(0, buf, BUF_LEN);//通常、readはカーネルの中で一行分バッファされる。つまりキーボードのキーを１つ叩くダビにその文字がプロ
		write(soc, buf,n);//ソケットsocに書き出す
		n = read(soc, buf, BUF_LEN);//ソケットsockから読む
		write(1, buf, n);//標準出力1に書き出す
	}

	close(soc);
}