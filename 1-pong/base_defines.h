// Para compilar por comando usando gcc:
// gcc pong.c -o pong.exe -lallegro -lallegro_font -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_acodec

void main_init();
void main_destroy();
void must_init(bool test, const char *description);
void audio_init();
void audio_deinit();
void audio_play_shot();
void audio_play_explode(int idx);

#define KEY_SEEN     1
#define KEY_RELEASED 2

ALLEGRO_TIMER*          timer;
ALLEGRO_DISPLAY*        disp;
ALLEGRO_FONT*           font;
ALLEGRO_EVENT_QUEUE*    queue;
ALLEGRO_EVENT           event;
unsigned char           key[ALLEGRO_KEY_MAX];

typedef struct BOUNCER
{
    float x, y;
    float dx, dy;
    int type;
} BOUNCER;

void update_ball_pos(BOUNCER* b);
void test_ball_collision(BOUNCER* b, float x, float y);
int check_collision(float bx, float by, float x, float y);



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

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    disp = al_create_display(640, 480);
    must_init(disp, "display");

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

    al_grab_mouse(disp);
    al_start_timer(timer);

}

void main_destroy(){
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    audio_deinit();
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

    sample_shot = al_load_sample("audio_shot.flac");
    must_init(sample_shot, "shot sample");

    sample_explode[0] = al_load_sample("audio_explode1.flac");
    must_init(sample_explode[0], "explode[0] sample");
    sample_explode[1] = al_load_sample("audio_explode2.flac");
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
