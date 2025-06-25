# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 18:18:26 by oelleaum          #+#    #+#              #
#    Updated: 2025/06/01 19:40:43 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC = src/philo_bonus.c \
			src/utils/str_utils_bonus.c \
			src/utils/time_bonus.c \
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
FLAGS = -Wall -Werror -Wextra -g3 #-lpthread -fsanitize=thread
NAME = philo_bonus
INC = include

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
