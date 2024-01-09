# Makefile for fract-ol
# Author: Bobbie Syvasalmi
# Version 1.0
# Date: 27/11/2023

NAME = fractol

HEADER = fractol.h
LIB = libft/libft.a
LIBDIR = ./libft
SRC = fractol.c events.c set.c
OBJ = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -L$(LIBDIR) -lft -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(LIB):
	make -C $(LIBDIR)

clean:
	@rm -rf *.o
	@make -C $(LIBDIR) clean

fclean: clean
	@rm -f fractol
	@rm -f $(LIB)
	
re: fclean all

.phony:: all clean fclean re