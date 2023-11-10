# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:00:42 by mflores-          #+#    #+#              #
#    Updated: 2023/11/10 17:07:40 by mflores-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#	GENERAL																	   #
#------------------------------------------------------------------------------#
NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror -g
RM = rm -f

#------------------------------------------------------------------------------#
#	HEADER FILES															   #
#------------------------------------------------------------------------------#
HEADER_FILES = cub3d
HEADER_PATH = includes/
HEADER = $(addsuffix .h, $(addprefix $(HEADER_PATH), $(HEADER_FILES)))
HEADER_INC = $(addprefix -I, $(HEADER_PATH) $(LIB_HEADER_PATH) \
								$(LIBLIST_HEADER_PATH) /usr/include/$(MLX_HEADER_PATH))

#------------------------------------------------------------------------------#
#	LIBFT																	   #
#------------------------------------------------------------------------------#
LIB_NAME = ft
LIB_PATH = libft/
LIB = -L$(LIB_PATH) -l$(LIB_NAME)
LIB_HEADER_PATH = $(LIB_PATH)includes/

#------------------------------------------------------------------------------#
#	LIBLIST																	   #
#------------------------------------------------------------------------------#
LIBLIST_NAME = ftlist
LIBLIST_PATH = list/
LIBLIST = -L$(LIBLIST_PATH) -l$(LIBLIST_NAME)
LIBLIST_HEADER_PATH = $(LIBLIST_PATH)

#------------------------------------------------------------------------------#
#	MINILIBX																   #
#------------------------------------------------------------------------------#
MLX_HEADER_FILES = mlx mlx_init
MLX_HEADER_PATH	= $(addsuffix .h, $(addprefix $(MLX_PATH), $(MLX_HEADER_FILES)))
MLX_NAME = mlx
MLX_PATH = mlx/
MLX_FLAGS = -lXext -lX11 -lm -lz
MLX = -L$(MLX_PATH) -l$(MLX_NAME) $(MLX_FLAGS) 

#------------------------------------------------------------------------------#
#	CUB3D FILES																   #
#------------------------------------------------------------------------------#
# List of all .c source files
ROOT_FILES = main

INIT_FILES = init
INIT_FOLDER = init/

PARSING_FILES = parsing check_file textures colors parsing_utils fill_map \
				check_map map_utils
PARSING_FOLDER = parsing/

UTILS_FILES = exit_utils
UTILS_FOLDER = utils/

GAME_FOLDER = game/
GAME_FILES = game map player_movement player_rotation player map_calc map_utils

SCREEN_FOLDER = screen/
SCREEN_FILES = screen

TEXTURES_FOLDER = textures/
TEXTURES_FILES = textures

SRCS_PATH = srcs/
SRCS_FILES = $(addsuffix .c, $(ROOT_FILES) \
						$(addprefix $(PARSING_FOLDER), $(PARSING_FILES)) \
						$(addprefix $(UTILS_FOLDER), $(UTILS_FILES)) \
						$(addprefix $(INIT_FOLDER), $(INIT_FILES)) \
						$(addprefix $(GAME_FOLDER), $(GAME_FILES)) \
						$(addprefix $(SCREEN_FOLDER), $(SCREEN_FILES)) \
						$(addprefix $(TEXTURES_FOLDER), $(TEXTURES_FILES))) 

# All .o files go to objs directory
OBJS_NAMES	= $(SRCS_FILES:.c=.o)
OBJS_FOLDER = $(addprefix $(OBJS_PATH), $(PARSING_FOLDER) $(UTILS_FOLDER) \
										$(GAME_FOLDER) $(SCREEN_FOLDER) \
										$(TEXTURES_FOLDER) $(INIT_FOLDER)) 
OBJS_PATH = objs/
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAMES))

# Gcc/Clang will create these .d files containing dependencies
DEPS = $(OBJS:.o=.d)

#------------------------------------------------------------------------------#
#	BASCIC RULES															   #
#------------------------------------------------------------------------------#
all: header $(NAME)
	@echo "\n$(BOLD)$(GREEN)[ ✔ ]\tCUB3D$(RESET)"
	@echo "$(BOLD)\n▶ TO LAUNCH:\t./$(NAME) map_file.cub\n$(RESET)"

# Actual target of the binary - depends on all .o files
$(NAME): lib liblist mlx $(HEADER) $(OBJS)
# Link all the object files
	@$(CC) $(FLAGS) $(HEADER_INC) $(OBJS) $(LIB) $(LIBLIST) $(MLX) -o $(NAME)
