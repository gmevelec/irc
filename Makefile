
SERVEUR = serveur
CLIENT = client

CFLAGS = -Wall -Wextra -Werror

INC = -I $(SERVEUR)/inc -I $(CLIENT)/inc -I./libft

INC_DIR = inc/
SRC_DIR = src/

SERVEUR_INC_FILES = $(SERVEUR).h
SERVEUR_INC = $(addprefix $(SERVEUR)_DIR/$(INC_DIR), $(SERVEUR_INC_FILES))
SERVEUR_FILES = serveur.c \
				treat_client.c \
				msg.c \
				msg_2.c \
				cmd.c \
				cmd_2.c \
				init.c \
				check.c \
				error.c \

SERVEUR_SRC = $(addprefix $(SERVEUR)_DIR/$(SRC_DIR), $(SERVEUR_FILES))
SERVEUR_OBJ = $(SERVEUR_SRC:.c=.o)

CLIENT_INC_FILES = $(CLIENT).h
CLIENT_INC = $(addprefix $(CLIENT)_dir/$(INC_DIR), $(CLIENT_INC_FILES))
CLIENT_FILES = client.c \
				error.c \
				read_write.c \
				check.c \

CLIENT_SRC = $(addprefix $(CLIENT)_DIR/$(SRC_DIR), $(CLIENT_FILES))
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

LIB = ./libft/libft.a

all: $(SERVEUR) $(CLIENT)

$(SERVEUR): $(SERVEUR_OBJ)
	@make -C ./libft
	@gcc $(CFLAGS) -o $(SERVEUR) $(SERVEUR_OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"Compilation of $(SERVEUR) : "\033[32m"Success"\033[0m"

$(CLIENT): $(CLIENT_OBJ)
	@make -C ./libft
	@gcc $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(LIB)
	@echo ""
	@echo "\033[33m"Compilation of $(CLIENT) : "\033[32m"Success"\033[0m"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@ $(INC)

clean-serveur:
	@rm -f $(SERVEUR_OBJ)
	@echo "\033[31m"Objects of $(SERVEUR) : deleted"\033[0m"

clean-client:
	@rm -f $(CLIENT_OBJ)
	@echo "\033[31m"Objects of $(CLIENT) : deleted"\033[0m"

clean: clean-serveur clean-client

fclean: clean
	@/bin/rm -f $(CLIENT) $(SERVEUR)
	@echo "\033[31m"$(CLIENT) and $(SERVEUR) : deleted"\033[0m"
	@make fclean -C libft

re: fclean all