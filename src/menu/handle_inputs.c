/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** inputs_nav.c
*/
#include "my.h"

const sfVector2f inputs_nav[] = {
    {0, 0},
    {16, 0},
    {32, 0},
    {48, 0},
    {64, 0},
    {80, 0},
    {96, 0},
    {112, 0},
    {0, 16},
    {16, 16},
    {32, 16},
    {48, 16},
    {64, 16},
    {80, 16},
    {96, 16},
    {112, 16},
    {0, 32},
    {16, 32},
    {32, 32},
    {48, 32},
    {64, 32},
    {80, 32},
    {96, 32},
    {112, 32},
    {0, 48},
    {16, 48}
};

bool create_input_button(menu_t *menu)
{
    menu->input_but = sfSprite_create();
    menu->input_but_txtr = sfTexture_createFromFile(
        "./assets/images/keyboard.png", NULL);
    if (!menu->input_but || !menu->input_but_txtr)
        return false;
    sfSprite_setTexture(menu->input_but, menu->input_but_txtr, sfTrue);
    return true;
}

static void wait_for_input(game_t *game, int i)
{
    while (sfRenderWindow_waitEvent(GAME_WIN, &game->event)) {
        if (game->event.type == sfEvtKeyPressed
            && game->event.key.code <= 25) {
            game->inputs[i] = game->event.key.code;
            break;
        }
    }
}

static void event_input_button(
    game_t *game, sfSprite *button, int i)
{
    sfVector2i mouse_loc = sfMouse_getPositionRenderWindow(game->window);
    sfFloatRect button_rect = {0};
    sfColor color = sfWhite;

    color.a = 100;
    button_rect = sfSprite_getGlobalBounds(button);
    if (sfFloatRect_contains(&button_rect, mouse_loc.x, mouse_loc.y) &&
        game->event.type == sfEvtMouseButtonPressed) {
        sfSprite_setColor(button, color);
        wait_for_input(game, i);
    }
    sfSprite_setColor(button, sfWhite);
}

void display_input_buttons(game_t *game, int i)
{
    sfIntRect rect = {0};
    sfVector2f pos = {(i * 90) + 440, 250.0f};
    sfVector2f scale = {3.7, 3.7};

    rect.height = 16;
    rect.width = 16;
    rect.top = inputs_nav[game->inputs[i]].y;
    rect.left = inputs_nav[game->inputs[i]].x;
    sfSprite_setTextureRect(game->menu->input_but, rect);
    sfSprite_setScale(game->menu->input_but, scale);
    sfSprite_setPosition(game->menu->input_but, pos);
    sfRenderWindow_drawSprite(GAME_WIN, game->menu->input_but, NULL);
    event_input_button(game, game->menu->input_but, i);
}
