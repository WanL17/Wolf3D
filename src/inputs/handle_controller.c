/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** handle_controller.c
*/
#include "my.h"

static void decreasing_ammo(player_t *pl, weapon_t *weapon)
{
    if (pl->cur_weapon != KNIFE_WEAPON)
        weapon->cur_ammo--;
}

static void controller_camera(player_t *pl)
{
    pl->new_angle = 0;
    if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickU) < DRIFT_LIMIT * -1)
        pl->new_angle -= CONTROLLER_SENSITIVITY;
    else if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickZ)
        < DRIFT_LIMIT * -1)
        pl->new_angle -= CONTROLLER_SENSITIVITY;
    if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickU) > DRIFT_LIMIT)
        pl->new_angle += CONTROLLER_SENSITIVITY;
    else if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickZ) > DRIFT_LIMIT)
        pl->new_angle += CONTROLLER_SENSITIVITY;
}

static void controller_movement(player_t *pl)
{
    for (int i = 0; i < 4; i++)
        pl->inputs[i] = false;
    if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickY) > DRIFT_LIMIT)
        pl->inputs[0] = true;
    if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickX) < -1 * DRIFT_LIMIT)
        pl->inputs[1] = true;
    if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickY) < -1 * DRIFT_LIMIT)
        pl->inputs[2] = true;
    if (sfJoystick_getAxisPosition(CONTROLLER, sfJoystickX) > DRIFT_LIMIT)
        pl->inputs[3] = true;
}

void use_weapons_controller(game_t *game, player_t *pl)
{
    weapon_t *weapon = &pl->weapons[pl->cur_weapon];

    if (weapon->cur_ammo > 0) {
        if (weapon->time <= 0) {
            decreasing_ammo(pl, weapon);
            weapon->time = weapon->states + 1;
            sfClock_restart(weapon->clock);
            sfMusic_play(weapon->sound);
        }
        if (pl->cur_weapon == KNIFE_WEAPON)
            detect_an_enemy_knife(pl, game->entities, weapon);
        else
            detect_an_enemy_gun(game, pl, game->entities, weapon);
    }
}

static void controller_buttons(game_t *game, player_t *pl)
{
    if (game->event.type == sfEvtJoystickButtonPressed) {
        switch (game->event.joystickButton.button) {
            case CONTROLLER_A :
                use_weapons_controller(game, pl);
                return;
            case CONTROLLER_R :
                pl->cur_weapon = GUN_WEAPON;
                return;
            case CONTROLLER_L :
                pl->cur_weapon = KNIFE_WEAPON;
                return;
            default :
                return;
        }
    }
}

void controller_support(game_t *game, player_t *pl)
{
    if (sfJoystick_isConnected(CONTROLLER) == sfFalse)
        return;
    controller_movement(pl);
    controller_camera(pl);
    controller_buttons(game, pl);
}
