# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 17:56:15 by pabeckha          #+#    #+#              #
#    Updated: 2024/04/08 19:11:01 by sfrankie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ar rcs $@ $^ is the recipe or command to build the target. 
# ar: Archive command used for creating static libraries.
# rcs: Options for ar:
#     r: Insert files into the archive.
#     c: Create the archive if it doesn't exist.
#     s: Write an index (symbol table) into the archive.
# $@: Automatic variable representing the target name
# $^: Automatic variable representing all the prerequisites(the object files)



# ar rcs $@ $^ is the recipe or command to build the target. 
# ar: Archive command used for creating static libraries.
# rcs: Options for ar:
#     r: Insert files into the archive.
#     c: Create the archive if it doesn't exist.
#     s: Write an index (symbol table) into the archive.
# $@: Automatic variable representing the target name
# $^: Automatic variable representing all the prerequisites(the object files)

# =============================================================================
# Color Variables
# =============================================================================

BLACK				= 		"\033[0;30m"
GRAY				= 		"\033[1;30m"
RED					=		"\033[0;31m"
GREEN				=		"\033[0;32m"
YELLOW				=		"\033[1;33m"
PURPLE				=		"\033[0;35m"
CYAN				=		"\033[0;36m"
WHITE				=		"\033[1;37m"
EOC					=		"\033[0;0m"
RESET_COLOR 		= 		"\033[0m"


# Standard
NAME			= minishell

# Directories
SRC_DIR			:= src/
OBJ_DIR			:= obj/
EXECUTION_DIR	:= execution/
BUILTIN_DIR		:= builtin/
PARSING_DIR		:= parsing/

# Compiler and Flags
CC				:= cc
RM				:= rm -f
CFLAGS			:= #-Wall -Wextra -Werror
LREADLINE		:= -lreadline
DEBUG			:= -g
# SANITIZER 		:= #-fsanitize=address -g

# Libraries
LIBFT			:= ./libs/libft/libft.a

					
BUILTIN_SRCS		:= 	$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)cd.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)echo.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)env.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)exit.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)export.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)pwd.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)unset.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)export_utils.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)builtin_utils.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)add_to_envp.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)print_export_structure.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)check_has_env_value.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)print_export_without_value.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)print_export_with_value.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)count_number_equal_signs.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)sort_var_envp.c \


EXECUTION_SRCS		:= 	$(SRC_DIR)$(EXECUTION_DIR)execution.c \
						$(SRC_DIR)$(EXECUTION_DIR)check_builtin.c \
						$(SRC_DIR)$(EXECUTION_DIR)ft_strcmp.c \
						$(SRC_DIR)$(EXECUTION_DIR)get_path_env.c \
						$(SRC_DIR)$(EXECUTION_DIR)split_concat_command.c \
						$(SRC_DIR)$(EXECUTION_DIR)split_concat_command_utils.c \
						$(SRC_DIR)$(EXECUTION_DIR)ft_free.c \
						$(SRC_DIR)$(EXECUTION_DIR)store_envp.c \
						$(SRC_DIR)$(EXECUTION_DIR)get_number_commands.c \
						$(SRC_DIR)$(EXECUTION_DIR)store_path_commands.c \
						$(SRC_DIR)$(EXECUTION_DIR)store_commands.c \
						$(SRC_DIR)$(EXECUTION_DIR)create_pipes.c \
						$(SRC_DIR)$(EXECUTION_DIR)create_child_processes.c \
						$(SRC_DIR)$(EXECUTION_DIR)builtin_execution.c \
						$(SRC_DIR)$(EXECUTION_DIR)pipes_implementation.c \
						$(SRC_DIR)$(EXECUTION_DIR)wait_child_processes.c \
						$(SRC_DIR)$(EXECUTION_DIR)signals/signals.c \
					

