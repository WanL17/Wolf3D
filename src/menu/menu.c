/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** create_menu.c
*/
#include "my.h"

void clean_menu(menu_t *menu)
{
    int i = 0;

    if (!menu)
        return;
    if (menu->buttons) {
        while (menu->buttons[i]) {
            destroy_button(menu->buttons[i]);
            i++;
        }
        free(menu->buttons);
    }
    i = 0;
    if (menu->texts){
        while (menu->texts[i]){
            sfText_destroy(menu->texts[i]->text);
            free(menu->texts[i]);
            i++;
        }
        free(menu->texts);
    }
}

static void destroy_menu_part2(menu_t *menu)
{
    if (menu->input_but)
        sfSprite_destroy(menu->input_but);
    if (menu->input_but_txtr)
        sfTexture_destroy(menu->input_but_txtr);
    if (menu->title_txtr)
        sfTexture_destroy(menu->title_txtr);
    if (menu->game_over)
        sfSprite_destroy(menu->game_over);
    if (menu->t_game_over)
        sfTexture_destroy(menu->t_game_over);
    if (menu->blur[1])
        sfSprite_destroy(menu->blur[1]);
    if (menu->blur_txtr[1])
        sfTexture_destroy(menu->blur_txtr[1]);
}

void destroy_menu(menu_t *menu)
{
    clean_menu(menu);
    for (int i = 0; i < 2; i++)
        if (menu->font[i])
            sfFont_destroy(menu->font[i]);
    for (int i = 0; i < 2; i++)
        if (menu->title[i])
            sfSprite_destroy(menu->title[i]);
    if (menu->background)
        sfSprite_destroy(menu->background);
    if (menu->background_txtr)
        sfTexture_destroy(menu->background_txtr);
    if (menu->timer)
        sfClock_destroy(menu->timer);
    if (menu->blur[0])
        sfSprite_destroy(menu->blur[0]);
    if (menu->blur_txtr[0])
        sfTexture_destroy(menu->blur_txtr[0]);
    destroy_menu_part2(menu);
    free(menu);
}

static void switch_to_game_win(game_t *game)
{
    sfMusic_stop(game->music[2]);
    sfMusic_stop(game->music[0]);
    sfMusic_play(game->music[1]);
    sfRenderWindow_setMouseCursorVisible(GAME_WIN, sfFalse);
    sfRenderWindow_setMouseCursorGrabbed(game->window, sfTrue);
}

static void switch_to_menus_win(game_t *game, int prev_menu)
{
    sfMusic_stop(game->music[2]);
    sfMusic_stop(game->music[1]);
    if (prev_menu == GAME_WINDOW || prev_menu == PAUSE_WINDOW)
        sfMusic_play(game->music[0]);
    sfRenderWindow_setMouseCursorVisible(GAME_WIN, sfTrue);
    sfRenderWindow_setMouseCursorGrabbed(game->window, sfFalse);
}

void switch_menu(game_t *game, int menu_index)
{
    int prev_menu = game->menu_index;

    game->menu_index = menu_index;
    clean_menu(game->menu);
    game->menu->buttons = NULL;
    game->menu->texts = NULL;
    menu_tab[menu_index](game);
    if (menu_index == GAME_WINDOW) {
        switch_to_game_win(game);
    } else if (menu_index == PAUSE_WINDOW) {
        sfMusic_stop(game->music[1]);
        sfMusic_play(game->music[2]);
        sfRenderWindow_setMouseCursorVisible(GAME_WIN, sfTrue);
        sfRenderWindow_setMouseCursorGrabbed(game->window, sfFalse);
    } else {
        switch_to_menus_win(game, prev_menu);
    }
}

static bool create_menu_images(menu_t *menu)
{
    menu->background_txtr = sfTexture_createFromFile(
        MENU_BACKGROUND_IMAGE, NULL);
    menu->background = sfSprite_create();
    if (!menu->background_txtr || !menu->background)
        return false;
    sfSprite_setTexture(menu->background, menu->background_txtr, sfTrue);
    menu->t_game_over = sfTexture_createFromFile(
        GAME_OVER_IMAGE, NULL);
    menu->game_over = sfSprite_create();
    if (!menu->game_over || !menu->t_game_over)
        return false;
    sfSprite_setTexture(menu->game_over, menu->t_game_over, sfTrue);
    sfSprite_setScale(menu->game_over, (sfVector2f){2, 2});
    sfSprite_setPosition(menu->game_over, (sfVector2f){100, 100});
    return true;
}

menu_t *create_menu(void)
{
    menu_t *menu = calloc(1, sizeof(menu_t));

    if (!menu)
        return NULL;
    if (!create_menu_images(menu)){
        destroy_menu(menu);
        return NULL;
    }
    menu->res_index = 0;
    menu->fps_index = 2;
    menu->timer = sfClock_create();
    menu->font[0] = sfFont_createFromFile(EXPOSE_FONT);
    menu->font[1] = sfFont_createFromFile(HELVETICA_FONT);
    if (!create_blur_shader(menu) || !menu->timer || !menu->background ||
        !menu->font[0] || !menu->font[1] || !create_titles(menu) ||
        !create_input_button(menu)){
        destroy_menu(menu);
        return NULL;
    }
    return menu;
}
