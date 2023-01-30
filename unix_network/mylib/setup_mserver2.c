/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mserver2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:28:08 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 00:42:25 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mylib.h"

int mserver_socket(in_port_t port, int backlog)
{
	struct sockaddr_in  me;
	int soc_waiting;

	memset((char *)&me, 0, sizeof(me));
	me.sin_family = AF_INET;
	me.sin_addr.s_addr = htonl(INADDR_ANY);
	me.sin_port = htons(port);

	soc_waiting = socket(AF_INET, SOCK_STREAM, 0);
	if (soc_waiting < 0)
	{
		perror("socket");
		return (-1);
	}

	int bind_res;
	bind_res = bind(soc_waiting, (struct sockaddr *)&me, sizeof(me));

	if ( bind_res == -1)
	{
		perror("bind");
		return (-1);
	}

	int listen_res = listen(soc_waiting, backlog);
	if (listen_res == -1)
	{
		perror("listen");
		return (-1);
	}

	fprintf(stderr, "successfully setup, now waitin\n");

	return soc_waiting;
}

int mserver_maccept(int soc_waiting, int limit, void (*func)())
{
	int i;
	int fd;

	for(i = 0; i < limit; i++)
	{
		fd = accept(soc_waiting, NULL, NULL);
		if (fd == -1)
		{
			fprintf(stderr, "accept error\n");
			return (-1);
		}
		(*func)(i, fd);
	}

	close(soc_waiting);

	return fd;
}