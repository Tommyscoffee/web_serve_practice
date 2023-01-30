/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mserver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 22:39:52 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 15:05:19 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int mserver_socket(in_port_t port, int backlog)
{
	struct sockaddr_in me;
	int soc_waiting;

	memset((char *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	me.sin_port = htons(port);

	//IPv4でストリーム型のソケット作成
	soc_waiting = socket(AF_INET, SOCK_STREAM, 0);
	if (soc_waiting < 0)
	{
		perror("socket");
		return -1;
	}

	//bindがラグを解消する
	int optval = 1;
	setsockopt(soc_waiting, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

	//ソケットに自分のアドレスを設定
	if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1)
	{
		perror("bind");
		return (-1);
	}

	//ソケットで接続待ち
	int listen_res = listen(soc_waiting, backlog);//ここでセットアップされるサーバは、いくつものクライアントからの接続要求を、１つのポートで待つ。
	//この後でてくるaccept()を伴う作業は人との対話を含むので時間がかかる。
	//1度に接続要求があった時、それらの要求をどう扱うかが問題
	if (listen_res == -1)
	{
		perror("listen");
		return (-1);
	}

	fprintf(stderr, "successfully bound, now waiting\n");

	return soc_waiting;
}

//マルチアクセプト
int mserver_maccept(int soc_waiting, int limit, void (*func)())//戻り値ソケットディスクリプタの最大値
{
	int i;
	int fd;

	fprintf(stderr, "soc_waiting  = %d", soc_waiting);
	//acceptをlimit回数実行
	for(i = 0; i < limit; i++)
	{
		fd = accept(soc_waiting, NULL, NULL);
		if(fd == -1)
		{
			fprintf(stderr, "accept error\n");
			return (-1);
		}
		fprintf(stderr, " accepted \n fd = %d\n", fd);
		(*func)(i, fd);
	}
	//待ち受けのソケットを閉じる
	close(soc_waiting);

	//最大のfdつまり最大値を返す
	return fd;//なぜfdの最大値を返すのか？マスクの幅を決める
}

