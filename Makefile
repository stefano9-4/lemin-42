# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lutomasz <lutomasz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/01 18:00:07 by lutomasz          #+#    #+#              #
#    Updated: 2020/02/01 12:19:38 by spozzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in

SRC_NAME = lemin.c parse.c utils.c hashmap.c bfs.c bellmanFord.c \
			suurballe.c

SRC_PATH = src/
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))

FLAGS = #-Wall -Wextra -Werror

HEADERS = ./header
HEAD = header/lemin.h

LIBFT_PATH = includes/libft/
LIBFT = $(addprefix $(LIBFT_PATH), libft.a)

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = obj/
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(HEAD) $(OBJ)
	@gcc $(FLAGS) -o $@ $(OBJ) -L $(LIBFT_PATH) -lft
	@echo "\n\033[1;32m---------->[LEM_IN IS READY]<----------- \033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	@mkdir -p obj
	gcc $(FLAGS) -o $@ -c $< -I $(HEADERS)

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "\n\033[1;31m---------->[.O REMOVED]<----------- \033[0m"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "\n\033[1;31m----------->[LEM_IN REMOVED]<-------- \033[0m"

re: fclean all

.PHONY : fclean clean all re
