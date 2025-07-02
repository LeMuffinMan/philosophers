# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/27 18:55:50 by oelleaum          #+#    #+#              #
#    Updated: 2025/07/02 06:55:35 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(INC) # -g3
LDFLAGS = -lpthread

INC = include
SRC = src/philo_bonus.c \
      src/threads_bonus.c \
      src/philo_process_bonus.c \
      src/forks_bonus.c \
      src/utils/str_utils_bonus.c \
      src/utils/time_bonus.c \
      src/utils/prints_bonus.c \
      src/utils/philo_routine_utils_bonus.c \
      src/utils/init_semaphores_utils_bonus.c \
      src/utils/close_unlink_free_bonus.c \
      src/utils/getters_setters_bonus.c \
      src/init/init_bonus.c \
      src/init/init_semaphores_bonus.c

NAME = philo_bonus

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = .objs

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o bin/$(NAME)
	@echo
	@echo "$(GREEN)Compilation successful ✅ $(NAME)$(RESET)"
	@echo

$(OBJ_DIR)/%.o: %.c include/philo_bonus.h Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf bin

re: fclean all

.PHONY: all re clean fclean
