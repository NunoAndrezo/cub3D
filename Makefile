NAME		=	cub3D

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -g -I/usr/include -Imlx_linux

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
SRC_FILES	=	main.c parsing.c initiate_game.c map_validation.c \
				handle_map.c get_next_line.c get_next_line_utils.c \
				ft_bzero.c ft_calloc.c utils.c setup_signals.c \
				flood_fill.c free_me_baby.c raycasting.c ft_memcpy.c \
				my_math.c drawing_3d_game.c ft_split.c ft_atoi.c \
				ft_strncmp.c start_time.c start_gaming.c mlx_events.c \
				2D_drawing.c handle_player_mov_and_rot.c load_game.c \
				strip_newline.c raycasting_utils.c rgb_to_color.c \
				drawing_3d_game_utils.c handle_map_support.c \
				free_me_baby2.c initiate_game_utils.c key_utils.c \
				map_validation_utils.c 2D_drawing_utils.c handle_map_support2.c \
				handle_map_support3.c handle_player_mov_and_rot_helper.c \
				handle_map_support4.c

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
	@if [ -d "minilibx-linux/obj" ]; then rm -rf minilibx-linux/obj; echo "$(BLUE)Deleting minilibx objects...$(RESET)"; else echo "No minilibx objects to remove."; fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then rm -f $(NAME); echo "$(BLUE)Deleting $(NAME)...$(RESET)"; else echo "No Executable to remove."; fi;
	@if [ -f minilibx-linux/libmlx.a ]; then rm -f minilibx-linux/libmlx.a; echo "$(BLUE)Deleting libmlx.a...$(RESET)"; else echo "No libmlx.a to remove."; fi;
	@if [ -f minilibx-linux/libmlx_Linux.a ]; then rm -f minilibx-linux/libmlx_Linux.a; echo "$(BLUE)Deleting libmlx_Linux.a...$(RESET)"; else echo "No libmlx_Linux.a to remove."; fi;

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re
