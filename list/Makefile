NAME = libftlist.a
AUTHOR = nmunoz
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = list_add \
		list_clone \
		list_contains \
		list_create \
		list_delete \
		list_equals \
		list_get \
		list_index \
		list_reverse \
		list_sort_asc \
		list_sort_desc \
		list_sublist \
		list_swap \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(YELLOW). . . COMPILING LIBLIST OBJECTS . . . $(GREY)%-33.33s\r$(WHITE)" $@

$(NAME): $(OBJS)
	@$(AR) $@ $^

bonus: $(OBJS_B)
	@$(AR) $(NAME) $^

all: $(NAME)

clean:
	@$(RM) -rd $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re

#Colors
DEF_COLOR = \033[0;39m
GREY = \033[0;90m
RED = \033[0;91m
GREEN = \033[1;92m
YELLOW = \033[0;93m
WHITE = \033[0;97m