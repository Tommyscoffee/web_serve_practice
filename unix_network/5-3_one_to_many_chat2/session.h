/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   session.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:58:25 by akihito           #+#    #+#             */
/*   Updated: 2023/01/30 03:11:48 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "sessionman.h"

#define HOSTNAME_LENGTH 64

extern void session_init(int soc);
extern void session_loop();
