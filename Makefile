# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hjiang <hjiang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/14 19:35:45 by hjiang            #+#    #+#              #
#    Updated: 2025/04/18 16:20:49 by hjiang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror -g 
CC		= cc

#FILES#
INCLUDE	= -Iinclude
SRC		= $(addprefix src/, command.c pipex.c utils.c ft_split.c)
OBJ		= $(SRC:.c=.o)
#COMPILATION#

all: $(NAME)

$(NAME):  $(OBJ)
	${CC} ${CFLAGS} -g $^ -o $(NAME)

%.o : %.c
	$(CC) ${CFLAGS} -g $(INCLUDE) -c $< -o $@

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re