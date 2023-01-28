# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akihito <akihito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 14:07:13 by akihito           #+#    #+#              #
#    Updated: 2023/01/28 14:59:28 by akihito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MYLIBDIR = ../mylib
MYLIB = $(MYLIBDIR)/mylib.a
CFLAGS = -I$(MYLIBDIR)

all: s c

s: server.o session.o
	$(CC) -o $@ $^ $(MYLIB) -lcurses

c: client.o session.o
	$(CC) -o $@ $^ $(MYLIB) -lcurses

server.o client.o: tag.h session.h

clean:
	$(RM) s c *.o *~

fclean: clean 

mylib_clean:
	make -C $(MYLIBDIR) clean
mylib:
	make -C $(MYLIBDIR)
re: mylib_clean fclean mylib all