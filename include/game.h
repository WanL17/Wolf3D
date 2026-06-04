/*
** EPITECH PROJECT, 2026
** wolf3D
** File description:
** TODO: I'd like to implement player inside the game struct later,
** it will make it easier to call it.
*/

#ifndef GAME_H
    #define GAME_H

    #include "my.h"

    #ifndef M_PI
        #define M_PI 3.14159265358979323846
    #endif

/////////////////////////////////// MACROS ////////////////////////////////////

// Function Macros :
    #define ABS(x) ((x) < 0 ? -(x) : (x))

// Shortcut Macros :
    #define GAME_FB game->framebuffer
    #define GAME_WIN game->window
    #define GAME_TXT game->texture
    #define GAME_SPR game->sprite

// Game Macros :
    #define TILE_SIZE 64
    #define FOV (M_PI / 3)
    #define NUM_RAYS 800
    #define SCREEN_HEIGHT 600
    #define SCREEN_WIDTH 800
    #define PARTICULE_NB 20
    #define REFRESH_SECONDS 0.2
    #define SKY_SPEED 100

// WALL MACROS :
    #define WALL_WIDTH 584
    #define WALL_HEIGHT 350

// Menu Macros :
    #define INTRO_MENU 0
    #define MAIN_MENU 1
    #define SETTINGS_MENU 2
    #define PAUSE_WINDOW 3
    #define GAME_WINDOW 4
    #define GAME_OVER_WINDOW 5

// HUD MACROS
    #define MAX_STATE 0
    #define HIGH_STATE 1
    #define MID_STATE 2
    #define LOW_STATE 3

// PLAYER MACROS :
    #define MAX_HEALTH 100
    #define PLAYER_BUBBLE 10
    #define WALK_SPD 3
    #define BOBBING_SPEED 0.2
    #define BOBBING_INTENSITY 10
    #define CAM_SENSIBILITY 0.001

// CONTROLLER MACROS :
    #define DRIFT_LIMIT 15
    #define CONTROLLER_SENSITIVITY 0.05
    #define CONTROLLER 0
    #define CONTROLLER_A 1
    #define CONTROLLER_B 2
    #define CONTROLLER_L 4
    #define CONTROLLER_R 5

// ENTITIES/ENEMIES MACROS :
    #define ENTITY_SPEED 3
    #define ENTITY_WIDTH 64
    #define ENTITY_HEIGHT 64
    #define ENTITY_DAMAGE 10
    #define ENTITY_HEALTH 40
    #define ENEMY_BUBBLE 50
    #define ENTITY_SPRITE_SHEET "assets/images/mutant_sprites.png"

// RESOLUTION MACROS :
    #define WINDOWED 0
    #define FULLSCREEN 1

/////////////////////////////////// STRUCTURES ////////////////////////////////

//Forward Declaration:
struct menu_s;

// STRUCTURE FOR THE PARTICULES :
typedef struct particule_s {
    sfRectangleShape *pixel;
    sfClock *clock;
    sfVector2f pos[PARTICULE_NB];
    bool start;
    bool first_iteration;
} particule_t;

// STRUCTURE FOR THE RAYS OF THE RAYCAST :
typedef struct {
    float dist;
    float x;
    float y;
} ray_t;

// STRUCTURE FOR THE PLAYER :
typedef struct {
    float x;
    float y;
    float angle;
    int hp;
    sfText *scores[2];
    sfSprite *hud;
    sfTexture *hud_txtr;
    sfSprite *health;
    sfTexture *health_max;
    sfTexture *health_mid;
    sfTexture *health_low;
    sfTexture *health_high;
    sfSprite *ammo;
    sfTexture *t_ammo[4];
    float bobbing;
    weapon_t weapons[2];
    int cur_weapon;
    bool inputs[4];
    float new_angle;
    int score;
} player_t;

// STRUCTURE FOR THE ENTITIES :
typedef struct entity_s entity_t;

