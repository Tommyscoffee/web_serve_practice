# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atomizaw <atomizaw@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 16:41:47 by atomizaw          #+#    #+#              #
#    Updated: 2023/01/23 17:10:44 by atomizaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = setup_client.o setup_server.o chop_newline.o
AR = ar -qc

mylib.a: $(OBJS)
	$(RM) $@
	$(AR) $@ $(OBJS)
$(warning AR = $(AR))
$(warning OBJS = $(OBJS))
$(OBJS):	mylib.h

clean:
	$(RM) *.o mylib.a

re: clean mylib.a