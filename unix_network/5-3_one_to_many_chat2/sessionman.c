/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sessionman.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:24:04 by akihito           #+#    #+#             */
/*   Updated: 2023/01/31 00:47:47 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sessionman.h"
#include <stdio.h>
#include <sys/types.h>
#include "session.h"
#include <stdlib.h>
#include <string.h>

static char buf[BUF_LEN];
static fd_set mask;
static int width;
static int attendants;

typedef struct
{
	int fd;
	char name[16];
} ATTENADNT;

static ATTENADNT p[MAX_ATTENDANTS];

static void send_all(int i, int n);
static void ending();

void enter(int i, int fd)
{
	int len;
	static char *mesg1="Type your name\n";
	static char *mesg2="Wait\n";

	p[i].fd = fd;
	memset(p[i].name, 0, 16);
	write(fd, mesg1, strlen(mesg1));
	len = read(fd, p[i].name, 16);//名前を待ち受ける
	sprintf(p[i].name + len -1, " -->  ");
	write(fd, mesg2, strlen(mesg2));
}

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

void sessionman_loop()
{
	fd_set	readOk;
	int		i;

	while(1)
	{
		readOk = mask;
		select(width, (fd_set *)&readOk, NULL, NULL, NULL);

		if (FD_ISSET(0, &readOk))
			ending;
		
		for( i = 0; i < attendants; i++)
		{
			if (FD_ISSET(p[i].fd, &readOk))//データのきているソケットに対してreadする
			{
				int	n;
				n = read(p[i].fd, buf, BUF_LEN);
				send_all(i, n);
			}
		}
	}
}

static void ending()
{
	int		i;

	for( i = 0; i < attendants; i++)
		write(p[i].fd, "q", 1);
	for(  i = 0; i < attendants; i++)
		close(p[i].fd);
	exit(0);
}

static void send_all(int i, int n )
{
	int		j;

	for ( j = 0; j < attendants; j++)
	{
		write(p[j].fd, p[i].name, strlen(p[i].name));
		write(p[j].fd, buf, n);
	}
}