// STRUCTURE FOR THE GAME :
typedef struct game_s {
    sfSprite *minimap;
    sfRenderWindow *window;
    sfTexture *texture;
    sfTexture *sky_txtr;
    sfTexture *enemy_txtr;
    sfSprite *sprite;
    sfSprite *sky;
    sfEvent event;
    sfImage *wall;
    framebuffer_t *framebuffer;
    ray_t ray;
    map_t *map;
    struct entity_s *entities;
    int menu_index;
    struct menu_s *menu;
    sfKeyCode inputs[4];
    int volume;
    float *zbuffer;
    sfMusic *music[3];
    bool minimap_visible;
    sfClock *difficulty;
    int ent_spawn;
    particule_t *particule;
    bool ent_hit;
} game_t;

// ENUMERATION OF THE DIFFERENT ENTITY TYPES :
typedef enum entity_type_e {
    ENTITY_PICKUP_HP,
    ENTITY_PICKUP_AMMO,
    ENTITY_ENEMY,
    ENTITY_BULLET
} entity_type_t;

// STRUCTURE FOR AN ENTITY :
struct entity_s {
    entity_type_t type;
    float x;
    float y;
    int move;
    int alive;
    int health;
    sfSprite *sprite;
    void (*update)(struct entity_s *entity, game_t *game, player_t *player);
    struct entity_s *next;
};

// STRUCTURE FOR THE BUTTONS :
typedef struct button_s {
    sfSprite *sprite;
    sfTexture *txtr;
    sfTexture *hover_txtr;
    void (*action)(game_t *, player_t *, struct button_s *);
} button_t;

// STRUCTURE FOR THE TEXTS :
typedef struct text_s {
    sfText *text;
    void (*action)(game_t *, player_t *, struct text_s *);
} text_t;

// STRUCTURE FOR THE MENUS :
typedef struct menu_s {
    text_t **texts;
    button_t **buttons;
    sfClock *timer;
    sfTexture *background_txtr;
    sfSprite *background;
    sfFont *font[2];
    sfSprite *title[2];
    sfTexture *title_txtr;
    sfSprite *blur[2];
    sfTexture *blur_txtr[2];
    int res_index;
    int fps_index;
    sfSprite *input_but;
    sfTexture *input_but_txtr;
    sfTexture *t_game_over;
    sfSprite *game_over;
} menu_t;

typedef struct {
    int size;
    int x;
    float cam_y;
} en_draw_t;

typedef struct {
    entity_t *entity;
    float dist;
} en_sort_t;

// Array with all the possible resolutions
extern const sfVector2u res_screen[];

// Array with all the possible framerates
extern const int fps_choice[];

// Array with all the possible inputs key position on the texture
extern const sfVector2f inputs_nav[];

/////////////////////////////////// FUNCTIONS /////////////////////////////////

// Menu Handling :
void clean_menu(menu_t *menu);
void destroy_menu(menu_t *menu);
void switch_menu(game_t *game, int menu_index);
bool create_titles(menu_t *menu);
bool create_blur_shader(menu_t *menu);
bool create_input_button(menu_t *menu);
menu_t *create_menu(void);

// Menu events :
void event_pressed_buttons(game_t *game, sfVector2i *mouse_loc);
void event_released_buttons(game_t *game, player_t *player,
    sfVector2i *mouse_loc);
void event_hover_buttons(game_t *game, sfVector2i *mouse_loc);

// Button Actions :
void scale_mouse(game_t *game, sfVector2i *mouse_loc);
void quit_button(game_t *game, player_t *pl, button_t *button);
void left_volume_button(game_t *game, player_t *pl, button_t *button);
void right_volume_button(game_t *game, player_t *pl, button_t *button);
void left_res_button(game_t *game, player_t *player, button_t *button);
void right_res_button(game_t *game, player_t *player, button_t *button);
void left_fps_button(game_t *game, player_t *player, button_t *button);
void right_fps_button(game_t *game, player_t *player, button_t *button);
void return_main_button(game_t *game, player_t *pl, button_t *button);
void return_pause_button(game_t *game, player_t *player, button_t *button);
void play_button(game_t *game, player_t *pl, button_t *button);
void setting_button(game_t *game, player_t *pl, button_t *button);

