NAME := pipex
NAME_BONUS := pipex_bonus

SRCS = ./srcs/main.c \
	  ./srcs/path_finder.c \
	  ./srcs/stderr_outputs.c \
	  ./srcs/libft_utils_1.c \
	  ./srcs/libft_utils_2.c \
	  ./srcs/libft_utils_3.c

SRCS_BONUS = ./srcs/main_bonus.c \
			 ./srcs/path_finder.c \
			 ./srcs/stderr_outputs.c \
			 ./srcs/libft_utils_1.c \
			 ./srcs/libft_utils_2.c \
			 ./srcs/libft_utils_3.c \
			 ./srcs/several_pipe_handling_bonus.c \
			 ./srcs/get_next_line_bonus.c \
			 ./srcs/get_next_line_utils_bonus.c

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

INC_DIR := ./includes/
EXE_DIR = ./

CC := cc
GCC := gcc
CFLAGS := -Wall -Werror -Wextra
MV := mv -f
RM := rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I $(INC_DIR) -o $@ -fsanitize=address

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $^ -I $(INC_DIR) -fsanitize=address

$(NAME_BONUS):	$(OBJS_BONUS)
	$(CC) -o $(NAME_BONUS) $^ -I $(INC_DIR) -fsanitize=address
	
bonus:	$(NAME_BONUS)

all: $(NAME)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: clean all

.PHONY: all clean fclean re
