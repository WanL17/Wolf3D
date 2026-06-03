##
## EPITECH PROJECT, 2025
## G-CPE-100-LYN-1-1-cpoolday10-40
## File description:
## Makefile
##

CC	=	epiclang

SRC	=	src/main.c					\
		src/init.c					\
		src/init_struct.c			\
		src/destroy.c					\
		src/raycast/draw.c					\
		src/raycast/framebuffer.c				\
		src/raycast/raycasting.c				\
		src/raycast/particles.c				\
		src/game/update.c					\
		src/game/game.c					\
		src/game/event.c					\
		src/game/difficulty.c					\
		src/map/alloc.c					\
		src/map/file.c					\
		src/menu/menu_nav.c				\
		src/menu/menu.c					\
		src/menu/blur_shader.c					\
		src/menu/create_specific_menus.c		\
		src/menu/menu_rendering.c			\
		src/menu/create_title.c			\
		src/menu/resolution_nav.c			\
		src/menu/fps_nav.c			\
		src/menu/handle_inputs.c			\
		src/menu/button_actions.c			\
		src/menu/button_actions_2.c			\
		src/menu/button_actions_3.c			\
		src/menu/parts_handling.c			\
		src/menu/text_actions.c				\
		src/menu/events.c				\
		src/hud/minimap.c				\
		src/hud/create_hud.c			\
		src/hud/score.c			\
		src/inputs/movement.c					\
		src/inputs/handle_controller.c			\
		src/entity/draw_entities.c			\
		src/entity/collision.c			\
		src/entity/entities_spawn.c				\
		src/entity/update_entities.c				\
		src/entity/create_entities.c		\
		src/entity/entity_comportement.c		\
		src/weapons/create_weapons.c		\
		src/weapons/use_weapons.c		\
		src/weapons/weapons_animation.c

CFLAGS  = -I./include -Wextra -Wall -pedantic -g3

LDFLAGS = -L$(HOME)/.local/csfml2/lib -L$(HOME)/.local/sfml2/lib \
           -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio \
           -Wl,-rpath,$(HOME)/.local/csfml2/lib:$(HOME)/.local/sfml2/lib -lm

OBJ	=	$(SRC:.c=.o)

NAME	=	wolf3d

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

