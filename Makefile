# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mflores- <mflores-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 15:00:42 by mflores-          #+#    #+#              #
#    Updated: 2023/05/02 20:30:31 by mflores-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#								GENERAL		               				       #
#------------------------------------------------------------------------------#

NAME	= cub3D
CC		= cc
FLAGS	= -Wall -Wextra -Werror -g
RM		= rm -f

#------------------------------------------------------------------------------#
#								HEADER FILES            				       #
#------------------------------------------------------------------------------#

HEADER_FILES	= cub3d
HEADERS_PATH 	= includes/
HEADERS			= $(addsuffix .h, $(addprefix $(HEADERS_PATH), $(HEADER_FILES)))
HEADERS_INC		= $(addprefix -I, $(HEADERS_PATH) $(LIB_HEADER_PATH) \
						$(LIBLIST_HEADER_PATH) /usr/include/$(MLX_HEADER_PATH))

#------------------------------------------------------------------------------#
#								LIBFT		           				   	   	   #
#------------------------------------------------------------------------------#

LIB_NAME 	= ft
LIB_PATH	= libft/
LIB			= -L$(LIB_PATH) -l$(LIB_NAME)
LIB_HEADER_PATH = $(LIB_PATH)includes/

#------------------------------------------------------------------------------#
#								LIST		           				   	   	   #
#------------------------------------------------------------------------------#

LIBLIST_NAME 	= ftlist
LIBLIST_PATH	= list/
LIBLIST			= -L$(LIBLIST_PATH) -l$(LIBLIST_NAME)
LIBLIST_HEADER_PATH = $(LIBLIST_PATH)

#------------------------------------------------------------------------------#
#								MINILIBX	           				   	   	   #
#------------------------------------------------------------------------------#

MLX_FILES	= mlx mlx_init
MLX_HEADER_PATH	= $(addsuffix .h, $(addprefix $(MLX_PATH), $(MLX_FILES)))
MLX_NAME	= mlx_Linux
MLX_PATH 	= mlx/
MLX_FLAGS	= -L/usr/lib -lXext -lX11 -lm -lz -O3
MLX			= -L$(MLX_PATH) -l$(MLX_NAME) $(MLX_FLAGS) 

#------------------------------------------------------------------------------#
#								CUB3D FILES          	 				   	   #
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
DEBUG_FILES = print_structs
DEBUG_FOLDER = debug/
GAME_FOLDER = game/
GAME_FILES = game map player_movement player_rotation player
SCREEN_FOLDER = screen/
SCREEN_FILES = screen minimap

SRCS_PATH = srcs/
SRCS_FILES 	= $(addsuffix .c, $(ROOT_FILES) \
							$(addprefix $(PARSING_FOLDER), $(PARSING_FILES)) \
							$(addprefix $(UTILS_FOLDER), $(UTILS_FILES)) \
							$(addprefix $(INIT_FOLDER), $(INIT_FILES)) \
							$(addprefix $(GAME_FOLDER), $(GAME_FILES)) \
							$(addprefix $(SCREEN_FOLDER), $(SCREEN_FILES)) \
							$(addprefix $(DEBUG_FOLDER), $(DEBUG_FILES))) 

# All .o files go to objs directory
OBJS_NAMES	= $(SRCS_FILES:.c=.o)
OBJS_FOLDER = $(addprefix $(OBJS_PATH), $(PARSING_FOLDER) $(UTILS_FOLDER) \
										$(GAME_FOLDER) $(SCREEN_FOLDER) \
										$(INIT_FOLDER) $(DEBUG_FOLDER)) 
OBJS_PATH 	= objs/
OBJS		= $(addprefix $(OBJS_PATH), $(OBJS_NAMES))

# Gcc/Clang will create these .d files containing dependencies
DEPS		= $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.d))

#------------------------------------------------------------------------------#
#								BASCIC RULES	        				       #
#------------------------------------------------------------------------------#

all:	header $(NAME)
	@echo "\n$(GREEN)[ ✔ ]\tCUB3D$(WHITE)"
	@echo "\033[1;39m\n▶ TO LAUNCH:\t./$(NAME) map_file.cub\n $(DEF_COLOR)"

# Actual target of the binary - depends on all .o files
$(NAME): lib liblist $(HEADERS) $(OBJS)
# Compile Minilibx
	@echo "$(YELLOW)\n. . . COMPILING MINILIBX OBJECTS . . . $(WHITE)\n"
	@$(MAKE) --no-print-directory -sC $(MLX_PATH)
	@echo "$(GREEN)[ ✔ ]\tMINILIBX$(WHITE)"