// Text Actions :
void text_fade(game_t *game, player_t *pl, text_t *text);
void volume_text(game_t *game, player_t *pl, text_t *text);
void resolution_text(game_t *game, player_t *pl, text_t *text);
void framerate_text(game_t *game, player_t *player, text_t *text);
void static_text(game_t *game, player_t *pl, text_t *text);

// Part Handling :
void destroy_button(button_t *button);
button_t *create_button(char *txtr_path, char *hover_txtr_path, sfVector2f *pos,
    void (*action)(game_t *, player_t *, button_t *));
text_t *create_text(char *str, sfVector2f *pos, int size,
    void (*action)(game_t *, player_t *, text_t *));

// Menu Switching :
void create_intro_menu(game_t *game);
void create_main_menu(game_t *game);
void create_setting_menu(game_t *game);
void create_pause_menu(game_t *game);
void game_menu(game_t *game);
void create_game_over_menu(game_t *game);

// Menu Rendering :
void display_input_buttons(game_t *game, int i);
void render_menu(game_t *game, player_t *pl);

// HUD:
bool create_score_texts(game_t *game, player_t *pl);
bool create_ammo_hp_textures(player_t *player);
bool create_hud(game_t *game, player_t *player);
sfSprite *create_health_sprite(sfTexture *texture, sfSprite *hud);
sfSprite *create_ammo_sprite(sfTexture *texture, sfSprite *hud);
void display_score(game_t *game, player_t *pl);

// Game Checks :
int is_wall(int x, int y, game_t *game);

// Draw Update :
void draw_floor_and_ceiling(framebuffer_t *fb);
void cast_all_rays(framebuffer_t *fb, player_t *player, game_t *game);
void cast_single_ray(player_t *player, float ray_angle, game_t *game);
void render_wall_column(framebuffer_t *fb, int column, ray_t *ray,
    game_t *game);
void update_sprites(game_t *game, player_t *player);

// Draw :
void draw_sky(game_t *game);
void draw_sprites(game_t *game, player_t *player);
void draw_particles(game_t *game, particule_t *particles);

// Game Frees :
void destroy_game(game_t *game);

// Game Loop :
void increase_difficulty(game_t *game);
void game_loop(game_t *game, player_t *pl);

// Event Handling :
void handle_event(game_t *game, player_t *pl);

// Game Initialisation :
game_t *init_game(void);
bool init_player(player_t *player, game_t *game);
void create_minimap(game_t *game, player_t *player);

// Movement :
void neutralise_bobbing(player_t *player);
void angle_to_player_movement(player_t *pl, float key_radian, game_t *game);
void key_movement(game_t *game, player_t *pl);
void key_cam(game_t *game, player_t *pl, sfVector2i *mouse_loc);

// Controller :
void controller_support(game_t *game, player_t *pl);

// Weapons :
bool create_weapons(player_t *player, game_t *game);
void use_weapons(game_t *game, player_t *pl);
void weapon_sprite_anim(player_t *pl);
void detect_an_enemy_knife(player_t *pl, entity_t *entities, weapon_t *weapon);
void detect_an_enemy_gun(player_t *pl, entity_t *entities, weapon_t *weapon);

// Entities :
int player_entity_collision(player_t *player, entity_t *entity);
void make_entities_spawn(game_t *game);
void spawn_entity(game_t *game, entity_type_t type, sfTexture *texture);
void update_entities(game_t *game, player_t *player);
void draw_entities(game_t *game, player_t *player);
void entity_movement(game_t *game, player_t *pl, entity_t *entity);

// Map Initialisation:
bool init_assets(game_t *game);
map_t *init_map(void);

#endif
