# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfrankie <sfrankie@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 17:56:15 by pabeckha          #+#    #+#              #
#    Updated: 2024/03/16 21:04:36 by sfrankie         ###   ########.fr        #
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
PARSING_DIR		:= parsing/
BUILTIN_DIR		:= builtin/

# Compiler and Flags
CC				:= cc
RM				:= rm -f
CFLAGS			:= -Wall -Wextra -Werror
LREADLINE		:= -lreadline
DEBUG			:= -g
# SANITIZER 		:= #-fsanitize=address -g
DEBUG			:= -g

# Libraries
LIBFT			:= ./libs/libft/libft.a

					
#BUILTIN_SRCS		:= 	$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)cd.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)echo.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)env.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)exit.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)export.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)pwd.c \
						$(SRC_DIR)$(EXECUTION_DIR)$(BUILTIN_DIR)unset.c \



#EXECUTION_SRCS		:= 	$(SRC_DIR)$(EXECUTION_DIR)execution.c \
						$(SRC_DIR)$(EXECUTION_DIR)check_builtin.c \
						$(SRC_DIR)$(EXECUTION_DIR)ft_strcmp.c \
						$(SRC_DIR)$(EXECUTION_DIR)get_path_env.c \
						$(SRC_DIR)$(EXECUTION_DIR)split_concat_command.c \
						$(SRC_DIR)$(EXECUTION_DIR)split_concat_command_utils.c \
						$(SRC_DIR)$(EXECUTION_DIR)ft_free.c \
						$(SRC_DIR)$(EXECUTION_DIR)store_main_variables.c \
					

PARSING_SRCS		:=	$(SRC_DIR)$(PARSING_DIR)default_display.c \
						$(SRC_DIR)$(PARSING_DIR)free.c \
						$(SRC_DIR)$(PARSING_DIR)init_input.c \
						$(SRC_DIR)$(PARSING_DIR)lex_init_token_2.c \
						$(SRC_DIR)$(PARSING_DIR)lex_init_token.c \
						$(SRC_DIR)$(PARSING_DIR)lex_logic.c \
						$(SRC_DIR)$(PARSING_DIR)lex_utils_2.c \
						$(SRC_DIR)$(PARSING_DIR)lex_utils.c \
						$(SRC_DIR)$(PARSING_DIR)parse_init_tree_node.c \
						$(SRC_DIR)$(PARSING_DIR)parse_logic.c \
						$(SRC_DIR)$(PARSING_DIR)parser.c \
						$(SRC_DIR)$(PARSING_DIR)print.c \


SHARED_SRCS			:= $(SRC_DIR)main.c

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