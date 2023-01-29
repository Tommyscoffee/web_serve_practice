/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sessionman.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:33:11 by akihito           #+#    #+#             */
/*   Updated: 2023/01/29 15:49:18 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ミニ電子会議のセッション管理プログラム

#include <stdio.h>
#include <sys/types.h>
#include "sessionman.h"
#define MAX_ATTENDANTS 5
#define BUF_LEN			80

static char buf[BUF_LEN];//送受信バッファ
static fd_set mask;//selectよう初期化マスク
static int width;//監視ディスクリプタの範囲
static int attendants;//参加人数

//参加者管理のためのデータ構造
typedef struct
{
	int fd;
char name[16];
} ATTENDANT;


static ATTENDANT p[MAX_ATTENDANTS];

//sessionのメインループの下請けルーチン
static void send_all(int i, int n);
static void ending();

//enterはmserver_maccept()に渡されるコールバック
void enter(int i, int fd)
{
	int len;//受信バイト数
	static char *mesg1="Type your name\n";
	static char *mesg2="Wait\n";

	p[i].fd = fd;
	memset(p[i].name, 0, 16);
	write(fd, mesg1, strlen(mesg1));
	len = read(fd, p[i].name, 16);
	sprintf(p[i].name + len - 1, " --> ");
	write(fd, mesg2, strlen(mesg2));
}

//セッションの初期化
void sessionman_init(int num, int maxfd)
{
	int i;
	static char *mesg = "Communication Ready\n";
	attendants = num;

	//selectのためのマスク準備
	width - maxfd +1;
	FD_ZERO(&mask);
	FD_SET(0, &mask);
	for(i = 0; i < num; i++)
	{
		FD_SET(p[i].fd, &mask);
	}

	//セッション開始のメッセージを全員に送る
	for (i = 0; i < num; i++)
	{
		write(p[i].fd, mesg, strlen(mesg));
	}
}

//セッションのメインループ
void sessionman_loop()
{
	fd_set readOk;//selectのためのマスク
	int i;

	while(1)
	{
		readOk = mask;
		select(width, (fd_set *)&readOk, NULL, NULL, NULL);
	}

	//キーボードからの入力ありか?
	if (FD_ISSET(0, &readOk))//サーバーのオペレータが何かキー入力をするとセッションが終了する。
		ending();

	//ソケットを順に調べる
	for(i = 0; i < attendants; i++)//データのきているソケットを調べてreadし、それをすぐ全参加者に配信する
	{
		if ( FD_ISSET(p[i].fd, &readOk))
		{
			int n;
			n = read(p[i].fd, buf, BUF_LEN);
			send_all(i, n);
		}
	}
}

static void ending()
{
	int i;
	for(i = 0; i < attendants; i++)
		write(p[i].fd, 'q', 1);
	for( i = 0; i < attendants; i++ )
		close(p[i].fd);
	exit(0);
}

static void send_all(int i, int n)
{
	int j;

	for(j = 0; j < attendants; j++)
	{
		write(p[j].fd, p[j].name, strlen(p[i].name));
		write(p[j].fd, buf, n);
	}
}