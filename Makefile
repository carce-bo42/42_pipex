NAME := pipex

SRCS = ./srcs/pipex.c \
	  ./srcs/path_finder.c \
	  ./srcs/stderr_outputs.c \
	  ./srcs/libft_utils_1.c \
	  ./srcs/libft_utils_2.c \
	  ./srcs/libft_utils_3.c

OBJS = ${SRCS:.c=.o}

INC_DIR := ./includes/
EXE_DIR = ./

CC := cc
GCC := gcc
CFLAGS := -Wall -Werror -Wextra
MV := mv -f
RM := rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@ #-fsanitize=address

$(NAME):	$(OBJS) 
	$(CC) -o $(NAME) $^ -I $(INC_DIR) #-fsanitize=address

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
