/*
** EPITECH PROJECT, 2025
** G-ING-210-LYN-2-1-wolf3d-1
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H
    #define _GNU_SOURCE

/////////////////////////////////// INCLUDE LIBRARIES /////////////////////////
    #include <stdarg.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <math.h>
    #include <time.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <stdbool.h>
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Audio.h>
    #include <SFML/Audio/SoundBuffer.h>
    #include <SFML/Audio/Sound.h>
    #include <SFML/Audio/Types.h>
    #include <SFML/System/Time.h>
    #include <SFML/System/Vector3.h>
    #include <SFML/System/Export.h>
    #include <SFML/Window/Types.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/OpenGL.h>
    #include <X11/Xlib.h>
    #include <X11/cursorfont.h>
    #include "framebuffer.h"
    #include "map.h"
    #include "menu.h"
    #include "equipment.h"
    #include "game.h"

/////////////////////////////////// MACROS ////////////////////////////////////
    #define DEFAULT 0
    #define TRUE 1
    #define FALSE 0
    #define EXPOSE_FONT "./assets/fonts/Expose.otf"
    #define HELVETICA_FONT "./assets/fonts/Helvetica.ttf"
    #define GAME_MUSIC "./assets/audio/game_music.mp3"
    #define MENU_MUSIC "./assets/audio/menu_music.mp3"
    #define PAUSE_MUSIC "./assets/audio/pause_music.mp3"
    #define SKY_IMAGE "assets/images/sky.png"
    #define WALL_IMAGE "assets/images/wall.png"
    #define DEFAULT_MAP "assets/maps/default"
    #define MENU_BACKGROUND_IMAGE "./assets/images/menu_background.png"
    #define GAME_OVER_IMAGE "./assets/images/toobad.png"

/////////////////////////////////// STRUCTURES ////////////////////////////////
typedef struct game_s game_t;

typedef void (*menus_nav_t)(game_t *game);

extern const menus_nav_t menu_tab[];

#endif
