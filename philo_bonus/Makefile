# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 02:15:17 by sthitiku          #+#    #+#              #
#    Updated: 2022/10/29 03:15:21 by sthitiku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = ph_print.c ph_routine.c ph_utils.c philo.c ph_time.c ph_monitor.c

OBJS = $(SRCS:.c=.o)

HEADER = philo_bonus.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	@$(RM) $(OBJS)
	
fclean: clean
	@$(RM) $(NAME)

re: fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS)
	@norminette -R CheckDefine $(HEADER)

.PHONY: all clean fclean re norm
