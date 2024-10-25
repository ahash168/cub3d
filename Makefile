# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahashem <ahashem@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 20:07:46 by ahashem           #+#    #+#              #
#    Updated: 2024/10/25 12:41:54 by ahashem          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

SRCCP	=	parsing.c parse_file.c parse_textures.c assign_texture.c assign_colour.c \
			set_colour.c parse_map.c validate_map.c parsing_utils.c

SRCCE	=	hooks.c minimap.c mooooove.c roooootate.c drawing.c loops.c handle_hooks.c \
			rays.c raaaaays.c doors.c

SRCCU	=	error.c close_game.c init_game.c

SRC 	= 	srcs/cub3d.c \
			$(addprefix srcs/parsing/, $(SRCCP)) \
			$(addprefix srcs/execution/, $(SRCCE)) \
			$(addprefix srcs/utils/, $(SRCCU))

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -g3 

# CFLAGS	+=	-fsanitize=address

LIBFT	=	includes/libft/libft.a

MLX		=	includes/mlx/libmlx.a

MLXFLAG	=	-L includes/mlx -lmlx -framework OpenGL -framework AppKit

all		:	$(NAME)

$(LIBFT):
	@$(MAKE)	-C includes/libft

$(MLX):
	@$(MAKE)  -C includes/mlx

$(NAME)	:	$(OBJ) $(LIBFT) $(MLX)
			cc $(CFLAGS) $(OBJ) $(MLXFLAG) -o $@ $(LIBFT) $(MLX)

%.o		:	%.c
			cc $(CFLAGS) -c $< -o $@

clean	:
			$(MAKE) -C includes/libft clean
			rm -rf $(OBJ)

fclean	:	clean
			$(MAKE) -C includes/libft fclean
			$(MAKE) -C includes/mlx clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
