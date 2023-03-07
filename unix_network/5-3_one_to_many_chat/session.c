/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 02:13:16 by akihito           #+#    #+#             */
/*   Updated: 2023/03/07 19:17:41 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <curses.h>
#include "session.h"
#define BUF_LEN 80

//sousinnyouuxindounosaizu

#define SEND_WIN_WIDTH 60
#define SEND_WIN_HEIGHT 1

//受信用ウィンドウのサイズ
#define RECV_WIN_WIDTH 60
#define RECV_WIN_HEIGHT 13

//送信ようと受信用のウィンドウを分ける

static WINDOW *win_send, *win_recv;
static WINDOW *frame_send, *frame_recv;

//通信用の変数
static char send_buf[BUF_LEN];//送信バッファ
static char recv_buf[BUF_LEN];//受信バッファ
static int session_soc;//ソケット
static fd_set mask;//selectよう初期化マスク
static int width;//マスクの幅

//終了処理の関数
static void die();

//公開される関数群

//セッションの初期化
void session_init(int soc)
{
	//selectようのマスクの設定
	session_soc = soc;
	width = soc + 1;
	FD_ZERO(&mask);
	FD_SET(0, &mask);
	FD_SET(soc, &mask);

	//cursesの初期化など
	initscr();
	signal(SIGINT, die);

	//送信用ウィンドウと枠を作る
	frame_send = newwin( SEND_WIN_HEIGHT + 2, SEND_WIN_WIDTH + 2, 18, 0);
	win_send = newwin( SEND_WIN_HEIGHT, SEND_WIN_WIDTH, 19, 1);
	box(frame_send, ':', '-');
	scrollok(win_send, TRUE);
	wmove(win_send, 0, 0);

	//受信用ウィンドウと枠を作る
	frame_recv = newwin(RECV_WIN_HEIGHT + 2, RECV_WIN_WIDTH+ 2, 0, 0);
	win_recv = newwin(RECV_WIN_HEIGHT, RECV_WIN_WIDTH, 1, 1);
	box(frame_recv, ':', '-');
	scrollok(win_recv, TRUE);
	wmove(win_recv, 0, 0);

	//端末属性の変更　複数のディスクリプタを同時に読み書きするときは、こうした方が管理が楽
	cbreak();//入力バッファを使用しないモードに変更
	noecho();//キー入力された文字を表示しないモードに設定

	//ウィンドウの表示
	wrefresh(frame_recv);
	wrefresh(win_recv);
	wrefresh(frame_send);
	wrefresh(win_send);
}

//セッションのメインループ
void session_loop()
{
	int c;//キーボードからの入力文字
	int flag = 1;
	fd_set readOk;
	int len = 0;
	int i;
	int y, x;
	int n;

	while(1)
	{
		//selectの前に毎回readOkを初期化する
		readOk = mask;
		select(width, (fd_set *)&readOk, NULL, NULL, NULL);

		if ( FD_ISSET(0, &readOk))
		{
			c = getchar();

			//back spaceの処理
			if (c == '\b' || c == 0x10 || c == 0x7F)
			{
				if (len == 0)
					continue;
				len--;
				getyx(win_send, y, x);
				wmove(win_send, y, x-1);
				waddch(win_send, ' ');
				wmove(win_send, y, x-1);
			}
			else if (c == '\n' || c == '\r')//改行で送信
			{
				send_buf[len++] = '\n';
				write(session_soc, send_buf, len);

				//clearing the send windo
				wclear(win_send);
				len = 0;
			}
			else
			{
				send_buf[len++] = c;
				waddch(win_send, c);
			}
			wrefresh(win_send);
		}
		//ソケットにデータありか？
		if (FD_ISSET(session_soc, &readOk))
		{
			n = read(session_soc, recv_buf, BUF_LEN);
			for(i = 0; i < n; i++)
			{
				// fprintf(stderr, "FD_ISSET(session_soc, &readOk)\n");
				waddch(win_recv, recv_buf[i]);
			}

			//quitを受けたら終了
			if (strstr(recv_buf, "quit")!=NULL)
			{
				flag = 0;
				wrefresh(win_recv);

				//move cursro back to the send buffer
				wrefresh(win_send);
			}

			if (flag == 0)
				break;
		}
	}
	//端末属性を復旧し終わる
	die();
}

static void die()
{
	endwin();
	close(session_soc);
	exit(0);
}