NAME_SERVER = 		serveur
NAME_CLIENT = 		client

SRC_DIR_SERVER =	./src/server
SRC_DIR_CLIENT = 	./src/client
SRC_DIR_SHARED =	./src/shared

OBJ_DIR_SERVER =	./obj_server
OBJ_DIR_CLIENT =	./obj_client
OBJ_DIR_SHARED =	./obj_shared

SRC_SERVER = 		server.c \
					commands.c \
					command_get.c \
					display.c

SRC_CLIENT = 		client.c \
					commands.c \
					command_get.c \
					display.c

SRC_SHARED =		handle_error.c \
					handle_file.c

OBJ_SERVER = 		$(addprefix $(OBJ_DIR_SERVER)/,$(SRC_SERVER:.c=.o))
OBJ_CLIENT = 		$(addprefix $(OBJ_DIR_CLIENT)/,$(SRC_CLIENT:.c=.o))
OBJ_SHARED =		$(addprefix $(OBJ_DIR_SHARED)/,$(SRC_SHARED:.c=.o))

SRC_PATH_SERVER = 	$(addprefix $(SRC_DIR_SERVER)/,$(SRC_SERVER))
SRC_PATH_CLIENT =	$(addprefix $(SRC_DIR_CLIENT)/,$(SRC_CLIENT))
SRC_PATH_SHARED =	$(addprefix $(SRC_DIR_SHARED)/,$(SRC_SHARED))

CC = 				gcc

FLAGS = 			-Wall -Werror -Wextra

HEADERS = 			-I ./headers

I_LIBFT = 			-I libft/INCLUDES/

LIBFT = 			$(I_LIBFT) -Llibft -lft

all: $(NAME_SERVER)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SHARED)
	@make -C libft
	@$(CC) $(FLAGS) -o $(NAME_SERVER) $(OBJ_SERVER) $(OBJ_SHARED) $(HEADERS) $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME_CLIENT) $(OBJ_CLIENT) $(OBJ_SHARED) $(HEADERS) $(LIBFT)
	@echo "\033[1;34mSERVER/CLIENT\t\t\033[1;33mCompilation\t\033[0;32m-OK-\033[0m"

$(OBJ_DIR_SERVER)/%.o: $(SRC_DIR_SERVER)/%.c
	@mkdir $(OBJ_DIR_SERVER) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

$(OBJ_DIR_CLIENT)/%.o: $(SRC_DIR_CLIENT)/%.c
	@mkdir $(OBJ_DIR_CLIENT) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

$(OBJ_DIR_SHARED)/%.o: $(SRC_DIR_SHARED)/%.c
	@mkdir $(OBJ_DIR_SHARED) 2> /dev/null || true
	@$(CC) $(FLAGS) $(HEADERS) -o $@ -c $< $(I_LIBFT)

clean: clean_server clean_client clean_shared

clean_server:
	@rm -rf $(OBJ_SERVER) $(NAME_SERVER)
	@echo "\033[1;34mSERVER\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

clean_client:
	@rm -rf $(OBJ_CLIENT) $(NAME_CLIENT)
	@echo "\033[1;34mCLIENT\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

clean_shared:
	@rm -rf $(OBJ_SHARED)
	@echo "\033[1;34mSHARED\t\033[1;33mCleaning obj\t\033[0;32m-OK-\033[0m"

fclean: clean
	@make fclean -C libft
	@echo "\033[1;34mSERVER/CLIENT\t\033[1;33mCleaning lib\t\033[0;32m-OK-\033[0m"
	@rm -rf $(OBJ_DIR_SERVER) $(OBJ_DIR_CLIENT) $(OBJ_DIR_SHARED)

re: fclean all

norme:
	@echo "\033[1;34mSERVER/CLIENT\t\033[1;33mNorminette\t\033[0;32m-OK-\033[0m"
	@norminette $(SRC_PATH_SERVER) $(SRC_PATH_CLIENT) $(SRC_PATH_SHARED)

.PHONY: re fclean clean all norme server client
