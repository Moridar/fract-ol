# Makefile for fract-ol
# Auother: Bobbie Syvasalmi
# Version 1.0
# Date: 27/11/2023

NAME = fractol

SRC = fractol.c events.c set.c
OBJ = $(SRC:%.c=%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJ)
	$(CC) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)


clean:
	rm -rf *.o

fclean: clean
	rm fractol