PARSING_SRCS		:=	$(SRC_DIR)$(PARSING_DIR)display/default_display.c \
						$(SRC_DIR)$(PARSING_DIR)display/verify_quote_number.c \
						$(SRC_DIR)$(PARSING_DIR)free/free.c \
						$(SRC_DIR)$(PARSING_DIR)init/init_prompt.c \
						$(SRC_DIR)$(PARSING_DIR)init/init_redirection.c \
						$(SRC_DIR)$(PARSING_DIR)init/heredoc_utils.c \
						$(SRC_DIR)$(PARSING_DIR)lex/init_token_list.c \
						$(SRC_DIR)$(PARSING_DIR)lex/init_token_type_2.c \
						$(SRC_DIR)$(PARSING_DIR)lex/init_token_type.c \
						$(SRC_DIR)$(PARSING_DIR)lex/init_words_arr.c \
						$(SRC_DIR)$(PARSING_DIR)lex/monitor_dollar_sign_2.c \
						$(SRC_DIR)$(PARSING_DIR)lex/monitor_dollar_sign.c \
						$(SRC_DIR)$(PARSING_DIR)lex/monitor_single_quote.c \
						$(SRC_DIR)$(PARSING_DIR)lex/utils_2.c \
						$(SRC_DIR)$(PARSING_DIR)lex/utils.c \
						$(SRC_DIR)$(PARSING_DIR)parse/if_no_cmd_tokens.c \
						$(SRC_DIR)$(PARSING_DIR)parse/init_binary_tree.c \
						$(SRC_DIR)$(PARSING_DIR)parse/init_cmd_table.c \
						$(SRC_DIR)$(PARSING_DIR)parse/init_tree_node.c \
						$(SRC_DIR)$(PARSING_DIR)parse/set_redirection_priority.c \
						$(SRC_DIR)$(PARSING_DIR)parse/utils.c \
						$(SRC_DIR)$(PARSING_DIR)print/print.c \
						$(SRC_DIR)$(PARSING_DIR)signals/signals.c \
						$(SRC_DIR)$(PARSING_DIR)parser.c \


SHARED_SRCS			:= 	$(SRC_DIR)main.c \
						$(SRC_DIR)init_vars.c \
	

#Source Files
SRCS			:= 	$(SHARED_SRCS) \
					$(EXECUTION_SRCS) \
					$(BUILTIN_SRCS) \
					$(PARSING_SRCS) \
					


SRCS_BONUS		:= 	$(SHARED_SRCS)\
				

# Creation of Object Files for each Source File
OBJ				:= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Creation of Object Files for each Bonus Source File
OBJ_BONUS		:= $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS_BONUS))

# Rules
all: 		${NAME}

bonus: 		${NAME}_bonus


$(OBJ_DIR)%.o: 	$(SRC_DIR)%.c
					@echo $(YELLOW) "Compiling...\t" $< $(EOC)
#					@curl 'http://141.147.48.52:8080/ansi?start=8b5cf6&end=db2777&padding=5&text=Minishell!'
					@mkdir -p $(@D)
					@${CC} ${CFLAGS} ${DEBUG} $(SANITIZER) -I.libs/libft -c $? -o $@


${NAME}: 		${OBJ}
					@echo $(GREEN) "Source files are compiled!\n" $(EOC)
					@echo $(WHITE) "Building minishell for" $(YELLOW) "Mandatory" $(WHITE) "..." $(EOC)
					@make -s -C ./libs/libft
					@${CC} ${CFLAGS} ${DEBUG} $(SANITIZER) $^ -L./libs/libft -lft $(LREADLINE) -o ${NAME}
					@echo $(GREEN) "Minishell Mandatory is created!\n" $(EOC) $(RESET_COLOR)


${NAME}_bonus:	${OBJ_BONUS}
					@echo $(GREEN) "Source files are compiled!\n" $(EOC)
					@echo $(WHITE) "Building minishell for" $(YELLOW) "Bonus" $(WHITE)
					@make -s -C ./libs/libft
					@${CC} ${CFLAGS} {DEBUG} $^ -L./libs/libft -lft $(LREADLINE) -o ${NAME}_bonus
					@echo $(GREEN) "Minishell Bonus is created!\n" $(EOC) $(RESET_COLOR)

libft:
				@make -C libs/libft


clean:
				@echo $(YELLOW) "Cleaning object files..." $(EOC)
				@make -s clean -C ./libs/libft
				@${RM} ${OBJ} ${OBJ_BONUS}
				@echo $(RED) "Object files are cleaned!\n" $(EOC)

fclean:			clean
				@echo $(YELLOW) "Removing minishell..." $(EOC)
				@${RM} ${NAME} ${NAME}_bonus
				@${RM} ./libs/libft/libft.a
				@rm -rf ${OBJ_DIR}
				@echo $(RED) "Minishell is removed!\n" $(EOC)

re:				fclean all



.PHONY: all clean fclean re libft bonus