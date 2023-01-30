# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akihito <akihito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 16:41:47 by atomizaw          #+#    #+#              #
#    Updated: 2023/01/30 15:28:52 by akihito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = setup_client.o setup_server.o chop_newline.o setup_mserver.o
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