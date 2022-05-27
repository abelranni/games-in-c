#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>


// --- general ---
#ifdef BASE_H
long frames;
long score;
#else
extern long frames;
extern long score;
#endif

void must_init(bool test, const char *description);
int between(int lo, int hi);
float between_f(float lo, float hi);
bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);

// --- display ---
#ifdef BASE_H
ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

#else
extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_BITMAP* buffer;

#endif

#define BUFFER_W 320
#define BUFFER_H 240
#define DISP_SCALE 2
#define DISP_W (BUFFER_W * DISP_SCALE)
#define DISP_H (BUFFER_H * DISP_SCALE)
void disp_init();
void disp_deinit();
void disp_pre_draw();
void disp_post_draw();

// --- keyboard ---
#ifdef BASE_H
unsigned char key[ALLEGRO_KEY_MAX];

#else
extern unsigned char key[ALLEGRO_KEY_MAX];

#endif

#define KEY_SEEN     1
#define KEY_RELEASED 2
void keyboard_init();
void keyboard_update(ALLEGRO_EVENT* event);

// --- font ---
#ifdef BASE_H
ALLEGRO_FONT* font;
#else
extern ALLEGRO_FONT* font;

#endif

void font_init();
