# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbeaudoi <tbeaudoi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 16:52:32 by tbeaudoi          #+#    #+#              #
#    Updated: 2022/07/12 15:23:52 by tbeaudoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
RM = rm -f

NAME_C = client
NAME_S = server

SRC_C = src/client.c
SRC_S = src/server.c
OBJ_C = $(SRC_C:.c=.o)
OBJ_S = $(SRC_S:.c=.o)


PRINTF = include/printf/libftprintf.a
PRINTF_PATH = include/printf/

				
all: client server

client: $(SRC_C) $(OBJ_C)
		$(MAKE) -C $(PRINTF_PATH)
		$(CC) $(CFLAGS) -o $(NAME_C) $(SRC_C) $(PRINTF)

server: $(SRC_S) $(OBJ_S) 
		$(CC) $(CFLAGS) -o $(NAME_S) $(SRC_S) $(PRINTF)

clean:
		$(RM) $(OBJ_C) $(OBJ_S)
		make -C $(PRINTF_PATH) clean

fclean: clean
		$(RM) $(NAME_C) $(NAME_S) $(PRINTF)

re: fclean all