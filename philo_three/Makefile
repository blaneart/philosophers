# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablanar <ablanar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/23 19:37:51 by ablanar           #+#    #+#              #
#    Updated: 2020/03/04 18:40:56 by ablanar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo_three

SRC =	ft_itoa.c ft_strncmp.c main.c monitor.c print_out.c\
		processes.c ft_memcpy.c parse.c
OBJS =	$(SRC:.c=.o)

CC =	gcc

CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	gcc -o $(NAME) $(OBJS) $(CFLAGS)
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all
