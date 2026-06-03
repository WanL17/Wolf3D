/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** init
*/
#include "my.h"

bool init_player(player_t *player, game_t *game)
{
    if (!create_ammo_hp_textures(player) || !create_score_texts(game, player)
        || !create_hud(game, player) || !create_weapons(player, game))
        return false;
    player->health = create_health_sprite(player->health_max, player->hud);
    player->ammo = create_ammo_sprite(player->t_ammo[MAX_STATE], player->hud);
    if (!player->ammo || !player->health)
        return false;
    player->x = game->map->spawn_x * TILE_SIZE;
    player->y = game->map->spawn_y * TILE_SIZE;
    player->hp = MAX_HEALTH;
    return true;
}

bool init_assets(game_t *game)
{
    game->framebuffer = create_fb(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->texture = sfTexture_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    game->sprite = sfSprite_create();
    game->wall = sfImage_createFromFile(WALL_IMAGE);
    game->sky = sfSprite_create();
    game->sky_txtr = sfTexture_createFromFile(SKY_IMAGE, NULL);
    game->music[0] = sfMusic_createFromFile(MENU_MUSIC);
    game->music[1] = sfMusic_createFromFile(GAME_MUSIC);
    game->music[2] = sfMusic_createFromFile(PAUSE_MUSIC);
    if (!game->framebuffer || !game->texture || !game->sprite || !game->wall ||
        !game->sky || !game->sky_txtr || !game->music[0] || !game->music[1])
        return false;
    sfSprite_setTexture(game->sprite, game->texture, sfTrue);
    sfSprite_setTexture(game->sky, game->sky_txtr, sfTrue);
    sfMusic_setLoop(game->music[0], sfTrue);
    sfMusic_setLoop(game->music[1], sfTrue);
    sfMusic_setLoop(game->music[2], sfTrue);
    return true;
}

map_t *init_map(void)
{
    map_t *map = malloc(sizeof(map_t));

    if (!map)
        return NULL;
    if (!load_map(DEFAULT_MAP, map)) {
        free_map(map);
        return NULL;
    }
    return map;
}
