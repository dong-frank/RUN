//
// Created by Frank on 2024/1/16.
//

#ifndef RUN_MENU_H
#define RUN_MENU_H
#include <common.h>
#include <game.h>
#include <guide.h>
#define NUM_WIDGETS 3
#define SELECTION_X 505
#define SELECTION_Y0 145
#define SELECTION_Y1 200
#define SELECTION_Y2 260
typedef struct menu{
    SDL_Event menu_event;
    SDL_Surface *surface_background;
    SDL_Texture *texture_background;
    SDL_Surface *surface_selection;
    SDL_Texture *texture_selection;
}Menu;
Menu menu;

typedef struct widget{
    char *name;
    int x,y;
    void (*action)();
}Widget;

Widget *menu_widgets;
int selection;


void Menu_logic();

void Draw_Menu();
void Draw_background();
void Draw_selection();

void Do_Event_Menu(SDL_Event*);

void Event_Menu();

void Init_widget();

void Do_widget();

void prev_widget();
void next_widget();
void act_widget();

void action_start();
void action_guide();
void action_exit();

void Quit_Menu();



#endif //RUN_MENU_H
