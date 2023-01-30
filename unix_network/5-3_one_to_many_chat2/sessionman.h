/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sessionman.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:41:57 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 03:03:15 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#define	PORT (in_port_t)5552
#define MAX_ATTENDANTS 5
#define BUF_LEN 80

extern void enter();
extern void sessionman_init(int  num, int maxfd);
extern void sessionman_loop();
