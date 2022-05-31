#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "base_defines.h"

int main()
{
    main_init();

    bool done = false;
    bool redraw = true;
    float x = 100;
    float y = 450;
    float dx = 0;
    BOUNCER obj = { 320, 240, 3, 9, 0};
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
                    x -= 30;
                if(key[ALLEGRO_KEY_RIGHT])
                    x += 30;
                if(key[ALLEGRO_KEY_ESCAPE])
                    done = true;

                x += dx;

                if(x < 0) {
                    x *= -1;
                    dx *= -1;
                    audio_play_shot();
                }

                if(x > 540) {
                    x -= (x - 540) * 2;
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
                al_set_mouse_xy(disp, 320, 240);
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
            al_clear_to_color(al_map_rgb(0, 0, 0));
            // al_draw_textf(font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
            al_draw_filled_rectangle(x, y, x + 100, y + 50, al_map_rgb(255, 0, 0));
            al_draw_circle(b->x, b->y, 20, al_map_rgb_f(1, 0, 1), 2);
            al_flip_display();
            redraw = false;
        }
    }

    main_destroy();
    return 0;
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
    if(b->x > 640)
    {
        b->x -= (b->x - 640);
        b->dx *= -1;
        audio_play_shot();
    }
    if(b->y < 0)
    {
        b->y  *= -1;
        b->dy *= -1;
        audio_play_shot();
    }
    if(b->y > 450)                
    {
        if (check_collision(b->x, b->y, x, y)) {
            audio_play_explode(0);                    
        }
        else {
            audio_play_shot();
        }
        b->x -= (b->y - 480);
        b->dy *= -1;
    }                
}

int check_collision(float bx, float by, float x, float y){
    if(bx > x && bx < x + 100 && by > y && by < y + 50){
        return 1;
    }
    return 0;
}