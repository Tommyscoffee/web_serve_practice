/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akihito <akihito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:16:31 by akihito           #+#    #+#             */
/*   Updated: 2023/01/29 15:52:57 by akihito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "session.h"

int main()
{
	int soc;
	char hostname[HOSTNAME_LENGTH];

	//サーバのホスト名の入力
	// printf("input server's hostname");
	// fgets(hostname, HOSTNAME_LENGTH, stdin);
	// chop_newline(hostname, HOSTNAME_LENGTH,);
	// hostname = "127.0.0.1"; 
	//接続まで
	if((soc = setup_client("127.0.0.1", PORT)) == -1)
	{
		exit(1);
	}

	//セッションモジュールの初期化
	session_init(soc);

	//セッションのループ
	session_loop();
}