/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** draw sprites and the such
*/

#include "my.h"

static sfVector2f entity_to_camera(player_t *player, entity_t *en)
{
    sfVector2f cam;
    float dir_x;
    float dir_y;
    float plane_x;
    float plane_y;
    float dx;
    float dy;
    float inv;

    dir_x = cosf(player->angle);
    dir_y = sinf(player->angle);
    plane_x = -sinf(player->angle) * tanf(FOV / 2);
    plane_y = cosf(player->angle) * tanf(FOV / 2);
    dx = en->x - player->x;
    dy = en->y - player->y;
    inv = 1.f / (plane_x * dir_y - dir_x * plane_y);
    cam.x = inv * (dir_y * dx - dir_x * dy);
    cam.y = inv * (-plane_y * dx + plane_x * dy);
    return cam;
}

static int get_en_draw_params(player_t *player, entity_t *en,
    en_draw_t *params)
{
    sfVector2f cam;
    float dx = en->x - player->x;
    float dy = en->y - player->y;
    float dist;

    cam = entity_to_camera(player, en);
    if (cam.y <= 0.1f)
        return 0;
    dist = fabs(dx) + fabs(dy);
    if (dist <= 0.1f)
        return 0;
    params->size = abs((int)((TILE_SIZE / dist) * 500));
    params->x = (SCREEN_WIDTH / 2) * (1 + cam.x / cam.y);
    params->cam_y = cam.y;
    return 1;
}

static void draw_entity(game_t *game, player_t *player, entity_t *en)
{
    en_draw_t params;

    if (!get_en_draw_params(player, en, &params))
        return;
    if (params.x < 0 || params.x >= SCREEN_WIDTH)
        return;
    if (params.cam_y >= game->zbuffer[params.x])
        return;
    sfSprite_setScale(en->sprite,
        (sfVector2f){params.size / 32.f, params.size / 32.f});
    sfSprite_setPosition(en->sprite,
        (sfVector2f){params.x, (SCREEN_HEIGHT / 2.f + params.size) +
            sin(player->bobbing) * BOBBING_INTENSITY});
    sfRenderWindow_drawSprite(game->window, en->sprite, NULL);
}

static int count_alive_entities(entity_t *entity)
{
    int count = 0;

    while (entity) {
        if (entity->alive)
            count++;
        entity = entity->next;
    }
    return count;
}

static int fill_sorted_entities(entity_t *entity, en_sort_t *sorted,
    player_t *player)
{
    int i = 0;
    float dx;
    float dy;

    while (entity) {
        if (entity->alive) {
            dx = entity->x - player->x;
            dy = entity->y - player->y;
            sorted[i].entity = entity;
            sorted[i].dist = dx * dx + dy * dy;
            i++;
        }
        entity = entity->next;
    }
    return i;
}

static void sort_pass(en_sort_t *sorted, int count, int index)
{
    en_sort_t tmp;

    for (int i = index + 1; i < count; i++) {
        if (sorted[index].dist < sorted[i].dist) {
            tmp = sorted[index];
            sorted[index] = sorted[i];
            sorted[i] = tmp;
        }
    }
}

static void sort_entities(en_sort_t *sorted, int count)
{
    for (int j = 0; j < count - 1; j++)
        sort_pass(sorted, count, j);
}

static void draw_sorted_entities(game_t *game, player_t *player,
    en_sort_t *sorted, int count)
{
    for (int i = 0; i < count; i++)
        draw_entity(game, player, sorted[i].entity);
}

void draw_entities(game_t *game, player_t *player)
{
    entity_t *entity = game->entities;
    en_sort_t *sorted = NULL;
    int count = count_alive_entities(entity);

    if (count == 0)
        return;
    sorted = malloc(sizeof(*sorted) * count);
    if (!sorted)
        return;
    entity = game->entities;
    fill_sorted_entities(entity, sorted, player);
    sort_entities(sorted, count);
    draw_sorted_entities(game, player, sorted, count);
    free(sorted);
}
