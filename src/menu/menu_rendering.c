/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** menu_window.c
*/
#include "my.h"

static void update_text(game_t *game, player_t *player)
{
    int i = 0;

    while (game->menu->texts[i]) {
        game->menu->texts[i]->action(game, player, game->menu->texts[i]);
        i++;
    }
}

static void render_menu3(game_t *game)
{
    if (game->menu_index == GAME_OVER_WINDOW) {
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->blur[1], NULL);
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->game_over, NULL);
    }
}

static void render_menu2(game_t *game, int *i)
{
    while (game->menu->texts[(*i)]) {
        sfRenderWindow_drawText(GAME_WIN, game->menu->texts[(*i)]->text, NULL);
        (*i)++;
    }
    if (game->menu_index == INTRO_MENU || game->menu_index == PAUSE_WINDOW) {
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->title[1], NULL);
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->title[0], NULL);
    }
    if (game->menu_index == MAIN_MENU) {
        sfSprite_setScale(game->menu->title[0], (sfVector2f){0.2, 0.2});
        sfSprite_setScale(game->menu->title[1], (sfVector2f){0.2, 0.2});
        sfSprite_setPosition(game->menu->title[0], (sfVector2f){0, -30});
        sfSprite_setPosition(game->menu->title[1], (sfVector2f){0, -25});
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->title[1], NULL);
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->title[0], NULL);
    }
    if (game->menu_index == SETTINGS_MENU) {
        for (int k = 0; k < 4; k++)
            display_input_buttons(game, k);
    }
}

void render_menu(game_t *game, player_t *player)
{
    sfVector2i mouse_loc = sfMouse_getPositionRenderWindow(game->window);
    int i = 0;

    if (game->menu_index == PAUSE_WINDOW)
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->blur[0], NULL);
    scale_mouse(game, &mouse_loc);
    if (game->menu_index != PAUSE_WINDOW &&
        game->menu_index != GAME_OVER_WINDOW)
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->background, NULL);
    update_text(game, player);
    event_hover_buttons(game, &mouse_loc);
    while (game->menu->buttons[i]) {
        sfRenderWindow_drawSprite(GAME_WIN, game->menu->buttons[i]->sprite,
            NULL);
        i++;
    }
    i = 0;
    render_menu2(game, &i);
    render_menu3(game);
}
