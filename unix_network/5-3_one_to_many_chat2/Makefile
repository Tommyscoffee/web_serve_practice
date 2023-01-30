# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akihito <akihito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 14:07:13 by akihito           #+#    #+#              #
#    Updated: 2023/01/30 02:59:58 by akihito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MYLIBDIR = ../mylib
MYLIB = $(MYLIBDIR)/mylib.a
OBJS1 = server.o sessionman.o
OBJS2 = client.o session.o
CFLAGS = -I$(MYLIBDIR)

all: s c

s: $(OBJS1)
	$(CC) -o $@ $^ $(MYLIB) -lcurses

c: $(OBJS2)
	$(CC) -o $@ $^ $(MYLIB) -lcurses

server.o: sessionman.h

client.o: session.h

clean:
	$(RM) s c $(OBJS1) $(OBJS2) *~

fclean: clean 

mylib_clean:
	make -C $(MYLIBDIR) clean
mylib:
	make -C $(MYLIBDIR)
re: mylib_clean fclean mylib all