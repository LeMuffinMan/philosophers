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
			src/init.c \
			src/utils/prints.c \
			src/utils/str_utils.c 

CC = cc
FLAGS = -Wall -Werror -Wextra -g3 
NAME = philo
INC = include

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = .objs

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) Makefile include/philo.h src/philo.c #ajouter ici 
	$(CC) $(FLAGS) $(OBJ) -I $(INC) -o $(NAME)
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

re : flcean all

#FORCE:
.PHONY: all re clean fclean #bonus
