/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** update menu->texts and menu->buttons to create a specific menu*
*/

#include "my.h"

static void check_buttons_and_texts(menu_t *menu, int nb_texts, int nb_buttons)
{
    for (int i = 0; i < nb_texts; i++){
        if (!menu->texts[i]){
            clean_menu(menu);
            return;
        }
        sfText_setFont(menu->texts[i]->text, menu->font[0]);
    }
    menu->texts[nb_texts] = NULL;
    for (int i = 0; i < nb_buttons; i++){
        if (!menu->buttons[i]){
            clean_menu(menu);
            return;
        }
    }
    menu->buttons[nb_buttons] = NULL;
}

static bool create_buttons_and_texts(menu_t *menu, int nb_texts, int nb_buttons)
{
    menu->texts = malloc(sizeof(text_t) * (nb_texts + 1));
    menu->buttons = malloc(sizeof(button_t) * (nb_buttons + 1));
    if (!menu->texts || !menu->buttons){
        clean_menu(menu);
        return false;
    }
    return true;
}

void create_intro_menu(game_t *game)
{
    if (!create_buttons_and_texts(game->menu, 1, 0))
        return;
    game->menu->texts[0] = create_text("Press Enter to start the game",
        &((sfVector2f){160, 450}), 50,
        text_fade);
    check_buttons_and_texts(game->menu, 1, 0);
}

void create_main_menu(game_t *game)
{
    if (!create_buttons_and_texts(game->menu, 0, 3))
        return;
    game->menu->buttons[0] = create_button("./assets/images/play_button.png",
        "./assets/images/play_button_hover.png", &((sfVector2f){270.0f, 100.f}),
        play_button);
    game->menu->buttons[1] = create_button("./assets/images/settings_button.png"
        , "./assets/images/settings_button_hover.png",
        &((sfVector2f){270.0f, 250.f}), setting_button);
    game->menu->buttons[2] = create_button("./assets/images/quit_button.png",
        "./assets/images/quit_button_hover.png", &((sfVector2f){270.0f, 400.f}),
        quit_button);
    check_buttons_and_texts(game->menu, 0, 3);
}

static void create_setting_menu3(game_t *game)
{
    game->menu->texts[7] = create_text("Inputs",
        &((sfVector2f){100.0f, 250.f}), 45, static_text);
    game->menu->texts[8] = create_text("Up", &((sfVector2f){450.0f, 220.f}),
        25, static_text);
    game->menu->texts[9] = create_text("Left", &((sfVector2f){540.0f, 220.f}),
        25, static_text);
    game->menu->texts[10] = create_text("Back", &((sfVector2f){630.0f, 220.f}),
        25, static_text);
    game->menu->texts[11] = create_text("Right", &((sfVector2f){720.0f, 220.f}),
        25, static_text);
    check_buttons_and_texts(game->menu, 12, 7);
}

static void create_setting_menu2(game_t *game)
{
    game->menu->buttons[5] = create_button("./assets/images/left_button.png",
        "./assets/images/left_button_hover.png", &((sfVector2f){440.0f, 300.f}),
        left_fps_button);
    game->menu->buttons[6] = create_button("./assets/images/right_button.png",
        "./assets/images/right_button_hover.png", &((sfVector2f){580.0f,
                300.f}), right_fps_button);
    game->menu->texts[1] = create_text("Volume", &((sfVector2f){100.0f, 400.f}),
        50, static_text);
    game->menu->texts[2] = create_text("Settings", &((sfVector2f){220.0f,
                -20}), 130, static_text);
    game->menu->texts[3] = create_text("Resolution",
        &((sfVector2f){100.0f, 350.f}), 50, static_text);
    game->menu->texts[4] = create_text(NULL, &((sfVector2f){500.0f, 350.f}), 45,
        resolution_text);
    game->menu->texts[5] = create_text("Framerate Limit",
        &((sfVector2f){100.0f, 300.f}), 45, static_text);
    game->menu->texts[6] = create_text(NULL, &((sfVector2f){500.0f, 300.f}), 45,
        framerate_text);
    create_setting_menu3(game);
}

void create_setting_menu(game_t *game)
{
    if (!create_buttons_and_texts(game->menu, 12, 7))
        return;
    game->menu->buttons[0] = create_button("./assets/images/left_button.png",
        "./assets/images/left_button_hover.png", &((sfVector2f){440.0f, 400.f}),
        left_volume_button);
    game->menu->buttons[1] = create_button("./assets/images/right_button.png",
        "./assets/images/right_button_hover.png", &((sfVector2f){580.0f,
                400.f}), right_volume_button);
    game->menu->buttons[2] = create_button("./assets/images/return_button.png",
        "./assets/images/return_button_hover.png", &((sfVector2f){5.0f, 500.f}),
        return_main_button);
    game->menu->buttons[3] = create_button("./assets/images/left_button.png",
        "./assets/images/left_button_hover.png", &((sfVector2f){440.0f, 350.f}),
        left_res_button);
    game->menu->buttons[4] = create_button("./assets/images/right_button.png",
        "./assets/images/right_button_hover.png", &((sfVector2f){680.0f,
                350.f}), right_res_button);
    game->menu->texts[0] = create_text(NULL, &((sfVector2f){500.0f, 400.f}), 45,
        volume_text);
    create_setting_menu2(game);
}

void game_menu(game_t *game)
{
    (void)game;
    return;
}

void create_pause_menu(game_t *game)
{
    if (!create_buttons_and_texts(game->menu, 0, 3))
        return;
    game->menu->buttons[0] = create_button("./assets/images/resume_button.png",
        "./assets/images/resume_button_hover.png", &((sfVector2f){270.0f,
                100.f}), play_button);
    game->menu->buttons[1] = create_button("./assets/images/settings_button.png"
        , "./assets/images/settings_button_hover.png",
        &((sfVector2f){270.0f, 250.f}), setting_button);
    game->menu->buttons[2] = create_button("./assets/images/quit_button.png",
        "./assets/images/quit_button_hover.png", &((sfVector2f){270.0f, 400.f}),
        quit_button);
    check_buttons_and_texts(game->menu, 0, 3);
}
