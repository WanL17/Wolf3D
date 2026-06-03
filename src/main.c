/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** calls stuff
*/
#include "my.h"

static void more_destroy_game(game_t *game)
{
    entity_t *next;

    if (game->map)
        free_map(game->map);
    if (game->enemy_txtr)
        sfTexture_destroy(game->enemy_txtr);
    while (game->entities){
        next = game->entities->next;
        sfSprite_destroy(game->entities->sprite);
        free(game->entities);
        game->entities = next;
    }
    if (game->menu)
        destroy_menu(game->menu);
    free(game->zbuffer);
    for (int i = 0; i < 3; i++)
        if (game->music[i])
            sfMusic_destroy(game->music[i]);
    sfClock_destroy(game->difficulty);
}

void destroy_game(game_t *game)
{
    if (!game)
        return;
    if (game->minimap)
        sfSprite_destroy(game->minimap);
    if (game->window)
        sfRenderWindow_destroy(game->window);
    if (game->texture)
        sfTexture_destroy(game->texture);
    if (game->sky_txtr)
        sfTexture_destroy(game->sky_txtr);
    if (game->sprite)
        sfSprite_destroy(game->sprite);
    if (game->sky)
        sfSprite_destroy(game->sky);
    if (game->wall)
        sfImage_destroy(game->wall);
    if (game->framebuffer)
        destroy_fb(game->framebuffer);
    more_destroy_game(game);
    free(game);
}

static void more_player_part_destruction(player_t *player)
{
    for (int i = 0; i < 4; i++)
        if (player->t_ammo[i])
            sfTexture_destroy(player->t_ammo[i]);
    for (int i = 0; i < 2; i++){
        if (player->weapons[i].clock)
            sfClock_destroy(player->weapons[i].clock);
        if (player->weapons[i].sprite)
            sfSprite_destroy(player->weapons[i].sprite);
        if (player->weapons[i].txtr)
            sfTexture_destroy(player->weapons[i].txtr);
        if (player->weapons[i].sound)
            sfMusic_destroy(player->weapons[i].sound);
    }
}

static void destroy_player_parts(player_t *player)
{
    for (int i = 0; i < 2; i++)
        if (player->scores[i])
            sfText_destroy(player->scores[i]);
    if (player->hud)
        sfSprite_destroy(player->hud);
    if (player->hud_txtr)
        sfTexture_destroy(player->hud_txtr);
    if (player->health)
        sfSprite_destroy(player->health);
    if (player->health_max)
        sfTexture_destroy(player->health_max);
    if (player->health_mid)
        sfTexture_destroy(player->health_mid);
    if (player->health_low)
        sfTexture_destroy(player->health_low);
    if (player->health_high)
        sfTexture_destroy(player->health_high);
    if (player->ammo)
        sfSprite_destroy(player->ammo);
    more_player_part_destruction(player);
}

int main(void)
{
    game_t *game = init_game();
    player_t player = {0};

    if (!game)
        return EXIT_FAILURE;
    if (!init_player(&player, game)){
        destroy_game(game);
        return EXIT_FAILURE;
    }
    game_loop(game, &player);
    destroy_game(game);
    destroy_player_parts(&player);
    return EXIT_SUCCESS;
}