# Build target for every single object file
# The potential dependency on header files is covered
# by calling `-include $(DEPS)`
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
# Create objs directory
	@mkdir -p $(OBJS_FOLDER)
  # The -MMD flags additionaly creates a .d file with
  # the same name as the .o file.
	@$(CC) $(FLAGS) $(HEADER_INC) -MMD -MP -o $@ -c $<
	@printf "$(YELLOW). . . compiling $(NAME) objects . . . => $(ITALIC)$(GREY)%-33.33s\r$(RESET)" $@

lib:
	@$(MAKE) --no-print-directory -C $(LIB_PATH)
	@echo "\n$(BOLD)$(GREEN)[ ✔ ]\tLIBFT$(RESET)"

liblist:
	@$(MAKE) --no-print-directory -C $(LIBLIST_PATH)
	@echo "\n$(BOLD)$(GREEN)[ ✔ ]\tLIBLIST$(RESET)"

mlx: $(MLX_PATH)
	@if [ ! -e "$(MLX_PATH)lib$(MLX_NAME).a" ]; then \
		echo "$(YELLOW). . . compiling Minilibx . . . $(RESET)"; \
		chmod +rx $(MLX_PATH)configure ; \
		$(MAKE) --no-print-directory -sC $(MLX_PATH); \
	fi
	@echo "$(BOLD)$(GREEN)[ ✔ ]\tMINILIBX$(RESET)"

clean:
	@if [ -d "$(OBJS_PATH)" ]; then \
		echo "$(YELLOW). . . cleaning objects . . .$(RESET)"; \
		$(MAKE) --no-print-directory clean -C $(LIB_PATH); \
		$(MAKE) --no-print-directory clean -sC $(MLX_PATH); \
		$(MAKE) --no-print-directory clean -C $(LIBLIST_PATH); \
		$(RM) -rd $(OBJS_PATH); \
	fi
	@echo "$(BOLD)$(GREEN)[ ✔ ]\tOBJECTS CLEANED$(RESET)"

fclean:	clean
	@if [ -e $(NAME) ]; then \
		echo "$(YELLOW). . . cleaning rest . . .$(RESET)"; \
		$(MAKE) --no-print-directory fclean -C $(LIB_PATH); \
		$(MAKE) --no-print-directory fclean -C $(LIBLIST_PATH); \
		$(RM) $(NAME); \
	fi
	@echo "$(BOLD)$(GREEN)[ ✔ ]\tALL CLEANED$(RESET)"

re:	fclean all

# Include all .d files
-include $(DEPS)

.PHONY:	all clean fclean re header norme check lib liblist mlx

#------------------------------------------------------------------------------#
#	CUSTOM RULES															   #
#------------------------------------------------------------------------------#
GITHUB_PROF = https://github.com/mariav7
GITHUB_COLL = https://github.com/namuzepeda

define HEADER_PROJECT

	  .oooooo.                .o8         .oooo.   oooooooooo.   
	 d8P'  `Y8b              "888       .dP""Y88b  `888'   `Y8b  
	888          oooo  oooo   888oooo.        ]8P'  888      888 
	888          `888  `888   d88' `88b     <88b.   888      888 
	888           888   888   888   888      `88b.  888      888 
	`88b    ooo   888   888   888   888 o.   .88P   888     d88' 
	 `Y8bood8P'   `V88V"V8P'  `Y8bod8P' `8bd88P'   o888bood8P'   
                                                                                                 
endef
export HEADER_PROJECT

header:
	clear
	@echo "$(CYAN)$$HEADER_PROJECT $(RESET)"
	@printf "$(BLUE)%20s Coded by:$(WHITE) \e]8;;$(GITHUB_PROF)\e\\mflores-\e]8;;\e\\ $(BLUE)and$(WHITE) \e]8;;$(GITHUB_COLL)\e\\\nmunoz\e]8;;\e\\ $(RESET)\n\n"

# COLORS
RESET = \033[0m
WHITE = \033[37m
GREY = \033[90m
RED = \033[91m
DRED = \033[31m
GREEN = \033[92m
DGREEN = \033[32m
YELLOW = \033[93m
DYELLOW = \033[33m
BLUE = \033[94m
DBLUE = \033[34m
MAGENTA = \033[95m
DMAGENTA = \033[35m
CYAN = \033[96m
DCYAN = \033[36m

# FORMAT
BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
STRIKETHROUGH = \033[9m
BLINK	= \033[5m