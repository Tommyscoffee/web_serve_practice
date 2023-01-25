/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mylib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 20:37:36 by atomizaw          #+#    #+#             */
/*   Updated: 2023/01/22 20:37:37 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

extern int setup_server(in_port_t port);
extern int setup_client(char *hostname, in_port_t port);
extern int mserver_socket(in_port_t port, int num);
extern int mserver_maccept(int soc, int limit, void (*func)());
extern char *chop_newline(char *buf, int len);


