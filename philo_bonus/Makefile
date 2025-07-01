# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/27 18:55:50 by oelleaum          #+#    #+#              #
#    Updated: 2025/06/27 18:55:53 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC = src/philo_bonus.c \
			src/threads.c \
			src/philo_process.c \
			src/utils/str_utils_bonus.c \
			src/utils/time_bonus.c \
			src/utils/cleanup.c \
			src/utils/getters_setters.c \
			src/init_bonus.c \
			src/init_semaphores_bonus.c
			# src/init/init_bonus.c \
			# src/init/init_data_utils_bonus.c \
			# src/utils/prints_bonus.c \
			# src/utils/free_destroy_utils.c \
			# src/utils/time.c \
			# src/utils/getters.c \
			# src/utils/setters.c \
			# src/philosophers_routine.c \
			# src/forks.c \
			# src/monitor_routine.c

CC = cc
FLAGS = -Wall -Werror -Wextra #-g3 -lpthread
NAME = philo_bonus
INC = include

# make re && valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --show-reachable=yes ./bin/philo_bonus 5 800 200 200 7
# gdb : au blocage : thread apply all bt

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = .objs

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) Makefile include/philo_bonus.h $(SRC)
	mkdir -p bin
	$(CC) $(FLAGS) $(OBJ) -I $(INC) -o bin/$(NAME)
	@echo 
	@echo "$(GREEN)compilation successful ✅ $(NAME)$(RESET)"
	@echo 
	
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re : fclean all

# FORCE:
.PHONY: all re clean fclean
