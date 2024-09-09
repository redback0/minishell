CC := cc
CFLAGS := -Wall -Wextra -Werror
DEBUG_FLAGS := -g -DDEBUG=1

NAME := minishell

FILES := minishell	ft_env		ft_env_ext \
		 signals	execute		execute_utils \
		 parse_args	redirect	execute_ext \
		 ms_echo	ms_cd		ms_pwd \
		 ms_export	ms_unset	ms_env \
		 execute_builtin		find_command \


SRC_DIR := src/
OBJ_DIR := obj/
DEBUG_DIR := debug_obj/

SRC := $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILES)))
OBJ := $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))
DEP := $(OBJ:.o=.d)
DEBUG_OBJ := $(patsubst $(OBJ_DIR)%, $(DEBUG_DIR)%, $(OBJ))
DEBUG_DEP := $(DEBUG_OBJ:.o=.d)

DLIBS := libft
LIBS := ft
FLIBS := $(join $(addsuffix /lib, $(DLIBS)), $(addsuffix .a, $(LIBS)))

RL_INCL := /usr/local/opt/readline/include
RL_LIB := /usr/local/opt/readline/lib

LFLAGS := $(addprefix -L, $(DLIBS)) $(addprefix -l, $(LIBS)) -L$(RL_LIB) -lreadline

# OS SPECIFICS
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -DMAC_OS
endif
ifeq ($(UNAME),Linux)
	CFLAGS += -DLINUX
endif


IFLAGS := -I. $(addprefix -I, $(DLIBS)) -Iinc -I$(RL_INCL) -Iconfig -Idefault_config

#PREFIX/COLOUR VARIABLES
C_GRAY := \033[1;30m
C_ORANGE := \033[0;33m
C_RED := \033[0;31m
C_CYAN := \033[0;36m
NC := \033[0m

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
	@echo $(DEP)
	@echo $(DEBUG_OBJ)
	@echo $(DLIBS)
	@echo $(LIBS)
	@echo $(FLIBS)
	@echo $(OBJ_DIR)

$(NAME): $(OBJ) $(FLIBS)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LFLAGS)

$(NAME)_debug: $(DEBUG_OBJ) $(FLIBS)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $@ $(DEBUG_OBJ) $(LFLAGS)

$(FLIBS):
	@printf "$(PREFIX) MAKING $(C_CYAN)$@$(NC) ARCHIVE\n"
	@$(MAKE) -C $(dir $@) --no-print-directory -s

-include $(DEP)
-include $(DEBUG_DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -MMD -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(DEBUG_DIR)%.o: $(SRC_DIR)%.c | $(DEBUG_DIR)
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(IFLAGS) -MMD -c $< -o $@

$(DEBUG_DIR):
	@mkdir $(DEBUG_DIR)

config/config.h: default_config/config.h

leaks: debug
	@printf "$(PREFIX) $(C_RED)RUNNING VALGRIND WITH READLINE SUPPRESSION$(NC)\n"
	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell_debug

debug: _debug $(NAME)_debug

_debug:
	@printf "$(PREFIX) $(RED)***DEBUG MODE***$(NC)\n"

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES AND LIBRARIES$(NC)\n"
	@rm -rf $(OBJ_DIR) $(DEBUG_DIR)
	@- $(foreach D, $(DLIBS), \
		$(MAKE) clean fclean -C $D --no-print-directory -s -i ; )

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME) $(NAME)_debug

re: fclean all

.PHONY: all clean fclean re debug debug_cflags print
