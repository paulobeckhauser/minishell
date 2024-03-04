# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabeckha <pabeckha@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 17:56:15 by pabeckha          #+#    #+#              #
#    Updated: 2024/03/04 12:06:04 by pabeckha         ###   ########.fr        #
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

# Compiler and Flags
CC				:= cc
RM				:= rm -f
CFLAGS			:= -Wall -Wextra -Werror
# SANITIZER 		:= #-fsanitize=address -g

# Libraries
LIBFT			:= ./libs/libft/libft.a


SHARED_SRCS		:= 	


#Source Files
SRCS			:= 	$(SHARED_SRCS) \
					$(SRC_DIR)main.c \


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
					@mkdir -p $(@D)
					@${CC} ${CFLAGS} $(SANITIZER) -I.libs/libft -c $? -o $@


${NAME}: 		${OBJ}
					curl 'http://141.148.244.146:8080/ansi?start=8b5cf6&end=db2777&padding=5&text=Minishell!'
					@echo $(GREEN) "Source files are compiled!\n" $(EOC)
					@echo $(WHITE) "Building minishell for" $(YELLOW) "Mandatory" $(WHITE) "..." $(EOC)
					@make -s -C ./libs/libft
					@${CC} ${CFLAGS} $(SANITIZER) $^ -L./libs/libft -lft -o ${NAME}
					@echo $(GREEN) "Minishell Mandatory is created!\n" $(EOC) $(RESET_COLOR)


${NAME}_bonus:	${OBJ_BONUS}
					@echo $(GREEN) "Source files are compiled!\n" $(EOC)
					@echo $(WHITE) "Building minishell for" $(YELLOW) "Bonus" $(WHITE)
					@make -s -C ./libs/libft
					@${CC} ${CFLAGS} $^ -L./libs/libft -lft -o ${NAME}_bonus
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