NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRCS = main.c \
       parsing.c \
       utils.c \
       init.c \
       simulation.c \
	   monitor.c

OBJS = $(SRCS:.c=.o)

HEADER = philo.h

GREEN = \033[0;32m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking philosophers...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ Philosophers compiled successfully!$(RESET)"

%.o: %.c $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo "$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✓ Everything cleaned!$(RESET)"

re: fclean all
	@echo "$(GREEN)✓ Project rebuilt!$(RESET)"

.PHONY: all clean fclean re