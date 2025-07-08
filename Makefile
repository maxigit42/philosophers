NAME = philo

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC = main.c atoi.c utils.c init.c init_philo.c routine.c one_philo.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

INC = -I$(INC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)
	@echo "$(NAME) creado"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Objetos eliminados"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) eliminado"

re: fclean all

run: all clean

.PHONY: all clean fclean re run
