/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** Handles player control
*/
#include "my.h"

static int player_bubbled(player_t *player, game_t *game, float key_radian,
    int boost)
{
    int x_possible = 1;
    int y_possible = 1;
    int base_x = player->x + cos(player->angle + key_radian) * WALK_SPD * boost;
    int base_y = player->y + sin(player->angle + key_radian) * WALK_SPD * boost;

    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            x_possible &= !is_wall(base_x + x * PLAYER_BUBBLE, player->y + y *
                PLAYER_BUBBLE, game);
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            y_possible &= !is_wall(player->x + x * PLAYER_BUBBLE, base_y + y *
                PLAYER_BUBBLE, game);
    return x_possible + y_possible * 2;
}

void angle_to_player_movement(player_t *pl, float key_radian, game_t *game)
{
    int possible_movement;
    float boost = 1;

    if (sfKeyboard_isKeyPressed(sfKeyLShift) ||
        ((game->event.type == sfEvtJoystickButtonPressed
                && game->event.joystickButton.button == CONTROLLER_B)))
        boost = 2;
    possible_movement = player_bubbled(pl, game, key_radian, boost);
    if (possible_movement & 1)
        pl->x += cos(pl->angle + key_radian) * WALK_SPD * boost;
    if (possible_movement & 2)
        pl->y += sin(pl->angle + key_radian) * WALK_SPD * boost;
}

void neutralise_bobbing(player_t *player)
{
    if (!player->bobbing)
        return;
    if (player->bobbing < M_PI){
        player->bobbing += BOBBING_SPEED;
        if (player->bobbing >= M_PI)
            player->bobbing = 0;
        return;
    }
    player->bobbing += BOBBING_SPEED;
    if (player->bobbing >= 2 * M_PI)
        player->bobbing = 0;
}

void key_movement(game_t *game, player_t *pl)
{
    sfKeyCode directions[4] = {game->inputs[2], game->inputs[1],
        game->inputs[0], game->inputs[3]};

    for (int i = 0; i < 4; i++){
        if (sfKeyboard_isKeyPressed(directions[i]))
            pl->inputs[i] = true;
        if (!sfKeyboard_isKeyPressed(directions[i]))
            pl->inputs[i] = false;
    }
}

void key_cam(game_t *game, player_t *pl, sfVector2i *mouse_loc)
{
    sfVector2u window_size = sfRenderWindow_getSize(game->window);
    float diff = mouse_loc->x - window_size.x / 2.0;

    pl->new_angle = CAM_SENSIBILITY * diff;
    sfMouse_setPositionRenderWindow((sfVector2i){window_size.x / 2.0,
            window_size.y / 2.0}, game->window);
}
