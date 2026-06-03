/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** equipment.h
*/

#ifndef EQUIPMENT_H
    #define EQUIPMENT_H

    #include "my.h"

// Macros Knife :
    #define KNIFE_WEAPON 0
    #define KNIFE_WIDTH 287
    #define KNIFE_HEIGHT 216
    #define KNIFE_STATES 3
    #define KNIFE_SPEED 0.1
    #define KNIFE_AMMO 1
    #define KNIFE_DAMAGE 40
    #define KNIFE_SOUND "./assets/audio/knife_sound.mp3"
    #define KNIFE_SPRITE_SHEET "./assets/images/knife_slash.png"

// Macros Gun :
    #define GUN_WEAPON 1
    #define GUN_SPEED 0.1
    #define GUN_WIDTH 64
    #define GUN_HEIGHT 64
    #define GUN_STATES 5
    #define GUN_AMMO 40
    #define GUN_BULLET_DAMAGE 20
    #define GUN_SPRITE_SHEET "./assets/images/gun_sprite.png"
    #define GUN_SOUND "./assets/audio/gun_sound.mp3"

typedef struct weapon_s {
    sfClock *clock;
    sfSprite *sprite;
    sfTexture *txtr;
    float speed;
    int states;
    sfIntRect txtr_rect;
    int damage;
    int time;
    int cur_ammo;
    int max_ammo;
    sfVector2i t_size;
    sfMusic *sound;
} weapon_t;

#endif
