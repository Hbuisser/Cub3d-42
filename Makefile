# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbuisser <hbuisser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/25 12:47:05 by hbuisser          #+#    #+#              #
#    Updated: 2020/03/11 15:20:02 by hbuisser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= cub3D
LIBFT_PATH 		= ./libft
MINILIBX_PATH   = ./miniLibX
SRCS 			= ./srcs/main.c \
					./parse/parse.c \
					./parse/parse2.c \
					./parse/get_elements.c \
					./parse/get_elem_resolution.c \
					./parse/get_elem_floor.c \
					./parse/get_elem_ceilling.c \
					./parse/get_textures.c \
					./parse/get_sprites.c \
					./parse/check_elements_errors.c \
					./parse/check_map_errors.c \
					./parse/check_map_errors2.c \
					./srcs/keycode.c \
					./srcs/init.c \
					./srcs/init2.c \
					./srcs/textures.c \
					./srcs/main_algo.c \
					./srcs/sprites.c \
					./srcs/sprites2.c \
					./srcs/exit.c \
					./srcs/exit2.c \
					./srcs/bmp.c 
OBJS			= ${SRCS:.c=.o}
INCLUDE 		= cube3d.h
LIBFT 			= libft
MINILIBX 		= miniLibX
CC				= gcc -g -Wall -Wextra -Werror #-fsanitize=address
RM				= rm -f
MLXFLAGS 		= -I ./miniLibX -L ./miniLibX -lmlx -framework OpenGl -framework Appkit
LIBFLAGS 		= -I ./libft -L ./libft -L . ./libft/*.c 
# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking

all:			libft_all minilibx_all ${NAME}
$(NAME):		${OBJS} 
				@$(CC) $(MLXFLAGS) $(LIBFLAGS) libft.a libmlx.a -I./ $(OBJS) -o $@ 
clean:			libft_clean minilibx_clean
				@${RM} ${OBJS}
fclean:			libft_fclean clean
				@${RM} ${NAME}
re:				fclean all

# make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
libft_all:
	make -C $(LIBFT_PATH) all
	cp ./libft/libft.a libft.a

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft.a

minilibx_all:
	make -C $(MINILIBX_PATH) all
	cp ./minilibX/libmlx.a libmlx.a

minilibx_clean:
	make -C $(MINILIBX_PATH) clean
	$(RM) libmlx.a
				
.PHONY: all fclean clean re
