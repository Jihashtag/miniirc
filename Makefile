# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbert <jbert@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/09/23 15:42:25 by jbert             #+#    #+#              #
#    Updated: 2016/01/10 13:29:19 by jbert            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SNAME = serveur
CNAME = client

SSRCS =	main.c fct.c opt.c opt_bis.c sock.c
CSRCS =	main2.c

SOBJS = ${SSRCS:.c=.o}
COBJS = ${CSRCS:.c=.o}

CFLAGS = -g3 -Wextra -Wall -Werror

CC = gcc
RM = rm -f

.SILENT:

$(CNAME):	${COBJS}
		make -C libftprintf/
		$(CC) $(CFLAGS) -o $(CNAME) $(COBJS) libftprintf/libftprintf.a

$(SNAME):	${SOBJS}
		make -C libftprintf/
		$(CC) $(CFLAGS) -o $(SNAME) $(SOBJS) libftprintf/libftprintf.a

all:	$(SNAME) $(CNAME)

clean:
		$(RM) $(COBJS) $(SOBJS)
		make clean -C libftprintf/

fclean:
		$(RM) $(SOBJS) $(SNAME) $(COBJS) $(CNAME)
		make fclean -C libftprintf/

re:		fclean all

.PHONY: SNAME CNAME all clean fclean re
