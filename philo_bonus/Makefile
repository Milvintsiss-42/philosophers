# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ple-stra <ple-stra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/29 15:36:23 by ple-stra          #+#    #+#              #
#    Updated: 2022/11/04 20:02:46 by ple-stra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

SRCS_DIR	= srcs
SRCS		= \
 $(addsuffix _bonus.c,\
 philosophers\
 processes monitoring\
 eat sleep think die\
 errors logs basic_utils\
 )
BUILD_DIR	= build
OBJ_DIR		= $(BUILD_DIR)/objs
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC			= -I./includes -I./

CC			= cc
CFLAGS		= -Wall -Wextra
ifneq (nWerror, $(filter nWerror,$(MAKECMDGOALS)))
	CFLAGS	+= -Werror
endif
ifeq (sanitize, $(filter sanitize,$(MAKECMDGOALS)))
	CFLAGS 	+= -fsanitize=address
endif
ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS	+= -D KDEBUG=1
endif

RM			= rm -rf

all			: $(NAME)

bonus		: $(NAME)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME)		: $(OBJ)
			$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ) $(LFLAGS)
			
clean		:
			$(RM) $(OBJ_DIR)
			$(RM) $(OBJBNS_DIR)

fclean		:
			$(RM) $(BUILD_DIR)
			$(RM) $(NAME)

fcleanall	:
			$(RM) $(BUILD_DIR)
			$(RM) $(NAME)

re			: fclean all

nWerror		:
			@echo "WARN: Compiling without Werror flag!"
sanitize	:
			@echo "WARN: Compiling with fsanitize flag!"
debug		:
			@echo "WARN: debug is enabled"

.PHONY: \
 all bonus clean fclean fcleanall re\
 nWerror sanitize debug
