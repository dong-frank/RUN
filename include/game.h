//
// Created by Frank on 2024/1/16.
//

#ifndef RUN_GAME_H
#define RUN_GAME_H
#include <common.h>
#include <menu.h>
#include <math.h>
#define FONT_SIZE_SMALL 22
#define FPS 120
#define BEFOREGAME 1500
#define FRAME_LEN (1000/FPS)
#define MIDDLE_TRACK 500
#define TRACK_GAP 300
#define MIDDLE_OBSTACLE 470
#define OBSTACLE_GAP 300
#define MIDDLE_GOLD 560
#define GOLD_GAP 280
#define MIDDLE_PALBALL  500
#define PALBALL_GAP 300
#define Y_RUNNER 350
#define Y_OBSTACLE_JUMP (-200)
#define Y_OBSTACLE_DOWN (-500)
#define Y_OBSTACLE (-100)
#define Y_GOLD (-600)
#define Y_GOLD_GAP 300
#define Y_END 700
#define Y_GET 420
#define Y_GET_GOLD 400
#define X_LIFE 1050
#define Y_LIFE 50
#define X_SCORE 1020
#define Y_SCORE 25
#define GOLD_SCORE 100
#define SHIELD_LAST 200
#define MOVE_TIME 25
#define RUNNING_TIME 10
#define PROB_POSSIBILITY 300
#define INCIDENT_POSSIBILITY 500
#define X_INCIDENT 30
#define Y_INCIDENT 75
#define INCIDENT_LAST 250
#define INCIDENT_SCORE 3
static Uint32 tick;
static Uint32 tick_start;
int Create_rand();
void Game_logic();
void Before_game();
void Speed_change();
void Game_input();
void Do_Event_game(SDL_Event*);
void Init_display_game();
void Do_game();
void Do_score();
bool Get_gold(int);
bool Get_obstacle_onlyjump(int);
bool Get_obstacle_onlydown(int);
bool Get_obstacle(int);
bool Get_prob(int);
void Lose_life();
void Draw_game();
void Draw_background_game();
void Draw_runner1();
void Draw_runner2();
void Draw_score();
void Draw_life();
void Draw_gold(int,Uint32,SDL_Surface*,SDL_Texture*,SDL_Rect*,bool);
void Draw_obstacle_onlyjump(int,Uint32);
void Draw_obstacle_onlydown(int,Uint32);
void Draw_obstacle(int,Uint32);
void Draw_palball(int,Uint32);
void Draw_shield(int,Uint32);
void Incident_poaixi();
void Incident_peikelong();
void Do_fps();
void Do_move();
void Do_jump();
void Present_fps();
void Present();
void Game_over();
void Quit_game();
typedef struct game{
    SDL_Event Event_game;
    SDL_Surface *surface_background;
    SDL_Texture *texture_background;
    SDL_Surface *surface_life;
    SDL_Texture *texture_life;
    SDL_Rect rect_life;
    TTF_Font *font;
    double speed;
    int score;
    bool game_over;
}Game;
Game game;

typedef struct runner{
    SDL_Surface *surface_runner;
    SDL_Texture *texture_runner;
    int place;
    int posture;
    int running;
    int running_time;
    int life;
    bool get_shield;
    int move_time;
}Runner;
Runner runner;

typedef struct items{
    SDL_Surface *surface_gold;
    SDL_Texture *texture_gold;
    SDL_Surface *surface_obstacle_onlyjump;
    SDL_Texture *texture_obstacle_onlyjump;
    SDL_Surface *surface_obstacle_onlydown;
    SDL_Texture *texture_obstacle_onlydown;
    SDL_Surface *surface_obstacle;
    SDL_Texture *texture_obstacle;
    SDL_Surface *surface_palball;
    SDL_Texture *texture_palball;
    SDL_Surface *surface_shield;
    SDL_Texture *texture_shield;
    SDL_Rect rect_gold[8];
    SDL_Rect rect_obstacle_onlyjump;
    SDL_Rect rect_obstacle_onlydown;
    SDL_Rect rect_obstacle;
    SDL_Rect rect_palball;
    SDL_Rect rect_shield;
    bool collision[3];
    bool get_golds[8];
    bool get_prob;
    bool draw_prob;
}Item;
Item items;
typedef struct incident{
    SDL_Surface *surface_poaixi;
    SDL_Texture *texture_poaixi;
    SDL_Rect rect_poaixi;
    SDL_Surface *surface_peikelong;
    SDL_Texture *texture_peikelong;
    SDL_Rect rect_peikelong;
    bool draw_incident;
    int choose_incident ;
    int incident_last;
}Incident;
Incident incident;
#define X_PAUSE 0
#define Y_PAUSE 0
#define PAUSE_WIDGET_MIDDLE 450
#define PAUSE_WIDGET_GAP 270
#define PAUSE_WIDGET_Y 550
#define X_SELECTION0 8
#define X_SELECTION1 16
#define X_SELECTION2 24
#define Y_SELECTION 400
bool is_pause;
bool is_reset;
bool is_quit;
bool choose;
void Pause_logic();
void Draw_pause();
void Init_pausewidget();
void action_continue();
void action_quit();
void action_reset();
void choose_pause();
void act_action_pause();

typedef struct pause{
    SDL_Event event_pause;
    SDL_Surface *surface_pause;
    SDL_Texture *texture_pause;
    SDL_Surface *surface_selection;
    SDL_Texture *texture_selection;
    SDL_Rect rect_pause;
    SDL_Rect rect_selection;
    int selection_pause;
    Uint32 PauseTime;
}Pause;
Pause pause;
typedef struct pause_widget{
    char *name;
    int x,y;
    void (*action)();
}Pause_Widget;
Pause_Widget *pausewidget;

void Over_logic();
void Draw_over();
void Init_overwidget();
void choose_over();
void act_action_over();
void action_quit_over();
void action_reset_over();
typedef struct over{
    SDL_Event event_over;
    SDL_Surface *surface_over;
    SDL_Texture *texture_over;
    int selection_over;
}Over;
Over over;
typedef struct over_widget{
    char *name;
    int x,y;
    void (*action)();
}Over_Widget;
Over_Widget *overwidget;
#endif //RUN_GAME_H
