/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:47:44 by akihito           #+#    #+#             */
/*   Updated: 2023/01/31 21:28:30 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "session.h"
#define BUF_LEN 20
#define MIN_X 1
#define MIN_Y 1
#define MAX_X 60
#define MAX_Y 60

//移動キーの割り当て
#define NORTH 'w'
#define SOUTH 's'
#define EAST 'd'
#define WEST 'a'
#define QUIT 'q'

//プライベート変数
static int session_soc;//socket
static fd_set mask;
static int width;
static char my_char, peer_char;

typedef struct {
	int x, y;
	char look;
} PLAYER;

static PLAYER me, peer;//自分と相手の状態を保持する変数

static char buf[BUF_LEN];

static WINDOW *win;//表示用のウィンドウ

//session モジュール　にプライベーツな関数
static void hide(PLAYER *who);
static void show(PLAYER *who);
static int update(PLAYER *who, int c);
static int interpret(PLAYER *who);
static void die();

//sessionのモジュールの初期化
void session_init(int soc,
					char mc, int mx, int my,
					char pc, int px, int py)
{
	//初期化データの設定
	session_soc = soc;
	width = soc + 1;
	FD_ZERO(&mask);
	FD_SET(0, &mask);//標準入力のビット
	FD_SET(session_soc, &mask);//ソケットのビット
	me.look = mc;
	peer.look = pc;

	me.x = mx;
	me.y = my;
	peer.x = px;
	peer.y = py;

	//curses の初期化
	initscr();
	signal(SIGINT, die);//シグナルハンドラにdie()を指定。これは割り込みキーが押された際に、端末
	//の設定を正常な状態に戻す必要があるため、

	//ウィンドウ枠
	win = newwin(MAX_Y + 2, MAX_X + 2, 0, 0);
	box(win, ':', '-');

	//端末設定
	cbreak();
	noecho();
}

// void ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void printb(unsigned int v) {
//   unsigned int mask = (int)1 << (sizeof(v) * 8 - 1);
//   do ft_putchar(mask & v ? '1' : '0');
//   while (mask >>= 1);
// }

//sessionメインループ
void session_loop()
{
	int c;//キーボードからの入力文字
	int flag;//ループ継続フラッグ
	fd_set readOk;//多重入力のマスク

	//自身の姿の表示
	show(&me);

	//ループ継続フラグの初期化
	flag = 1;

	//ループ
	while(1)//flag == 0 で抜ける
	{
		//selectの前に毎回readOkを初期化する
		readOk = mask;
		// printb(readOk.fds_bits);
		select(width, (fd_set *)&readOk, NULL, NULL, NULL);

		//キーボードからの入力ありか？
		if (FD_ISSET(0, &readOk))
		{
			c = getchar();
			hide(&me);
			hide(&me);
			flag = update(&me, c);
			show(&me);
			write(session_soc, buf, BUF_LEN);
			if (flag ==  0) break;
		}

		//ソケットにデータありか？
		if ( FD_ISSET(session_soc, &readOk))
		{
			read(session_soc, buf, BUF_LEN);
			hide(&peer);
			flag = interpret(&peer);
			show(&peer);
			if (flag == 0)break;
		}
	}
	//端末属性を復旧して終わる
	die();
}

static void show(PLAYER *who)
{
	wmove(win, who->y, who->x);//whoの場所に置く
	waddch(win, who->look);//その場にwhoのlookを置く
	wmove(win, who->y, who->x);//カーソルを戻す
	wrefresh(win);//ウィンドウの更新
}

static void hide(PLAYER *who)
{
	wmove(win, who->y, who->x);//whoの場所に動く
	waddch(win, ' ');//その場所にスペースを書く
}

static int update(PLAYER *who, int c)
{
	switch(c)
	{
		case WEST:
			if (who->x > MIN_X)
				(who->x)--;
			break;
		case NORTH:
			if (who->y > MIN_Y)
				(who->y)--;
			break;
		case SOUTH:
			if (who->y < MAX_Y)
				(who->y)++;
			break;
		case EAST:
			if (who->x < MAX_X)
				(who->x)++;
			break;
		case QUIT:
			buf[0]=QUIT;
			return 0;
		default:
			break;
	}
	//更新された位置データを送信用文字列に変更する
	sprintf(buf, "%d %d\n", who->x, who->y);
	return 1;
}

static int interpret(PLAYER *who)
{
	//もし相手が終了を希望したら
	if (buf[0] == 'q')
		return 0;

	//受信文字列から位置データに変換する
	sscanf(buf, "%d %d", &who->x, &who->y);
	return 1;
}

static void die()
{
	endwin();
	exit(0);
}