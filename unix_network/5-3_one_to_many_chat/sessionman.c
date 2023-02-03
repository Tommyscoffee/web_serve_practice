/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sessionman.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 01:33:11 by akihito           #+#    #+#             */
/*   Updated: 2023/01/31 00:49:38 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//ミニ電子会議のセッション管理プログラム

#include <stdio.h>
#include <sys/types.h>
#include "sessionman.h"
#include <fcntl.h>

#define MAX_ATTENDANTS	5
#define BUF_LEN			80

static char 	buf[BUF_LEN];//送受信バッファ
static fd_set 	mask;//selectよう初期化マスク
static int 		width;//監視ディスクリプタの範囲
static int 		attendants;//参加人数

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

	fprintf(stderr, "enter()\n");
	fprintf(stderr, "fd = %d\n", fd);
	p[i].fd = fd;
	memset(p[i].name, 0, 16);
	fprintf(stderr, mesg1);
	// fprintf()
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
	width = maxfd + 1;
	FD_ZERO(&mask);
	FD_SET(0, &mask);
	for(i = 0; i < num; i++)
	{
		FD_SET(p[i].fd, &mask);
	}

	//セッション開始のメッセージを全員に送る
	for (i = 0; i < num; i++)
	{
		fprintf(stderr, "p[%d].fd = %d\n", i, p[i].fd);
		write(p[i].fd, mesg, strlen(mesg));
	}
}

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void printb(unsigned int v) {
  unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
  do ft_putchar(mask & v ? '1' : '0');
  while (mask >>= 1);
}

//セッションのメインループ
void sessionman_loop()
{
	fd_set readOk;//selectのためのマスク
	int i;
	fprintf(stderr, "sessionman_loop()\n");
	while(1)
	{
		fprintf(stderr, "while()内\n");
		readOk = mask;
		// fcntl(p[i].fd, F_SETFL, O_NONBLOCK);
		fprintf(stderr, "readOk = %d\n",  readOk.fds_bits);
		select(width, (fd_set *)&readOk, NULL, NULL, 1000);
		fprintf(stderr, "select後\n");
		//キーボードからの入力ありか?
		// if (FD_ISSET(0, &readOk) )//サーバーのオペレータが何かキー入力をするとセッションが終了する。
		// 	ending();

		//ソケットを順に調べる
		for(i = 0; i < attendants; i++)//データのきているソケットを調べてreadし、それをすぐ全参加者に配信する
		{
			fprintf(stderr, "read\n");
			if ( FD_ISSET(p[i].fd, &readOk))
			{
				int n;
				n = read(p[i].fd, buf, BUF_LEN);
				send_all(i, n);
			}
		}
		// wrefresh(frame_recv);
		// wrefresh(win_recv);
		// wrefresh(frame_send);
		// wrefresh(win_send);
	}
}

static void ending()
{
	int i;
	for(i = 0; i < attendants; i++)
		write(p[i].fd, "q", 1);
	for( i = 0; i < attendants; i++ )
		close(p[i].fd);
	exit(0);
}

static void send_all(int i, int n)
{
	int j;

	for(j = 0; j < attendants; j++)
	{
		fprintf(stderr, "send_all()\n");
		write(p[j].fd, p[j].name, strlen(p[i].name));
		write(p[j].fd, buf, n);
	}
}