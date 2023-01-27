/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:39:01 by akihito           #+#    #+#             */
/*   Updated: 2023/01/27 15:51:32 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <curses.h>
#include <signal.h>
#include "tag.h"
extern void session_init(int soc,
						char mc, int mx, int my,
						char pc, int px, int py);

extern void session_loop();
