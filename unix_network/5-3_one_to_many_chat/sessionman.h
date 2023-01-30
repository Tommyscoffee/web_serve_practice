/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sessionman.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:39:01 by akihito           #+#    #+#             */
/*   Updated: 2023/01/29 16:51:38 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "tag.h"

#define PORT (in_port_t)5552
#define MAX_ATTENDANTS 5

extern void enter();
extern void sessionman_init(int soc, int maxfd);
extern void sessionman_loop();