/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:56:13 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 03:14:04 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "session.h"
#include "sessionman.h"
#include "../mylib/mylib.h"
#include <stdio.h>

int main()
{
	int soc;
	char hostname[HOSTNAME_LENGTH];

	// printf("input server's hostname:");
	// fgets(hostname, HOSTNAME_LENGTH, stdin);
	// chop_newline(hostname, HOSTNAME_LENGTH);

	soc = setup_client("127.0.0.1", PORT);
	if (soc == -1)
		exit(1);
	
	session_init(soc);

	session_loop();
}