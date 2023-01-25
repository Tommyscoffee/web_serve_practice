#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>    /* sockaddr_in、inet_addr()に必要 */

#define PORT (in_port_t)5512
#define BUF_LEN 512

int main()
{
	struct hostent *server_ent;//サーバ（相手）の情報
	struct sockaddr_in server; //サーバのアドレス
	int soc;//ソケットのディスクリプタ
	char hostname[] = "127.0.0.1"; // サーバ（相手）のホスト名
	char buf[BUF_LEN];// 送受信のバッファ

	//サーバのホスト名からアドレス情報を得る
	if ((server_ent = gethostbyname(hostname)) == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
	printf("%d: %s\n", __LINE__, server_ent->h_name);fflush(stdout);
	//サーバのアドレスをsockaddr_in 構造体に格納
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(hostname);
	memcpy((char *)&server.sin_addr, server_ent->h_addr, server_ent->h_length);

	//IPv4でストリーム型のソケットを作成
	if ((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}
	printf("soc %d\n", soc);
	//サーバに接続
	if ((connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1))
	{
		perror("connect");
		exit(1);
	}


	//相手が先
	write(1, "Wait\n", 5);

	//通信ループ
	while ( strncmp(buf, "quit", 4) != 0)
	{
		int n;

		n = read(soc, buf, BUF_LEN);
		write(1, buf, n);
		n = read(0, buf, BUF_LEN);
		write(soc, buf, n);
	}

	close(soc);
}