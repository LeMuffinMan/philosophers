# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelleaum <oelleaum@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 18:18:26 by oelleaum          #+#    #+#              #
#    Updated: 2025/07/02 09:05:32 by oelleaum         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INC) # -g3
LDFLAGS = -lpthread

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
      src/utils/getters.c \
      src/utils/setters.c \
      src/philosophers_routine.c \
      src/forks.c \
      src/monitor_routine.c

NAME = philo
INC = include
OBJ_DIR = .objs
BIN_DIR = bin

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
RESET = \033[0m

all: $(BIN_DIR)/$(NAME)

$(BIN_DIR)/$(NAME): $(OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@
	@echo "\n$(GREEN)Compilation successful ✅ $(NAME)$(RESET)\n"

$(OBJ_DIR)/%.o: %.c include/philo.h | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

re: fclean all

.PHONY: all re clean fclean
