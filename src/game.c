//
// Created by Frank on 2024/1/16.
//
#include <game.h>
void Init_display_game(){
    game.font= TTF_OpenFont("res/ttf/pixel-comic-sans-undertale-sans-font.ttf",FONT_SIZE_SMALL);
    runner.place=0;
    runner.posture=0;
    runner.life=1;
    runner.get_shield=false;
    game.score=0;
    game.speed=0.18;
    game.game_over=false;
    runner.move_time=MOVE_TIME;
    tick=SDL_GetTicks();
    tick_start=SDL_GetTicks();
    Init_pausewidget();
    Init_overwidget();
    is_pause=false;
    is_reset=false;
    is_quit=false;
    choose=false;
    for(int i=0;i<3;i++) {
        items.collision[i]=false;
    }
    for(int i=0;i<8;i++){
        items.get_golds[i]=false;
    }
    items.get_prob=false;
    items.draw_prob=false;
    incident.draw_incident=false;
    incident.incident_last=0;
    incident.choose_incident=2;
}
void Init_pausewidget(){
    pausewidget= malloc(3 * sizeof (Pause_Widget));
    pausewidget[0]=(Pause_Widget){"Exit",PAUSE_WIDGET_MIDDLE-PAUSE_WIDGET_GAP,PAUSE_WIDGET_Y,action_quit};
    pausewidget[1]=(Pause_Widget){"Continue",PAUSE_WIDGET_MIDDLE,PAUSE_WIDGET_Y,action_continue};
    pausewidget[2]=(Pause_Widget){"Reset",PAUSE_WIDGET_MIDDLE+PAUSE_WIDGET_GAP,PAUSE_WIDGET_Y,action_reset};
    pause.selection_pause=-1;
}
void Init_overwidget(){
    overwidget= malloc(2 * sizeof (Over_Widget ));
    overwidget[0]=(Over_Widget){"Exit",PAUSE_WIDGET_MIDDLE-PAUSE_WIDGET_GAP,PAUSE_WIDGET_Y,action_quit_over};
    overwidget[1]=(Over_Widget){"Reset",PAUSE_WIDGET_MIDDLE+PAUSE_WIDGET_GAP,PAUSE_WIDGET_Y,action_reset_over};
    over.selection_over=-1;
}
int Create_rand(){
    struct timespec time1={0,0};
    clock_gettime(CLOCK_REALTIME,&time1);
    srand(time1.tv_nsec);
    int random_int =rand();
    return random_int % 3 - 1;
}
void Game_logic(){
    Before_game();
    do {
        Init_display_game();
        Do_game();
    }while(is_reset);
    Quit_game();
}
void Before_game(){
    SDL_Surface *surface_before= IMG_Load("./res/img/background/beforegame.png");
    SDL_Texture *texture_before= SDL_CreateTextureFromSurface(app.renderer,surface_before);
    SDL_RenderCopy(app.renderer,texture_before,NULL,NULL);
    SDL_FreeSurface(surface_before);
    SDL_DestroyTexture(texture_before);
    SDL_RenderPresent(app.renderer);
    SDL_Delay(BEFOREGAME);
    SDL_RenderClear(app.renderer);
    SDL_Surface *surface_beforestart= IMG_Load("./res/img/background/beforestart.png");
    SDL_Texture *texture_beforestart= SDL_CreateTextureFromSurface(app.renderer,surface_beforestart);
    SDL_RenderCopy(app.renderer,texture_beforestart,NULL,NULL);
    SDL_FreeSurface(surface_beforestart);
    SDL_DestroyTexture(texture_beforestart);
    SDL_RenderPresent(app.renderer);
    SDL_Delay(BEFOREGAME);
    SDL_RenderClear(app.renderer);
}
void Speed_change(){
    game.speed+=0.0001;
}
void Game_input(){
    while(SDL_PollEvent(&game.Event_game)){
        Do_Event_game(&game.Event_game);
        Do_move();
        Do_jump();
        if(app.keyboard[SDL_SCANCODE_P]){
            is_pause=true;
        }
    }
}
void Do_Event_game(SDL_Event* event){
    switch(event->type){
        case SDL_KEYDOWN:
            app.keyboard[event->key.keysym.scancode]=true;
            break;
        case SDL_KEYUP:
            app.keyboard[event->key.keysym.scancode]=false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            app.keyboard[event->button.button]= true;
            break;
        case SDL_MOUSEBUTTONUP:
            app.keyboard[event->button.button]=false;
            break;
        default:
            break;
    }
}
void Do_game(){
    Draw_game();
}
void Do_score(){
    if(incident.draw_incident) {
        game.score += (int) (game.speed * 10)*INCIDENT_SCORE;
    } else{
        game.score += (int) (game.speed * 10);
    }
}
bool Get_gold(int rand_gold){
    if(runner.place==rand_gold){
        return true;
    } else return false;
}
bool Get_obstacle_onlyjump(int rand_obstacle){
    if(runner.place==rand_obstacle&&runner.posture!=1&&!runner.get_shield){
        return true;
    }else return false;
}
bool Get_obstacle_onlydown(int rand_obstacle){
    if(runner.place==rand_obstacle&&runner.posture!=-1&&!runner.get_shield){
        return true;
    }else return false;
}
bool Get_obstacle(int rand_obstacle){
    if(runner.place==rand_obstacle&&!runner.get_shield){
        return true;
    }else return false;
}
bool Get_prob(int rand_prob){
    if(runner.place==rand_prob){
        return true;
    }else return false;
}
void Lose_life(){
    runner.life--;
}
void Do_move(){
    if(incident.choose_incident==-1) {
        if (app.keyboard[SDL_SCANCODE_LEFT]) {
            if (runner.place < 1) {
                runner.place++;
            }
        } else if (app.keyboard[SDL_SCANCODE_RIGHT]) {
            if (runner.place > -1) {
                runner.place--;
            }
        } else {
            return;
        }
    }else{
        if (app.keyboard[SDL_SCANCODE_LEFT]) {
            if (runner.place > -1) {
                runner.place--;
            }
        } else if (app.keyboard[SDL_SCANCODE_RIGHT]) {
            if (runner.place < 1) {
                runner.place++;
            }
        } else {
            return;
        }
    }
}
void Do_jump(){
    if(incident.choose_incident==-1) {
        if (app.keyboard[SDL_SCANCODE_UP]&&runner.posture!=-1) {
            runner.posture = -1;
        } else if (app.keyboard[SDL_SCANCODE_DOWN]&&runner.posture!=1) {
            runner.posture = 1;
        } else {
            return;
        }
    } else {
        if (app.keyboard[SDL_SCANCODE_UP]&&runner.posture!=1) {
            runner.posture = 1;
        } else if (app.keyboard[SDL_SCANCODE_DOWN]&&runner.posture!=-1) {
            runner.posture = -1;
        } else {
            return;
        }
    }
}
void Draw_game(){
    Uint32 ticks_start=SDL_GetTicks()-pause.PauseTime;
    Uint32 ticks_start_gold[8]={0};
    for(int i=0;i<8;i++){
        ticks_start_gold[i]=ticks_start-Y_GOLD_GAP*i;
    }
    Uint32 ticks_start_obstacle_onlyjump=ticks_start;
    Uint32 ticks_start_obstacle_onlydown=ticks_start;
    Uint32 ticks_start_obstacle=ticks_start;
    Uint32 ticks_start_prob=ticks_start;
    int int_rand_obstacle_onlyjump=Create_rand();
    int int_rand_obstacle_onlydown=Create_rand();
    int int_rand_obstacle=Create_rand();
    int int_rand_prob=Create_rand();

    while(int_rand_obstacle_onlyjump==int_rand_obstacle_onlydown){
        int_rand_obstacle_onlyjump=Create_rand();
    }
    int int_rand_gold[8]={Create_rand()};
    for(int i=0;i<8;i++){
        int_rand_gold[i]=int_rand_gold[0];
    }
    Uint32 duration_obstacle_onlyjump=0;
    Uint32 duration_obstacle_onlydown=0;
    Uint32 duration_obstacle=0;
    Uint32 duration_prob=0;
    Uint32 duration_gold[8]={0};
    int prob_count=0;
    int incident_count=0;
    int choose_items =Create_rand();

    int shield_count=0;
    while ((!app.keyboard[SDL_SCANCODE_ESCAPE])&&(!game.game_over)) {
        Speed_change();
        for(int i=0;i<8;i++){
            duration_gold[i]=SDL_GetTicks()-ticks_start_gold[i]-pause.PauseTime;
        }
        duration_obstacle_onlyjump = SDL_GetTicks() - ticks_start_obstacle_onlyjump - pause.PauseTime;
        duration_obstacle_onlydown = SDL_GetTicks() - ticks_start_obstacle_onlydown - pause.PauseTime;
        duration_obstacle = SDL_GetTicks() - ticks_start_obstacle - pause.PauseTime;


        Game_input();
        Draw_background_game();
        Draw_obstacle_onlyjump(int_rand_obstacle_onlyjump, duration_obstacle_onlyjump);
        Draw_obstacle(int_rand_obstacle, duration_obstacle);
        for(int i=0;i<8;i++){
            Draw_gold(int_rand_gold[i],duration_gold[i],items.surface_gold,items.texture_gold,&items.rect_gold[i],items.get_golds[i]);
        }
        if(prob_count<PROB_POSSIBILITY&&!items.draw_prob){
            prob_count++;
        } else if(prob_count>=PROB_POSSIBILITY){
            prob_count=0;
            items.draw_prob=true;
            ticks_start_prob=SDL_GetTicks()-pause.PauseTime;
            choose_items =Create_rand();
        }
        if(items.draw_prob) {
            duration_prob = SDL_GetTicks() - ticks_start_prob - pause.PauseTime;
            if(choose_items==-1||choose_items==1) {
                Draw_palball(int_rand_prob, duration_prob);
            }else if(choose_items==0){
                Draw_shield(int_rand_prob,duration_prob);
            }
        }

        if(incident_count<INCIDENT_POSSIBILITY&&!incident.draw_incident){
            incident_count++;
        } else if(incident_count>=INCIDENT_POSSIBILITY){
            incident_count=0;
            incident.draw_incident=true;
            incident.choose_incident=Create_rand();
        }
        if(incident.draw_incident){
            if(incident.choose_incident==-1){
                Incident_poaixi();
            } else if(incident.choose_incident==0||incident.choose_incident==1){
                Incident_peikelong();
            }
            incident.incident_last++;
        }
        if(incident.incident_last>INCIDENT_LAST){
            incident.incident_last=0;
            incident.draw_incident=false;
            incident.choose_incident=2;
        }

        if(runner.running==0){
            Draw_runner1();
            runner.running_time++;
            if(runner.running_time==RUNNING_TIME){
                runner.running=1;
                runner.running_time=0;
            }
        } else{
            Draw_runner2();
            runner.running_time++;
            if(runner.running_time==RUNNING_TIME){
                runner.running=0;
                runner.running_time=0;
            }
        }
        if(runner.get_shield){
            shield_count++;
            if(shield_count>SHIELD_LAST){
                shield_count=0;
                runner.get_shield=false;
            }
        }
        Draw_obstacle_onlydown(int_rand_obstacle_onlydown, duration_obstacle_onlydown);
        Draw_score();
        Draw_life();

        Pause_logic();
        Game_over();

        Do_score();
        if (runner.posture == 1 || runner.posture == -1) {
            runner.move_time--;
        }
        if (runner.move_time == 0) {
            runner.posture = 0;
            runner.move_time = MOVE_TIME;
        }
        Present();
        for(int i=0;i<8;i++){
            if(items.rect_gold[i].y > Y_GET_GOLD && items.rect_gold[i].y < Y_GET + 30 && !items.get_golds[i]){
                if(Get_gold(int_rand_gold[i])){
                    if(incident.draw_incident) {
                        game.score += GOLD_SCORE*INCIDENT_SCORE;
                    } else{
                        game.score+= GOLD_SCORE;
                    }
                    items.get_golds[i]=true;
                }
            }
            if(items.rect_gold[i].y > Y_END){
                items.rect_gold[i].y = Y_GOLD;
                if(i<7){
                    int_rand_gold[i]=int_rand_gold[7];
                } else{
                    int_rand_gold[7] = Create_rand();
                    while (int_rand_gold[7] == int_rand_gold[0]) {
                        int_rand_gold[7] = Create_rand();
                    }
                }
                ticks_start_gold[i]=SDL_GetTicks() - pause.PauseTime;
                items.get_golds[i]=false;
            }
        }
        if (items.rect_obstacle_onlyjump.y > Y_GET&&!items.collision[0]) {
            if (Get_obstacle_onlyjump(int_rand_obstacle_onlyjump)) {
                if(incident.choose_incident==0){
                    game.game_over=true;
                } else {
                    Lose_life();
                }
            }
            items.collision[0] = true;
        }
        if(items.rect_obstacle_onlyjump.y> Y_END){
            items.rect_obstacle_onlyjump.y = Y_OBSTACLE_JUMP;
            ticks_start_obstacle_onlyjump = SDL_GetTicks() - pause.PauseTime;
            int_rand_obstacle_onlyjump = Create_rand();
            while (int_rand_obstacle_onlyjump == int_rand_obstacle_onlydown) {
                int_rand_obstacle_onlyjump = Create_rand();
            }
            items.collision[0] = false;
        }
        if (items.rect_obstacle_onlydown.y > Y_GET&&!items.collision[1]) {
            if (Get_obstacle_onlydown(int_rand_obstacle_onlydown)) {
                if(incident.choose_incident==0){
                    game.game_over=true;
                } else {
                    Lose_life();
                }
            }
            items.collision[1]=true;
        }
        if(items.rect_obstacle_onlydown.y > Y_END){
            items.rect_obstacle_onlydown.y = Y_OBSTACLE_DOWN;
            ticks_start_obstacle_onlydown = SDL_GetTicks() - pause.PauseTime;
            int_rand_obstacle_onlydown = Create_rand();
            while (int_rand_obstacle_onlyjump == int_rand_obstacle_onlydown) {
                int_rand_obstacle_onlydown = Create_rand();
            }
            items.collision[1]=false;
        }
        if (items.rect_obstacle.y > Y_GET&&!items.collision[2]) {
            if (Get_obstacle(int_rand_obstacle)) {
                if(incident.choose_incident==0){
                    game.game_over=true;
                } else {
                    Lose_life();
                }
            }
            items.collision[2]=true;
        }
        if(items.rect_obstacle.y > Y_END){
            items.rect_obstacle.y = Y_OBSTACLE;
            ticks_start_obstacle = SDL_GetTicks() - pause.PauseTime;
            int_rand_obstacle = Create_rand();
            items.collision[2]=false;
        }
        if (items.rect_palball.y > Y_GET&&items.rect_palball.y < Y_GET + 30 &&!items.get_prob) {
            if (Get_prob(int_rand_prob)) {
                runner.life++;
                items.get_prob=true;
            }
        }
        if(items.rect_palball.y>Y_END){
            items.rect_palball.y = Y_GOLD;
            int_rand_prob=Create_rand();
            ticks_start_prob = SDL_GetTicks() - pause.PauseTime;
            items.get_prob=false;
            items.draw_prob=false;
        }
        if (items.rect_shield.y > Y_GET&&items.rect_shield.y < Y_GET + 30 &&!items.get_prob) {
            if (Get_prob(int_rand_prob)) {
                runner.get_shield=true;
                items.get_prob=true;
            }
        }
        if(items.rect_shield.y>Y_END){
            items.rect_shield.y = Y_GOLD;
            int_rand_prob=Create_rand();
            ticks_start_prob = SDL_GetTicks() - pause.PauseTime;
            items.get_prob=false;
            items.draw_prob=false;
        }
            Game_over();
    }
    if(!is_quit&&!is_reset) {
        Over_logic();
    }
}
void Draw_background_game(){
    game.surface_background= IMG_Load("res/img/background/game.png");
    game.texture_background= SDL_CreateTextureFromSurface(app.renderer,game.surface_background);
    SDL_RenderCopy(app.renderer,game.texture_background,NULL,NULL);
    SDL_FreeSurface(game.surface_background);
    SDL_DestroyTexture(game.texture_background);
}
void Draw_runner1(){
    if(!runner.get_shield) {
        if (runner.posture == 0) {
            runner.surface_runner = IMG_Load("res/img/runner/runner1.png");
        } else if (runner.posture == 1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_jump.png");
        } else if (runner.posture == -1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_squat.png");
        }
    } else{
        if (runner.posture == 0) {
            runner.surface_runner = IMG_Load("res/img/runner/runner1_shield.png");
        } else if (runner.posture == 1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_jump_shield.png");
        } else if (runner.posture == -1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_squat_shield.png");
        }
    }
    runner.texture_runner= SDL_CreateTextureFromSurface(app.renderer,runner.surface_runner);
    SDL_Rect rect ={MIDDLE_TRACK+runner.place*TRACK_GAP,Y_RUNNER,runner.surface_runner->w,runner.surface_runner->h};
    SDL_RenderCopy(app.renderer,runner.texture_runner,NULL,&rect);
    SDL_FreeSurface(runner.surface_runner);
    SDL_DestroyTexture(runner.texture_runner);
}
void Draw_runner2(){
    if(!runner.get_shield) {
        if (runner.posture == 0) {
            runner.surface_runner = IMG_Load("res/img/runner/runner2.png");
        } else if (runner.posture == 1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_jump.png");
        } else if (runner.posture == -1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_squat.png");
        }
    } else{
        if (runner.posture == 0) {
            runner.surface_runner = IMG_Load("res/img/runner/runner2_shield.png");
        } else if (runner.posture == 1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_jump_shield.png");
        } else if (runner.posture == -1) {
            runner.surface_runner = IMG_Load("res/img/runner/runner_squat_shield.png");
        }
    }
    runner.texture_runner= SDL_CreateTextureFromSurface(app.renderer,runner.surface_runner);
    SDL_Rect rect ={MIDDLE_TRACK+runner.place*TRACK_GAP,Y_RUNNER,runner.surface_runner->w,runner.surface_runner->h};
    SDL_RenderCopy(app.renderer,runner.texture_runner,NULL,&rect);
    SDL_FreeSurface(runner.surface_runner);
    SDL_DestroyTexture(runner.texture_runner);
}
void Draw_score(){
    char buf[16];
    SDL_Color color_black={0,0,0,0};
    sprintf(buf,"Score: %d",game.score);
    SDL_Rect rect_score={X_SCORE,Y_SCORE};
    Write_words(buf,color_black,game.font,app.renderer,&rect_score);
}
void Draw_life(){
    char buf[16];
    SDL_Color color_black={0,0,0,0};
    sprintf(buf,": %d",runner.life);
    SDL_Rect rect_life_num={X_LIFE+50,Y_LIFE+20};
    Write_words(buf,color_black,game.font,app.renderer,&rect_life_num);

    game.surface_life= IMG_Load("res/img/items/palball_small.png");
    game.texture_life= SDL_CreateTextureFromSurface(app.renderer,game.surface_life);
    game.rect_life.x=X_LIFE;
    game.rect_life.y=Y_LIFE;
    game.rect_life.w=game.surface_life->w;
    game.rect_life.h=game.surface_life->h;
    SDL_RenderCopy(app.renderer,game.texture_life,NULL,&game.rect_life);
}
void Draw_gold(int rand,Uint32 duration, SDL_Surface *surface ,SDL_Texture *texture , SDL_Rect *rect,bool get_gold){
    if(get_gold==false){
        surface = IMG_Load("res/img/items/gold.png");
    } else{
        surface = IMG_Load("res/img/items/blank.png");
    }
    texture= SDL_CreateTextureFromSurface(app.renderer,surface);
    rect->x=MIDDLE_GOLD + rand * GOLD_GAP;
    rect->y=Y_GOLD + game.speed * duration;
    rect->w=surface->w;
    rect->h=surface->h;
    SDL_RenderCopy(app.renderer,texture,NULL,rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Draw_obstacle_onlyjump(int rand,Uint32 duration){
    items.surface_obstacle_onlyjump= IMG_Load("res/img/items/obstacle_onlyjump.png");
    items.texture_obstacle_onlyjump= SDL_CreateTextureFromSurface(app.renderer,items.surface_obstacle_onlyjump);
    items.rect_obstacle_onlyjump.x=MIDDLE_OBSTACLE+rand*OBSTACLE_GAP;
    items.rect_obstacle_onlyjump.y=Y_OBSTACLE_JUMP+game.speed*duration;
    items.rect_obstacle_onlyjump.w=items.surface_obstacle_onlyjump->w;
    items.rect_obstacle_onlyjump.h=items.surface_obstacle_onlyjump->h;
    SDL_RenderCopy(app.renderer,items.texture_obstacle_onlyjump,NULL,&items.rect_obstacle_onlyjump);
    SDL_FreeSurface(items.surface_obstacle_onlyjump);
    SDL_DestroyTexture(items.texture_obstacle_onlyjump);
}
void Draw_obstacle_onlydown(int rand,Uint32 duration){
    items.surface_obstacle_onlydown= IMG_Load("res/img/items/obstacle_onlydown.png");
    items.texture_obstacle_onlydown= SDL_CreateTextureFromSurface(app.renderer,items.surface_obstacle_onlydown);
    items.rect_obstacle_onlydown.x=MIDDLE_OBSTACLE+rand*OBSTACLE_GAP;
    items.rect_obstacle_onlydown.y=Y_OBSTACLE_DOWN+game.speed*duration;
    items.rect_obstacle_onlydown.w=items.surface_obstacle_onlydown->w;
    items.rect_obstacle_onlydown.h=items.surface_obstacle_onlydown->h;
    SDL_RenderCopy(app.renderer,items.texture_obstacle_onlydown,NULL,&items.rect_obstacle_onlydown);
    SDL_FreeSurface(items.surface_obstacle_onlydown);
    SDL_DestroyTexture(items.texture_obstacle_onlydown);
}
void Draw_obstacle(int rand,Uint32 duration){
    items.surface_obstacle= IMG_Load("res/img/items/obstacle.png");
    items.texture_obstacle= SDL_CreateTextureFromSurface(app.renderer,items.surface_obstacle);
    items.rect_obstacle.x=MIDDLE_OBSTACLE+rand*OBSTACLE_GAP;
    items.rect_obstacle.y=Y_OBSTACLE+game.speed*duration;
    items.rect_obstacle.w=items.surface_obstacle->w;
    items.rect_obstacle.h=items.surface_obstacle->h;
    SDL_RenderCopy(app.renderer,items.texture_obstacle,NULL,&items.rect_obstacle);
    SDL_FreeSurface(items.surface_obstacle);
    SDL_DestroyTexture(items.texture_obstacle);
}
void Draw_palball(int rand,Uint32 duration){
    if(items.get_prob==false) {
        items.surface_palball = IMG_Load("res/img/items/palball.png");
    } else{
        items.surface_palball = IMG_Load("res/img/items/blank.png");
    }
    items.texture_palball= SDL_CreateTextureFromSurface(app.renderer,items.surface_palball);
    items.rect_palball.x=MIDDLE_PALBALL+rand*PALBALL_GAP;
    items.rect_palball.y=Y_OBSTACLE+game.speed*duration;
    items.rect_palball.w=items.surface_palball->w;
    items.rect_palball.h=items.surface_palball->h;
    SDL_RenderCopy(app.renderer,items.texture_palball,NULL,&items.rect_palball);
    SDL_FreeSurface(items.surface_palball);
    SDL_DestroyTexture(items.texture_palball);
}
void Draw_shield(int rand,Uint32 duration){
    if(items.get_prob==false) {
        items.surface_shield = IMG_Load("res/img/items/shield.png");
    } else{
        items.surface_shield = IMG_Load("res/img/items/blank.png");
    }
    items.texture_shield= SDL_CreateTextureFromSurface(app.renderer,items.surface_shield);
    items.rect_shield.x=MIDDLE_PALBALL+rand*PALBALL_GAP;
    items.rect_shield.y=Y_OBSTACLE+game.speed*duration;
    items.rect_shield.w=items.surface_shield->w;
    items.rect_shield.h=items.surface_shield->h;
    SDL_RenderCopy(app.renderer,items.texture_shield,NULL,&items.rect_shield);
    SDL_FreeSurface(items.surface_shield);
    SDL_DestroyTexture(items.texture_shield);
}
void Incident_poaixi(){
    incident.surface_poaixi= IMG_Load("res/img/incident/boaixi.png");
    incident.texture_poaixi= SDL_CreateTextureFromSurface(app.renderer,incident.surface_poaixi);
    incident.rect_poaixi.x=X_INCIDENT;
    incident.rect_poaixi.y=Y_INCIDENT;
    incident.rect_poaixi.w=incident.surface_poaixi->w;
    incident.rect_poaixi.h=incident.surface_poaixi->h;
    SDL_RenderCopy(app.renderer,incident.texture_poaixi,NULL,&incident.rect_poaixi);
    SDL_FreeSurface(incident.surface_poaixi);
    SDL_DestroyTexture(incident.texture_poaixi);
}
void Incident_peikelong(){
    incident.surface_peikelong= IMG_Load("res/img/incident/peikelong.png");
    incident.texture_peikelong= SDL_CreateTextureFromSurface(app.renderer,incident.surface_peikelong);
    incident.rect_peikelong.x=X_INCIDENT;
    incident.rect_peikelong.y=Y_INCIDENT;
    incident.rect_peikelong.w=incident.surface_peikelong->w;
    incident.rect_peikelong.h=incident.surface_peikelong->h;
    SDL_RenderCopy(app.renderer,incident.texture_peikelong,NULL,&incident.rect_peikelong);
    SDL_FreeSurface(incident.surface_peikelong);
    SDL_DestroyTexture(incident.texture_peikelong);
}
void Do_fps(){
    //TODO: 减去程序本身执行的时间
    SDL_Delay(FRAME_LEN);
}
void Present_fps(){
    Uint32 duration = SDL_GetTicks()-tick;
    tick=SDL_GetTicks();
    Uint32 fps= 1000/duration;
    char buf[16];
    SDL_Color color_black={0,0,0,0};
    sprintf(buf,"FPS: %u",fps);
    SDL_Rect rect_fps={50,50};
    Write_words(buf,color_black,game.font,app.renderer,&rect_fps);
}
void Present(){
//    Present_fps();
    SDL_RenderPresent(app.renderer);
    Do_fps();
    SDL_RenderClear(app.renderer);
}
void Game_over(){
    if(runner.life<=0||is_reset){
        game.game_over=true;
    }
}
void Quit_game(){
    SDL_RenderClear(app.renderer);
    TTF_CloseFont(game.font);
    Menu_logic();
}

void Pause_logic(){
    if(is_pause){
        Uint32 starttime=SDL_GetTicks();
        Draw_pause();
        SDL_RenderPresent(app.renderer);
        while(is_pause&& SDL_WaitEvent(&pause.event_pause)&&!app.keyboard[SDL_SCANCODE_ESCAPE]){
        SDL_Delay(1);
        Do_Event_game(&pause.event_pause);
        choose_pause();
        act_action_pause();
        }
        pause.PauseTime+=(SDL_GetTicks()-starttime);
    } else return;
}
void choose_pause(){
    if(pause.event_pause.button.x>=40&&pause.event_pause.button.x<=375
    &&pause.event_pause.button.y>=510&&pause.event_pause.button.y<=545
    &&pause.event_pause.type==SDL_MOUSEBUTTONDOWN){
        pause.selection_pause=0;
    }else if(pause.event_pause.button.x>=430&&pause.event_pause.button.x<=770
    &&pause.event_pause.button.y>=510&&pause.event_pause.button.y<=545
    &&pause.event_pause.type==SDL_MOUSEBUTTONDOWN){
        pause.selection_pause=1;
    }else if(pause.event_pause.button.x>=825&&pause.event_pause.button.x<=1160
    &&pause.event_pause.button.y>=510&&pause.event_pause.button.y<=545
    &&pause.event_pause.type==SDL_MOUSEBUTTONDOWN){
        pause.selection_pause=2;
    }

}
void act_action_pause(){
    if(pause.selection_pause!=-1){
    void (*action)()=pausewidget[pause.selection_pause].action;
    if(action!=NULL){
        action();
        pause.selection_pause=-1;
        }
    } else return;

}
void Draw_pause(){
    pause.surface_pause= IMG_Load("res/img/pause/pause.png");
    pause.texture_pause= SDL_CreateTextureFromSurface(app.renderer,pause.surface_pause);
    pause.rect_pause.x=X_PAUSE;
    pause.rect_pause.y=Y_PAUSE;
    pause.rect_pause.w=pause.surface_pause->w;
    pause.rect_pause.h=pause.surface_pause->h;
    SDL_RenderCopy(app.renderer,pause.texture_pause,NULL,&pause.rect_pause);
    SDL_FreeSurface(pause.surface_pause);
    SDL_DestroyTexture(pause.texture_pause);
}
void action_continue(){
    is_pause=false;
}
void action_quit(){
    is_pause=false;
    game.game_over=true;
    is_quit=true;
}
void action_reset() {
    is_pause = false;
    is_reset = true;
}
void Over_logic(){
        Uint32 starttime=SDL_GetTicks();
        Draw_over();
        SDL_RenderPresent(app.renderer);
        while(!choose&&SDL_WaitEvent(&over.event_over)&&!app.keyboard[SDL_SCANCODE_ESCAPE]){
            SDL_Delay(0);
            Do_Event_game(&over.event_over);
            choose_over();
            act_action_over();
        }
        pause.PauseTime+=(SDL_GetTicks()-starttime);
}
void act_action_over(){
    if(over.selection_over!=-1){
        void (*action)()=overwidget[over.selection_over].action;
        if(action!=NULL){
            action();
            over.selection_over=-1;
        }
    } else return;

}
void action_quit_over(){
    choose=true;
}
void action_reset_over(){
    choose=true;
    is_reset=true;
}
void Draw_over(){
    over.surface_over= IMG_Load("res/img/background/death.png");
    over.texture_over= SDL_CreateTextureFromSurface(app.renderer,over.surface_over);
    SDL_RenderCopy(app.renderer,over.texture_over,NULL,NULL);
    TTF_Font *font_over = TTF_OpenFont("res/ttf/pixel-comic-sans-undertale-sans-font.ttf",50);
    char buf[16];
    SDL_Color color_black={255,255,255,255};
    sprintf(buf,"Score: %d",game.score);
    SDL_Rect rect_score={470,300};
    Write_words(buf,color_black,font_over,app.renderer,&rect_score);
    SDL_FreeSurface(over.surface_over);
    SDL_DestroyTexture(over.texture_over);
    TTF_CloseFont(font_over);
}
void choose_over() {
    if (over.event_over.button.x >= 470 && over.event_over.button.x <= 725
        && over.event_over.button.y >= 550 && over.event_over.button.y <= 570
        && app.keyboard[over.event_over.button.button]) {
        over.selection_over = 1;
    } else if (over.event_over.button.x >= 470 && over.event_over.button.x <= 725
        && over.event_over.button.y >= 610 && over.event_over.button.y <= 630
        && app.keyboard[over.event_over.button.button]) {
        over.selection_over = 0;
    }
}