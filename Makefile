# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltulune <ltulune@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 18:12:54 by ltulune           #+#    #+#              #
#    Updated: 2021/04/08 18:51:02 by ltulune          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

HEAD = includes/

SRCDIR = srcs/

LIB = lib/

FILES = parse_ambient_light.c parse_camera.c parse_cylinder.c parse_light.c \
	parse_plane.c parse_resolution.c parse_scene.c parse_sphere.c \
	parse_square.c parse_triangle.c parse_utils.c print_error.c \
	get_next_line.c get_next_line_utils.c ft_atof.c rgb_vector.c \
	vector_functions.c ray_tracer.c get_pixel_color.c intersect_sphere.c \
	compute_light_intensity.c intersect_plane.c intersect_triangle.c main.c \
	intersect_square.c intersect_cylinder.c intersect_cylinder2.c \
	rotation.c save_bmp.c vector_functions2.c handle_key.c \

SRCS = $(addprefix $(SRCDIR), $(FILES))

OBJS = ${SRCS:.c=.o}

CC = gcc -g

RM = rm -f

CFLAGS = -I $(HEAD) -Wall -Wextra -Werror

FLAGS = -L $(LIB)libft -lft

MACOS_FLAGS	= libmlx.dylib -framework Metal -framework AppKit

$(NAME) : $(OBJS) $(HEAD)*.h
	@make -C $(LIB)libft all
	@make -C $(LIB)mlx_mms
	@mv $(LIB)/mlx_mms/libmlx.dylib libmlx.dylib
	${CC} ${CFLAGS} $(OBJS) $(FLAGS) $(MACOS_FLAGS) -o ${NAME}

%.o: %.c $(HEAD)
	$(CC) -c  $< -o $@ -I$(HEAD)

all: ${NAME}

clean:
	make clean -C $(LIB)libft
	make clean -C $(LIB)mlx_mms
	${RM} ${OBJS}
	$(RM) libmlx.dylib

fclean: clean
	${RM} ${NAME}
	make fclean -C $(LIB)libft


re: fclean all

bonus: all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCDIR)*.c $(HEAD)*.h

.PHONY: all clean fclean re norme bonus
