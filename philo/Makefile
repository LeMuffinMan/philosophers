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

SRC = src/philo.c \
			src/init/init_mutex_utils.c \
			src/init/init_forks.c \
			src/init/init.c \
			src/init/init_data_utils.c \
			src/init/init_philo_struct.c \
			src/utils/prints.c \
			src/utils/str_utils.c \
			src/utils/free_destroy_utils.c \
			src/utils/time.c \
			src/philosophers_routine.c \
			src/forks.c \
			src/monitor_routine.c

CC = cc
FLAGS = -Wall -Werror -Wextra -g3 -pthread #-fsanitize=thread
NAME = philo
INC = include

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = .objs

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) Makefile include/philo.h $(SRC)
	mkdir -p bin
	$(CC) $(FLAGS) $(OBJ) -I $(INC) -o bin/$(NAME)
	@echo 
	@echo "$(GREEN)compilation successful ✅ $(NAME)$(RESET)"
	@echo 
	
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

#bonus

clean: 
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re : fclean all

# FORCE:
.PHONY: all re clean fclean #bonus
