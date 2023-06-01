NAME = ./woody_woodpacker

SRC = main.c error_input.c parser.c woody.c elf.c code_cave.c expand.c creat_segment.c
SRC_ASM = rc4.asm

OBJ = $(SRC:.c=.o)

SRC_DIR = ./srcs
OBJ_DIR = ./objs
INC_DIR = ./include
ASM_DIR = $(SRC_DIR)/rc4

OBJS = $(OBJ:%=$(OBJ_DIR)/%)

INC = woody.h

HEAD = $(INC_DIR)/$(INC)

LIBFT = libft.a
LIB_DIR = ./libft
LFT = $(LIB_DIR)/$(LIBFT)
LIB = -L $(LIB_DIR) -l$(LIBFT:lib%.a=%)

#OBJ_PATH = $(addprefix $(OBJ_DIR)/,$(SRC":.c=.o))

FLG = -Wno-format #-Wall -Werror -Wextra

CC = gcc

all:
	@make -C $(LIB_DIR)
	@make $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(FLG) -I $(INC_DIR) -o $@ -c -fPIC $<

$(OBJS): $(HEAD)

$(NAME): $(OBJS)
	#echo $(OBJS)
	#echo $(OBJ_PATH)
	rm -rf woody
	#$(CC) $(FLG) $(OBJS) -lm -o $@ $(LIB)
	nasm -felf64 $(ASM_DIR)/$(SRC_ASM)
	clang $(ASM_DIR)/rc4.o $(OBJS) -o $@ $(LIB)

clean:
	@rm -rf $(OBJ_DIR)
	@make $@ -C $(LIB_DIR)

fclean: clean
	@rm -rf $(NAME)
	@make $@ -C $(LIB_DIR)

re: fclean all

