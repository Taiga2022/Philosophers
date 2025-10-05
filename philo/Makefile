# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimizu <tshimizu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/15 11:46:30 by tshimizu          #+#    #+#              #
#    Updated: 2025/10/05 18:04:54 by tshimizu         ###   ########.fr        #
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

SRC = philo.c\
	  routine.c\
	  utils.c\
	  thread.c\
	  free.c \
	  monitor.c

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
#    DEBUG / SANITIZER
# ========================
asan: CFLAGS += -g -fsanitize=address

asan: re
	@echo "🚀 Running with AddressSanitizer"
	./$(NAME) 5 800 200 200

tsan: CFLAGS += -g -fsanitize=thread
tsan: CC = clang
tsan: re
	@echo "🚀 Running with ThreadSanitizer"
	./$(NAME) 5 800 200 200

debug: CFLAGS += -g
debug: re
	@echo "🚀 Debug build ready (use gdb/lldb)"

valgrind: re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 5 800 200 200

helgrind: re
	valgrind --tool=helgrind --fair-sched=yes ./$(NAME) 5 800 200 200

drd: re
	valgrind --tool=drd  ./$(NAME) 5 800 200 200

# ========================
#    TEST / RUN HELPERS
# ========================
run: all
	./$(NAME) 5 800 200 200

test: all
	./$(NAME) 2 300 100 100
	./$(NAME) 5 800 200 200
	./$(NAME) 5 800 200 200 7

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
.PHONY: all clean fclean re asan tsan debug run test valgrind
