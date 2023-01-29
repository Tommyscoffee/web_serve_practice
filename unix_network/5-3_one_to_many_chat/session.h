/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:41:21 by akihito           #+#    #+#             */
/*   Updated: 2023/01/29 15:49:18 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/types.h>
#include <curses.h>
#include <signal.h>
#include "tag.h"
#include "sessionman.h"
#include <stdlib.h>

extern void session_init(int soc);

extern void session_loop();
