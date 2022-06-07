#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "defines.h"
#include "types.h"
#include "pong.h"

//--- Prototipos de Funciones -----------------------------------------------------------
//
void main_init();
void main_destroy();
void must_init(bool test, const char *description);
void audio_init();
void audio_deinit();
void audio_play_shot();
void audio_play_explode(int idx);
void disp_init();
void disp_deinit();

//--- Variables Globales -----------------------------------------------------------
//
ALLEGRO_TIMER*          timer;
ALLEGRO_DISPLAY*        disp;
ALLEGRO_BITMAP*         buffer;
ALLEGRO_FONT*           font;
ALLEGRO_EVENT_QUEUE*    queue;
ALLEGRO_EVENT           event;
unsigned char           key[ALLEGRO_KEY_MAX];
#include "sprites.h"


// --- Inicializacion y configuración general ---------------------------------------------------
//
void must_init(bool test, const char *description)
{
    if(test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void main_init() {

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");

    disp_init();

    font = al_create_builtin_font();
    must_init(font, "font");

    must_init(al_init_primitives_addon(), "primitives");
    al_install_mouse();
    must_init(al_install_mouse(), "mouse");

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");
    audio_init();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source()); 

    memset(key, 0, sizeof(key));

    // al_grab_mouse(disp);
    al_start_timer(timer);

    must_init(al_init_image_addon(), "image");
    sprites_init();    

}

void main_destroy(){
    al_destroy_font(font);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    disp_deinit();
    audio_deinit();
    sprites_deinit();
}


// --- Inicializacion y configuración de audio ---------------------------------------------------
//
ALLEGRO_SAMPLE* sample_shot;
ALLEGRO_SAMPLE* sample_explode[2];

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    sample_shot = al_load_sample(".\\assets\\audio_shot.flac");
    must_init(sample_shot, "shot sample");

    sample_explode[0] = al_load_sample(".\\assets\\audio_explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample(".\\assets\\audio_explode2.flac");
    must_init(sample_explode[1], "explode[1] sample");
}

void audio_deinit()
{
    al_destroy_sample(sample_shot);
    al_destroy_sample(sample_explode[0]);
    al_destroy_sample(sample_explode[1]);
}

void audio_play_shot()
{
    al_play_sample(sample_shot, 0.2, 0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );                    
}

void audio_play_explode(int idx)
{
    al_play_sample(sample_explode[idx], 0.2, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}


// --- Inicializacion y configuración de display ---------------------------------------------------
// 
void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
}

void disp_post_draw()
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}

#include "init.h"
#include "render.h"
#include "logic.h"