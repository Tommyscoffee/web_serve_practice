#include "mylib.h"

int setup_client(char *hostname, in_port_t port)//接続先のポート
{
	struct hostent *server_ent;
	struct sockaddr_in server;
	int soc;
	//接続先のホスト名からホストの情報を得る
	server_ent = gethostbyname(hostname);
	if (server_ent == NULL)
	{
		perror("gethostbyname");
		return (-1);
	}
	//接続先のアドレスをsockaddr_in 構造体に設定
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	memcpy((char *)&server.sin_addr, server_ent->h_addr, server_ent->h_length);
	//IPv4でストリーム型のソケットをさくせ
	soc = socket(AF_INET, SOCK_STREAM, 0);
	if (soc < 0)
	{
		perror("socket");
		return (-1);
	}
	//接続
	if (connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("connect");
		return (-1);
	}
	fprintf(stderr, "connected\n");
	printf("soc %d\n", soc);
	//ソケットを返す
	return soc;

}
