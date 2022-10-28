# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 02:29:05 by sthitiku          #+#    #+#              #
#    Updated: 2022/10/29 03:24:50 by sthitiku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

M_DIR = ./philo
B_DIR = ./philo_bonus

all:
	@echo $(M_DIR)
	@make -C $(M_DIR)
	@echo " "
	@echo $(B_DIR)
	@make -C $(B_DIR)

bonus: all

clean:
	@make clean -C $(M_DIR)
	@make clean -C $(B_DIR)

fclean: clean
	@make fclean -C $(M_DIR)
	@make fclean -C $(B_DIR)

re: fclean all

norm:
	@echo $(M_DIR)
	@make norm -C $(M_DIR)
	@echo " "
	@echo $(B_DIR)
	@make norm -C $(B_DIR)

.PHONY: all bonus clean fclean re