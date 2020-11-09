# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 14:13:16 by qsymond           #+#    #+#              #
#    Updated: 2020/11/03 14:31:16 by qsymond          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRCS = main.c philosopher.c process.c print.c utils.c
OBJS = $(SRCS:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIB = -lpthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
