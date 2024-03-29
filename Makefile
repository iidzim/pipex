# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iidzim <iidzim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/14 10:51:45 by iidzim            #+#    #+#              #
#    Updated: 2021/06/22 09:53:53 by iidzim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	pipex

SRCS			=	./src/pipex.c\
					./src/main.c\
					./src/ft_split.c\
					./src/utils.c

OBJS			= 	${SRCS:.c=.o}

CC				= 	gcc
FLAGS           =  -Wall -Wextra -Werror
RM				= 	rm -f

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) -o $(NAME) $(SRCS) $(FLAGS)

clean:
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY: 		all fclean clean re
