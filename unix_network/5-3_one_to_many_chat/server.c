/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:26:23 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 00:24:26 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sessionman.h"
#include <stdio.h>
#include "../mylib/mylib.h"

//ミニ電子会議のサーバプログラム

int main(int argc, char *argv[])
{
	int num;
	int soc;
	int maxfd;

	//引数で参加者人数を知る
	if (argc != 2)
	{
		fprintf(stderr, "usage: s attendants\n");
		exit(0);
	}

	//引数の変換　文字列==>int
	if((num = atoi(argv[1])) <= 0 && num > MAX_ATTENDANTS)
	{
		fprintf(stderr, "attendants = LIMIT = %d\n", MAX_ATTENDANTS);
		exit(1); 
	}

	//ソケットディスクリプタをsocに受け取る
	if (( soc = mserver_socket( PORT, num)) == -1)
	{
		fprintf(stderr, "cannot setup server\n");
		exit(1);
	}

	fprintf(stderr, "soc = %d\n", soc);
	//m_acceptにコールバック関数のenterを渡す帰ってくるのは最大のディスクリプタ
	maxfd = mserver_maccept(soc, num, enter);
	if (maxfd != 0)
	{	
		fprintf(stderr, "mserver_accept success\n");
	}
	fprintf(stderr, "successfully bound, now waiting in main()\n");
	fprintf(stderr, "maxfd = %d\n", maxfd);

	//セッションモジュールの初期化
	sessionman_init(num, maxfd);

	//セッション管理のメインループ
	sessionman_loop();
	

}