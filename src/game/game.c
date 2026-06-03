/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** game
*/
#include "my.h"

int is_wall(int x, int y, game_t *game)
{
    int map_x = x / TILE_SIZE;
    int map_y = y / TILE_SIZE;

    if (x < 0 || y < 0)
        return 1;
    if (map_x < 0 || map_x >= game->map->width ||
        map_y < 0 || map_y >= game->map->height)
        return 1;
    return game->map->grid[map_y][map_x] == 1;
}

static void draw_game(game_t *game, player_t *pl)
{
    draw_sky(game);
    sfSprite_setPosition(GAME_SPR, (sfVector2f){0, sin(pl->bobbing) *
            BOBBING_INTENSITY});
    sfRenderWindow_drawSprite(GAME_WIN, GAME_SPR, NULL);
    draw_sprites(game, pl);
    sfRenderWindow_drawSprite(game->window, pl->hud, NULL);
    if (pl->hp > 0)
        sfRenderWindow_drawSprite(game->window, pl->health, NULL);
    if (pl->weapons[pl->cur_weapon].cur_ammo > 0)
        sfRenderWindow_drawSprite(game->window, pl->ammo, NULL);
    if (game->minimap_visible)
        create_minimap(game, pl);
    display_score(game, pl);
}

static void update_game(game_t *game, player_t *pl)
{
    cast_all_rays(GAME_FB, pl, game);
    sfTexture_updateFromPixels(GAME_TXT, GAME_FB->pixels, 800, 600, 0, 0);
    update_sprites(game, pl);
}

void game_loop(game_t *game, player_t *pl)
{
    sfColor c_floor = sfColor_fromRGBA(55, 45, 64, 255);

    sfMusic_play(game->music[0]);
    switch_menu(game, INTRO_MENU);
    sfClock_restart(game->difficulty);
    while (sfRenderWindow_isOpen(game->window)) {
        sfRenderWindow_clear(GAME_WIN, c_floor);
        increase_difficulty(game);
        if (game->menu_index == GAME_WINDOW)
            update_game(game, pl);
        draw_game(game, pl);
        handle_event(game, pl);
        if (game->menu_index != GAME_WINDOW)
            render_menu(game, pl);
        sfRenderWindow_display(GAME_WIN);
    }
}
