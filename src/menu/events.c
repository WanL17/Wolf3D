/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** button events processing
*/

#include "my.h"

static void button_hovering_action(sfVector2i *mouse_loc,
    button_t *button)
{
    sfFloatRect rect = sfSprite_getGlobalBounds(button->sprite);
    sfFloatRect bounds = sfSprite_getLocalBounds(button->sprite);

    if (sfFloatRect_contains(&rect, mouse_loc->x, mouse_loc->y)) {
        sfSprite_setTexture(button->sprite, button->hover_txtr, sfTrue);
        sfSprite_setScale(button->sprite, (sfVector2f){0.3f, 0.3f});
        sfSprite_setOrigin(button->sprite, (sfVector2f){bounds.width / 10,
                bounds.height / 10});
    } else {
        sfSprite_setColor(button->sprite, sfWhite);
        sfSprite_setTexture(button->sprite, button->txtr, sfTrue);
        sfSprite_setScale(button->sprite, (sfVector2f){0.25f, 0.25f});
        sfSprite_setOrigin(button->sprite, (sfVector2f){0.0f, 0.0f});
    }
}

void event_hover_buttons(game_t *game, sfVector2i *mouse_loc)
{
    int i = 0;

    while (game->menu->buttons[i]) {
        button_hovering_action(mouse_loc, game->menu->buttons[i]);
        i++;
    }
}

void event_pressed_buttons(game_t *game, sfVector2i *mouse_loc)
{
    sfFloatRect button_rect;
    int i = 0;

    while (game->menu->buttons[i]){
        button_rect = sfSprite_getGlobalBounds(game->menu->buttons[i]->sprite);
        if (sfFloatRect_contains(&button_rect, mouse_loc->x, mouse_loc->y))
            sfSprite_setColor(game->menu->buttons[i]->sprite, sfRed);
        i++;
    }
}

void event_released_buttons(game_t *game, player_t *player,
    sfVector2i *mouse_loc)
{
    sfFloatRect button_rect;
    int i = 0;

    while (game->menu->buttons[i]){
        button_rect = sfSprite_getGlobalBounds(game->menu->buttons[i]->sprite);
        if (sfFloatRect_contains(&button_rect, mouse_loc->x, mouse_loc->y)){
            game->menu->buttons[i]->action(game, player,
                game->menu->buttons[i]);
            return;
        }
        i++;
    }
}
