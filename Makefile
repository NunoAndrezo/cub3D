NAME		=	cub3d

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -g -lm -I/usr/include -Imlx_linux

PRINTF		= ./printf/libftprintf.a
LIBFT		= ./libft/libft.a
LIBMLX		= ./minilibx-linux/libmlx_Linux.a


# directories
SRC_DIR		=	src/
OBJ_DIR		=	obj/
INC_DIR		=	inc/

# color codes
RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
UP			=	\033[A
CUT			=	\033[K

#source files
SRC_FILES	=	main.c parsing.c initiate.c map_validation.c \
				handle_map.c get_next_line.c get_next_line_utils.c \
				ft_bzero.c ft_calloc.c utils.c


OBJ_FILES	=	$(SRC_FILES:.c=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

#all rule
all: $(NAME)

#compile the executable
$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@$(MAKE) -s -C minilibx-linux
#-s to silent/surpress output
	@$(CC) $(CFLAGS) $(OBJ) $(LIBMLX) -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then rm -rf $(OBJ_DIR); echo "$(BLUE)Deleting all objects...$(RESET)"; else echo "No objects to remove."; fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then rm -f $(NAME); echo "$(BLUE)Deleting $(NAME)...$(RESET)"; else echo "No Executable to remove."; fi;
	@if [ -f minilibx-linux/libmlx.a ]; then rm -f minilibx-linux/libmlx.a; echo "$(BLUE)Deleting libmlx.a...$(RESET)"; else echo "No libmlx.a to remove."; fi;
	@if [ -f minilibx-linux/libmlx_Linux.a ]; then rm -f minilibx-linux/libmlx_Linux.a; echo "$(BLUE)Deleting libmlx_Linux.a...$(RESET)"; else echo "No libmlx_Linux.a to remove."; fi;

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re
