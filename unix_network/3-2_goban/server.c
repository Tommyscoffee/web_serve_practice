/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomizaw <atomizaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:26:17 by atomizaw          #+#    #+#             */
/*   Updated: 2023/01/24 18:57:04 by atomizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "goban.h"

int main()
{
	int soc;//ソケットディスクりぷた
	char my_stone='o';
	char peer_stone='x';

	//接続完了まで
	if((soc = setup_server(PORT)) == -1)
		exit(1);
	printf("%d\n", __LINE__);
	//碁盤の初期化
	goban_init(soc, my_stone, peer_stone);

	printf("%d\n", __LINE__);
	//ループ
	while(1)
	{
		//相手の番
		goban_show();
		printf("Wait\n");
		if( goban_peer_turn() == -1)
			break;

		//自分の番
		goban_show();
		printf("Go ahead\n");
		if( goban_my_turn() == -1 )
			break;
	}
	//終了処理
	goban_destroy();
}