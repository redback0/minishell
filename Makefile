CC = cc
CFLAGS = -Wall -Wextra -Werror $(DEBUG_FLAGS)
DEBUG_FLAGS =
ifeq ($(DEBUG), 1)
	DEBUG_FLAGS = -g -DDEBUG=1
	export DEBUG
endif

NAME = minishell

SRC = $(addprefix src/, minishell.c)

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

LIBFT = libft
DLIBS = $(LIBFT)
LIBS = ft
FLIBS = $(join $(addsuffix /lib, $(DLIBS)), $(addsuffix .a, $(LIBS)))

LFLAGS = $(addprefix -L, $(DLIBS)) $(addprefix -l, $(LIBS)) -lreadline

# OS SPECIFICS
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -DMAC_OS
endif
ifeq ($(UNAME),Linux)
	CFLAGS += -DLINUX
endif


IFLAGS = -I. $(addprefix -I, $(DLIBS)) -Iconfig -Idefault_config

#PREFIX/COLOUR VARIABLES
C_GRAY = \033[1;30m
C_ORANGE = \033[0;33m
C_RED = \033[0;31m
C_CYAN = \033[0;36m
NC = \033[0m

PREFIX := $(C_ORANGE)<$(NAME)>$(NC)

all: $(NAME)

print:
	@echo $(NAME)
	@echo $(CC)
	@echo $(CFLAGS)
	@echo $(LFLAGS)
	@echo $(IFLAGS)
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(DLIBS)
	@echo $(LIBS)
	@echo $(FLIBS)

$(NAME): $(OBJ) $(FLIBS)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

$(FLIBS):
	@printf "$(PREFIX) MAKING $(C_CYAN)$@$(NC) ARCHIVE\n"
	@$(MAKE) -C $(dir $@) --no-print-directory -s

-include $(DEP)

%.o: %.c
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -MMD -c $< -o $@

leaks: all
	@printf "$(C_RED)NOT IMPLEMENTED$(NC)\n"

debug: fclean debug_cflags $(NAME)

debug_cflags:
	@$(eval DEBUG_FLAGS = -g -DDEBUG=1)
	@$(eval export DEBUG=1)

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES AND LIBRARIES$(NC)\n"
	@rm -f $(OBJ) $(DEP)
	@- $(foreach D, $(DLIBS), \
		$(MAKE) clean fclean -C $D --no-print-directory -s -i ; )

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug debug_cflags print
