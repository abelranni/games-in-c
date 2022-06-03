#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "base.h"

#define SHIP_HEIGHT     10
#define SHIP_WIDTH      25
#define BALL_RADIUS      5

void ball_draw(BOUNCER* ball);
void block_draw(float x, float y);
void ship_draw(SHIP* ship_ptr);
void ship_update(SHIP* ship_ptr);
void ball_update(BOUNCER* ball_ptr);
void keyboard_update(ALLEGRO_EVENT* event);

float dx = 0;
bool done = false;
bool redraw = true;
long frames = 0;

int main()
{
    main_init();

    BOUNCER ball;
    ball.pos.x = BUFFER_W/2;
    ball.pos.y = BUFFER_H/2;
    ball.pos.dx = 2;
    ball.pos.dy = 4;
    ball.radius = BALL_RADIUS;
    BOUNCER* ball_ptr = &ball;

    SHIP ship;
    ship.pos.x = BUFFER_W/2;
    ship.pos.y = BUFFER_H-SHIP_HEIGHT;
    ship.pos.dx = SHIP_WIDTH/2;
    ship.pos.dy = 0;
    ship.width = SHIP_WIDTH;
    ship.height = SHIP_HEIGHT;
    SHIP* ship_ptr = &ship;

    while(1)
    {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                ball_update(ball_ptr);
                ship_update(ship_ptr);
                test_ball_collision(ball_ptr, ship.pos.x, ship.pos.y);
                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                ship.pos.dx += event.mouse.dx * 0.1;
                al_set_mouse_xy(disp, BUFFER_W/2, BUFFER_W/2);
                break;
        }

        if(done) break;
        keyboard_update(&event);

        if(redraw && al_is_event_queue_empty(queue)) 
        {            
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0,0,0));
            ball_draw(ball_ptr);
            ship_draw(ship_ptr);
            disp_post_draw();
            redraw = false;
        }
    }
    main_destroy();
    return 0;
}

void keyboard_update(ALLEGRO_EVENT* event)
{                   
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            if(key[ALLEGRO_KEY_ESCAPE])
                done = true;
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;            
    }
}

void ship_update(SHIP* ship_ptr){

    if(key[ALLEGRO_KEY_LEFT])
        ship_ptr->pos.x -= ship_ptr->pos.dx;
    if(key[ALLEGRO_KEY_RIGHT])
        ship_ptr->pos.x += ship_ptr->pos.dx;

    if(ship_ptr->pos.x < 0) {
        ship_ptr->pos.x *= -1;
        dx *= -1;
        audio_play_shot();
    }

    if(ship_ptr->pos.x > BUFFER_W-SHIP_WIDTH) {
        ship_ptr->pos.x -= (ship_ptr->pos.x - (BUFFER_W-SHIP_WIDTH)) * 2;
        dx *= -1;
        audio_play_shot();
    }

    ship_ptr->pos.x += dx;
    dx *= 0.9;

}


void ball_draw(BOUNCER* ball_ptr){
    al_draw_filled_circle(ball_ptr->pos.x, 
                          ball_ptr->pos.y, 
                          ball_ptr->radius, 
                          al_map_rgb_f(1, 0, 1));
}

void ship_draw(SHIP* ship_ptr){
    al_draw_filled_rectangle(ship_ptr->pos.x, 
                             ship_ptr->pos.y, 
                             ship_ptr->pos.x + ship_ptr->width, 
                             ship_ptr->pos.y + ship_ptr->height,
                             al_map_rgb_f(1, 0, 1));
}


// --- Movimientos y Colisiones ---------------------------------------------------
//
void ball_update(BOUNCER* ball_ptr)
{
    ball_ptr->pos.x += ball_ptr->pos.dx;
    ball_ptr->pos.y += ball_ptr->pos.dy;
}

void test_ball_collision(BOUNCER* ball_ptr, float x, float y)
{
    if(ball_ptr->pos.x < 0)
    {
        ball_ptr->pos.x  *= -1;
        ball_ptr->pos.dx *= -1;
        audio_play_shot();
    }
    if(ball_ptr->pos.x > BUFFER_W-(BALL_RADIUS*2))
    {
        ball_ptr->pos.x -= (ball_ptr->pos.x - (BUFFER_W-(BALL_RADIUS*2)));
        ball_ptr->pos.dx *= -1;
        audio_play_shot();
    }
    if(ball_ptr->pos.y < 0)
    {
        ball_ptr->pos.y  *= -1;
        ball_ptr->pos.dy *= -1;
        audio_play_shot();
    }
    if(ball_ptr->pos.y > BUFFER_H-(BALL_RADIUS*2))
    {
        if (check_collision(ball_ptr->pos.x, ball_ptr->pos.y, x, y)) {
            audio_play_shot();
        }
        else {
            audio_play_explode(0);                    
        }
            ball_ptr->pos.x -= (ball_ptr->pos.y - (BUFFER_H-(BALL_RADIUS*2)));
            ball_ptr->pos.dy *= -1;
    }                
}

int check_collision(float bx, float by, float x, float y){
    if(bx > x && bx < x + 100 && by > y && by < y + 50){
        return 1;
    }
    return 0;
}