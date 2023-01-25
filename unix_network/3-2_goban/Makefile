# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atomizaw <atomizaw@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 16:47:47 by atomizaw          #+#    #+#              #
#    Updated: 2023/01/23 17:46:27 by atomizaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MYLIBDIR = ../mylib
MYLIB = $(MYLIBDIR)/mylib.a
CFLAGS = -I $(MYLIBDIR)
# include $(MYLIBDIR)/Makefile
all:mylib s c 
s: server.o goban.o 
	$(CC) -o $@ $^ $(MYLIB) -fsanitize=address

c: client.c goban.o 
	$(CC) -o $@ $^ $(MYLIB) -fsanitize=address

server.o client.o: goban.h

clean:
	$(RM) s c *.o *~

fclean: clean 

mylib_clean:
	make -C $(MYLIBDIR) clean
mylib:
	make -C $(MYLIBDIR)
re: mylib_clean fclean mylib all
