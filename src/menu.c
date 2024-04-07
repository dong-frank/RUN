//
// Created by Frank on 2024/1/16.
//
#include <menu.h>
void Draw_Menu(){
    Draw_background();
    Draw_selection();
    SDL_RenderPresent(app.renderer);
    Do_fps();
    SDL_RenderClear(app.renderer);
}
void Draw_background(){
    menu.surface_background=IMG_Load("res/img/background/background_start.png");
    menu.texture_background=SDL_CreateTextureFromSurface(app.renderer,menu.surface_background);
    SDL_Rect rect_background ={0,0,menu.surface_background->w,menu.surface_background->h};
    SDL_RenderCopy(app.renderer,menu.texture_background,NULL,&rect_background);
    SDL_FreeSurface(menu.surface_background);
    SDL_DestroyTexture(menu.texture_background);
}


void Draw_selection(){
    menu.surface_selection= IMG_Load("./res/img/widget/select.png");
    menu.texture_selection= SDL_CreateTextureFromSurface(app.renderer,menu.surface_selection);
    if(selection==0) {
        SDL_Rect rect_selection = {SELECTION_X, SELECTION_Y0, menu.surface_selection->w,
                                   menu.surface_selection->h};
        SDL_RenderCopy(app.renderer, menu.texture_selection, NULL, &rect_selection);
    } else if (selection==1){
        SDL_Rect rect_selection = {SELECTION_X, SELECTION_Y1, menu.surface_selection->w,
                                   menu.surface_selection->h};
        SDL_RenderCopy(app.renderer, menu.texture_selection, NULL, &rect_selection);
    }else if (selection==2){
        SDL_Rect rect_selection = {SELECTION_X, SELECTION_Y2, menu.surface_selection->w,
                                   menu.surface_selection->h};
        SDL_RenderCopy(app.renderer, menu.texture_selection, NULL, &rect_selection);
    }
    SDL_FreeSurface(menu.surface_selection);
    SDL_DestroyTexture(menu.texture_selection);
}
void Do_Event_Menu(SDL_Event* event){
    switch(event->type){
        case SDL_QUIT:
            app.keyboard[SDL_SCANCODE_ESCAPE]=true;
            return;
        case SDL_KEYDOWN:
            app.keyboard[event->key.keysym.scancode]=true;
            break;
        case SDL_KEYUP:
            app.keyboard[event->key.keysym.scancode]=false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            app.keyboard[event->button.button]= true;
            printf("(%d,%d)\n",menu.menu_event.button.x,menu.menu_event.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            app.keyboard[event->button.button]=false;
            break;
        default:
            break;
    }
}

void Event_Menu(){
    while((!app.keyboard[SDL_SCANCODE_ESCAPE])&&SDL_WaitEvent(&menu.menu_event)){
        Draw_Menu();
        Do_Event_Menu(&menu.menu_event);
        Do_widget();
    }
}

void Init_widget(){
    menu_widgets= malloc(NUM_WIDGETS * sizeof(Widget));
    menu_widgets[0]=(Widget){"Start",SELECTION_X,SELECTION_Y0,action_start};
    menu_widgets[1]=(Widget){"Guide",SELECTION_X,SELECTION_Y1,action_guide};
    menu_widgets[2]=(Widget){"Exit",SELECTION_X,SELECTION_Y2,action_exit};
    selection =0;
}
void prev_widget(){
    if(selection==0){
        selection=2;
    } else{
        selection--;
    }
}
void next_widget(){
    if(selection==2){
        selection=0;
    } else{
        selection++;
    }
}
void act_widget(){
    void (*action)()=menu_widgets[selection].action;
    if(action!=NULL){
        action();
    }
}
void Do_widget(){
    if(app.keyboard[SDL_SCANCODE_UP]||app.keyboard[SDL_SCANCODE_LEFT]){
        prev_widget();
    }
    if(app.keyboard[SDL_SCANCODE_DOWN]||app.keyboard[SDL_SCANCODE_RIGHT]){
        next_widget();
    }

    if(menu.menu_event.button.x>=500&&menu.menu_event.button.x<=680&&menu.menu_event.button.y>=150&&menu.menu_event.button.y<=200){
        selection=0;
    } else if(menu.menu_event.button.x>=500&&menu.menu_event.button.x<=680&&menu.menu_event.button.y>=200&&menu.menu_event.button.y<=250){
        selection=1;
    } else if(menu.menu_event.button.x>=500&&menu.menu_event.button.x<=680&&menu.menu_event.button.y>=250&&menu.menu_event.button.y<=300){
        selection=2;
    }
    if(app.keyboard[SDL_SCANCODE_RETURN]||app.keyboard[SDL_SCANCODE_SPACE]||menu.menu_event.type==SDL_MOUSEBUTTONDOWN){
        act_widget();
    }
}
void action_start(){
    Quit_Menu();
    Game_logic();
}
void action_guide(){
    Quit_Menu();
    Guide_logic();
}
void action_exit(){
    Quit_Menu();
    app.keyboard[SDL_SCANCODE_ESCAPE]=true;
}

void Quit_Menu(){
    SDL_RenderClear(app.renderer);
}

void Menu_logic(){
    Init_widget();
    Draw_Menu();
    Event_Menu();
    Quit_Menu();
}