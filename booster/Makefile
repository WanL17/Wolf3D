##
## EPITECH PROJECT, 2025
## G-ING-200-LYN-2-1-myworld-sacha.defossez
## File description:
## Makefile
##

SRC	=	booster.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	booster

CFLAGS	=	-Wall -O3 -Wextra -pedantic -I./include/

LDFLAGS = -L$(HOME)/.local/csfml2/lib -L$(HOME)/.local/sfml2/lib \
           -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio \
           -Wl,-rpath,$(HOME)/.local/csfml2/lib:$(HOME)/.local/sfml2/lib -lm

ifeq ($(ENV), dev)
	CFLAGS += -g3
endif

ifeq ($(DEBUG), yes)
	CFLAGS += -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
