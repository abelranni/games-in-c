#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "base.h"

#define BLOCK_HEIGHT     10
#define BLOCK_WIDTH      25
#define BALL_RADIUS      5

void ball_draw(BOUNCER* b);
void block_draw(float x, float y);

int main()
{
    main_init();

    bool done = false;
    bool redraw = true;
    float x = BUFFER_W/2;
    float y = BUFFER_H-BLOCK_HEIGHT;
    float dx = 0;
    BOUNCER obj = { BUFFER_W/2, BUFFER_H/2, 2, 4, 0};
    BOUNCER* b = &obj;

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                update_ball_pos(b);
                test_ball_collision(b, x, y);
            
                if(key[ALLEGRO_KEY_LEFT])
                    x -= BLOCK_WIDTH/2;
                if(key[ALLEGRO_KEY_RIGHT])
                    x += BLOCK_WIDTH/2;
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                x += dx;

                if(x < 0) {
                    x *= -1;
                    dx *= -1;
                    audio_play_shot();
                }

                if(x > BUFFER_W-BLOCK_WIDTH) {
                    x -= (x - (BUFFER_W-BLOCK_WIDTH)) * 2;
                    dx *= -1;
                    audio_play_shot();
                }

                dx *= 0.9;

                for(int i = 0; i < ALLEGRO_KEY_MAX; i++) {
                    key[i] &= KEY_SEEN;
                }

                redraw = true;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
                dx += event.mouse.dx * 0.1;
                al_set_mouse_xy(disp, BUFFER_W/2, BUFFER_W/2);
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(queue)) 
        {            
            disp_pre_draw();
            al_clear_to_color(al_map_rgb(0,0,0));

            ball_draw(b);
            block_draw(x, y);

            disp_post_draw();
            redraw = false;
        }
    }

    main_destroy();
    return 0;
}




void ball_draw(BOUNCER* b){
    al_draw_filled_circle(b->x, b->y, BALL_RADIUS, al_map_rgb_f(1, 0, 1));
}
void block_draw(float x, float y){
    al_draw_filled_rectangle(x, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, al_map_rgb_f(1, 0, 1));
}


// --- Movimientos y Colisiones ---------------------------------------------------
//
void update_ball_pos(BOUNCER* b)
{
    b->x += b->dx;
    b->y += b->dy;
}

void test_ball_collision(BOUNCER* b, float x, float y)
{
    if(b->x < 0)
    {
        b->x  *= -1;
        b->dx *= -1;
        audio_play_shot();
    }
    if(b->x > BUFFER_W-(BALL_RADIUS*2))
    {
        b->x -= (b->x - (BUFFER_W-(BALL_RADIUS*2)));
        b->dx *= -1;
        audio_play_shot();
    }
    if(b->y < 0)
    {
        b->y  *= -1;
        b->dy *= -1;
        audio_play_shot();
    }
    if(b->y > BUFFER_H-(BALL_RADIUS*2))
    {
        if (check_collision(b->x, b->y, x, y)) {
            audio_play_shot();
        }
        else {
            audio_play_explode(0);                    
        }
            b->x -= (b->y - (BUFFER_H-(BALL_RADIUS*2)));
            b->dy *= -1;
    }                
}

int check_collision(float bx, float by, float x, float y){
    if(bx > x && bx < x + 100 && by > y && by < y + 50){
        return 1;
    }
    return 0;
}