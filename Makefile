# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 10:51:45 by iidzim            #+#    #+#              #
#    Updated: 2021/06/14 10:56:31 by iidzim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

SRCS			=	./pipex.c

OBJS			= 	${SRCS:.c=.o}

INCLUDE 		= 	-I includes -L includes
CC				= 	gcc
FLAGS           =  -Wall -Wextra -Werror -g -fsanitize=address
RM				= 	rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) -o $(NAME) $(SRCS) $(INCLUDE) $(FLAGS)

clean:			@$(RM) $(OBJS)

fclean:			@$(RM) $(NAME)

re:				fclean all

.PHONY: 		all fclean clean re
