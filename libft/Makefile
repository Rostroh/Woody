# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rostroh <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 18:41:32 by rostroh           #+#    #+#              #
#    Updated: 2022/09/16 13:24:55 by rostroh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	  ft_isprint.c ft_itoa.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c\
	  ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c\
	  ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
	  ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c \
	  ft_strcmp.c ft_strcpy.c ft_strctrim.c ft_strdel.c ft_strdup.c ft_strequ.c\
	  ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c \
	  ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
	  ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strrev.c \
	  ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
	  ft_toupper.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	  ft_lstmap.c ft_isspace.c ft_islower.c ft_isupper.c ft_long_itoa.c \
	  ft_getopt.c print_byte.c \
	  printf/binary_to_decimal.c printf/condition.c printf/conv.c \
	  printf/ft_printf.c printf/ft_putwchar.c printf/gestion.c \
	  printf/gestion_print.c printf/get_base.c printf/more_shitty_fonction.c \
	  printf/params.c printf/print.c printf/shitty_fonction.c printf/space.c \
	  printf/wchar_fonction.c

HEAD = libft.h
OBJ = $(SRC:.c=.o)

SRC_DIR = ./src
OBJ_DIR = ./obj
HEAD_DIR = ./include

SRCS = $(SRC:%=$(SRC_DIR)/%)
OBJS = $(OBJ:%=$(OBJ_DIR)/%)

INC = $(HEAD_DIR)/$(HEAD)

OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

FLG = -Wall -Werror -Wextra #-fsanitize=address -g3

all:
	@mkdir -p ./obj
	@mkdir -p ./obj/printf
	@make $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(FLG) -I $(HEAD_DIR) -o $@ -c $<

$(NAME): $(OBJ_PATH)
	@echo creat $(NAME)
	@ar rc $@ $(OBJ_PATH)

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f libft.h.gch

fclean: clean
	@rm -f $(NAME)

re: fclean all

print-%:
	@echo $*= $($*)
