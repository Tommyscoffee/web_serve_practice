/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:04:10 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 03:00:17 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sessionman.h"
#include "../mylib/mylib.h"

int main(int argc, char *argv[])
{
	int		num;
	int		soc;
	int		maxfd;


	if (argc != 2)
	{
		fprintf(stderr, "usage: s attendants\n");
		exit(1);
	}

	num = atoi(argv[1]);
	if (num <= 0 || num > MAX_ATTENDANTS)
	{
		fprintf(stderr, "attendanst limit = %d\n", MAX_ATTENDANTS);
		exit(1);
	}

	soc = mserver_socket( PORT, num);
	if (soc == -1)
	{
		fprintf(stderr, "cannot setup sever\n");
		exit(1);
	}

	maxfd = mserver_maccept(soc, num, enter);

	sessionman_init(num, maxfd);

	sessionman_loop();
}