# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/15 11:46:30 by tshimizu          #+#    #+#              #
#    Updated: 2025/09/15 11:51:32 by tshimizu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ========================
#       CONFIGURATION
# ========================
NAME		= philo

CC			= cc
SRC_DIR		= src
OBJ_DIR		= objs
INC_DIR		= includes

INCFLAG		= -I$(INC_DIR)
CFLAGS		= -Wall -Wextra -Werror $(INCFLAG)

SRC = philo.c

SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

RM			= rm -f

# ========================
#        TARGETS
# ========================
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo "✅ Compiled: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔧 Compiled: $<"

# ========================
#       CLEANING
# ========================

clean:
	@$(RM) $(OBJS)
	@echo "🧹 Cleaned object files."

fclean: clean
	@$(RM) $(NAME)
	@echo "🧼 Cleaned executable."

re: fclean all

# ========================
#        PHONY
# ========================
.PHONY: all clean fclean re