# Link all the object files
	@$(CC) $(FLAGS) $(HEADERS_INC) $(OBJS) $(LIB) $(LIBLIST) $(MLX) -o $(NAME)
# Build target for every single object file
# The potential dependency on header files is covered
# by calling `-include $(DEPS)`
$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
# Create objs directory
	@mkdir -p $(OBJS_FOLDER)
  # The -MMD flags additionaly creates a .d file with
  # the same name as the .o file.
	@$(CC) $(FLAGS) $(HEADERS_INC) -MMD -MP -o $@ -c $<
	@printf "$(YELLOW). . . COMPILING Cub3D OBJECTS . . . $(GREY)%-33.33s\r$(DEF_COLOR)" $@

lib:
	@$(MAKE) --no-print-directory -C $(LIB_PATH)
	@echo "\n$(GREEN)[ ✔ ]\tLIBFT $(DEF_COLOR)"

liblist:
	@$(MAKE) --no-print-directory -C $(LIBLIST_PATH)
	@echo "\n$(GREEN)[ ✔ ]\tLIBLIST $(DEF_COLOR)"

clean:
ifeq ("$(shell test -d $(OBJS_PATH) && echo $$?)","0")
	@echo "$(YELLOW)\n. . . CLEANING OBJECTS . . .\n$(DEF_COLOR)"
	@$(MAKE) --no-print-directory clean -C $(LIB_PATH)
	@$(MAKE) --no-print-directory clean -sC $(MLX_PATH)
	@$(MAKE) --no-print-directory clean -C $(LIBLIST_PATH)
	@$(RM) -rd $(OBJS_PATH)
	@echo "$(GREEN)[ ✔ ]\tOBJECTS CLEANED$(DEF_COLOR)"
else
	@echo "$(BLUE)NO OBJECTS TO CLEAN$(DEF_COLOR)"
endif

fclean:	clean
ifeq ("$(shell test -e $(NAME) && echo $$?)","0")
	@echo "$(YELLOW)\n. . . CLEANING REST . . .\n$(DEF_COLOR)"
	@$(MAKE) --no-print-directory fclean -C $(LIB_PATH)
	@$(MAKE) --no-print-directory fclean -C $(LIBLIST_PATH)
	@$(RM) $(NAME)
	@echo "$(GREEN)[ ✔ ]\tALL CLEANED$(DEF_COLOR)"
else
	@echo "$(BLUE)NOTHING TO CLEAN$(DEF_COLOR)"
endif

re:	fclean all

# Include all .d files
-include $(DEPS)

.PHONY:	all clean fclean re header norme check lib liblist

#------------------------------------------------------------------------------#
#								CUSTOM RULES    					           #
#------------------------------------------------------------------------------#

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
	@echo "$(CYAN)$$HEADER_PROJECT $(DEF_COLOR)"

check:
	@grep -qe ${USER} -e ${MAIL} $(SRCS_PATH)$(SRCS_FILES) $(HEADERS) && \
	echo "$(GREEN)[ ✔ ]\tUsername and email$(DEF_COLOR)" \
	|| echo "$(RED)[ ✗ ]\tUsername and email$(DEF_COLOR)"
	@ls | grep -q -U $(NAME) && \
	echo "$(GREEN)[ ✔ ]\tExecutable name$(DEF_COLOR)" || \
	echo "$(RED)[ ✗ ]\tExecutable name$(DEF_COLOR)"
	@$(MAKE) norme | grep -B 1 Error && \
	echo "$(RED)[ ✗ ]\tNorme$(DEF_COLOR)" || \
	echo "$(GREEN)[ ✔ ]\tNorme$(DEF_COLOR)"

norme:
	@if norminette $(HEADERS) $(SRCS_PATH) $(LIB_PATH); then \
	echo "$(GREEN)[ ✔ ]\tNORME$(DEF_COLOR)"; \
	else \
	echo "$(RED)[ ✗ ]\tNORME$(DEF_COLOR)"; \
	fi

#Colors
DEF_COLOR = \033[0;39m
GREY = \033[0;90m
RED = \033[1;91m
GREEN = \033[1;92m
YELLOW = \033[0;93m
BLUE = \033[1;94m
MAGENTA = \033[1;35m
CYAN = \033[1;96m
WHITE = \033[0;97m