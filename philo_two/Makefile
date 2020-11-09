# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qsymond <qsymond@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/03 15:41:33 by qsymond           #+#    #+#              #
#    Updated: 2020/11/03 15:41:34 by qsymond          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
SRCS = main.c philo.c process.c print.c utils.c
OBJS = $(SRCS:.c=.o)
CC = clang
CFLAGS = -Wall -Wextra -Werror
LIB = -lpthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CCFLAGS) -o $(NAME) $(OBJS) $(LIB)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
