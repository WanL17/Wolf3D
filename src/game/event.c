/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** This is where the events are managed (closing windows, inputs, etc.)
*/
#include "my.h"

static void check_ammo(player_t *pl, int cur, int max)
{
    if (cur >= max * 80 / 100) {
        sfSprite_setTexture(pl->ammo, pl->t_ammo[0], sfTrue);
        return;
    }
    if (cur <= max * 79 / 100 && cur >= max * 55 / 100) {
        sfSprite_setTexture(pl->ammo, pl->t_ammo[1], sfTrue);
        return;
    }
    if (cur <= max * 54 / 100 && cur >= max * 30 / 100) {
        sfSprite_setTexture(pl->ammo, pl->t_ammo[2], sfTrue);
        return;
    }
    if (cur <= max * 29 / 100 && cur >= max * 1 / 100)
        sfSprite_setTexture(pl->ammo, pl->t_ammo[3], sfTrue);
}

static void check_health(player_t *pl)
{
    if (pl->hp >= 80) {
        sfSprite_setTexture(pl->health, pl->health_max, sfTrue);
        return;
    }
    if (pl->hp <= 79 && pl->hp >= 55) {
        sfSprite_setTexture(pl->health, pl->health_high, sfTrue);
        return;
    }
    if (pl->hp <= 54 && pl->hp >= 30) {
        sfSprite_setTexture(pl->health, pl->health_mid, sfTrue);
        return;
    }
    if (pl->hp <= 29 && pl->hp >= 5)
        sfSprite_setTexture(pl->health, pl->health_low, sfTrue);
}

static void key_button_pressed(game_t *game, player_t *pl)
{
    if (game->event.key.code == sfKeyEscape) {
        switch_menu(game, PAUSE_WINDOW);
        return;
    }
    if (game->event.key.code == sfKeyM) {
        game->minimap_visible = !game->minimap_visible;
        return;
    }
    if (game->event.key.code == sfKeyNum1) {
        pl->cur_weapon = KNIFE_WEAPON;
        return;
    }
    if (game->event.key.code == sfKeyNum2)
        pl->cur_weapon = GUN_WEAPON;
}

static void check_event(game_t *game)
{
    switch (game->event.type) {
        case sfEvtClosed:
            sfRenderWindow_close(game->window);
            break;
        case sfEvtResized:
            break;
        default:
            break;
    }
}

static void check_menu_event(game_t *game, player_t *player,
    sfVector2i *mouse_loc)
{
    if (sfKeyboard_isKeyPressed(sfKeyEnter) && game->menu_index == INTRO_MENU){
        switch_menu(game, MAIN_MENU);
        return;
    }
    switch (game->event.type) {
        case sfEvtMouseButtonPressed:
            event_pressed_buttons(game, mouse_loc);
            break;
        case sfEvtMouseButtonReleased:
            event_released_buttons(game, player, mouse_loc);
            break;
        default:
            break;
    }
}

static void check_game_event(game_t *game, player_t *player)
{
    check_health(player);
    check_ammo(player, player->weapons[player->cur_weapon].cur_ammo,
        player->weapons[player->cur_weapon].max_ammo);
    if (player->hp <= 0){
        switch_menu(game, GAME_OVER_WINDOW);
        player->hp = MAX_HEALTH;
        return;
    }
    switch (game->event.type) {
        case sfEvtMouseButtonPressed:
            use_weapons(game, player);
            break;
        case sfEvtKeyPressed:
            key_button_pressed(game, player);
            break;
        default:
            break;
    }
}

void scale_mouse(game_t *game, sfVector2i *mouse_loc)
{
    sfVector2u window_size = sfRenderWindow_getSize(game->window);
    sfVector2f window_fsize = {window_size.x, window_size.y};

    mouse_loc->x *= (SCREEN_WIDTH / window_fsize.x);
    mouse_loc->y *= (SCREEN_HEIGHT / window_fsize.y);
}

void handle_event(game_t *game, player_t *pl)
{
    sfVector2i mouse_loc = sfMouse_getPositionRenderWindow(game->window);

    while (sfRenderWindow_pollEvent(game->window, &game->event)){
        if (game->menu_index != GAME_WINDOW) {
            scale_mouse(game, &mouse_loc);
            check_menu_event(game, pl, &mouse_loc);
        }
        if (game->menu_index == GAME_WINDOW)
            check_game_event(game, pl);
        check_event(game);
    }
    if (game->menu_index == GAME_WINDOW) {
        if (sfJoystick_isConnected(0) == sfTrue)
            controller_support(game, pl);
        if (sfJoystick_isConnected(0) == sfFalse){
            key_movement(game, pl);
            key_cam(game, pl, &mouse_loc);
        }
        make_entities_spawn(game);
    }
}
