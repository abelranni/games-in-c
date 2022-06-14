// --- sprites ---
//
typedef struct SPRITES
{
    ALLEGRO_BITMAP* _sheet;
    ALLEGRO_BITMAP* ship_img;
    ALLEGRO_BITMAP* ball_img[2];
    ALLEGRO_BITMAP* bricks_img[BRICKS_VARIANTS];
} SPRITES;
SPRITES sprites;

ALLEGRO_BITMAP* sprite_grab(int x, int y, int w, int h)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(sprites._sheet, x, y, w, h);
    must_init(sprite, "sprite grab");
    return sprite;
}

void sprites_init()
{
    sprites._sheet = al_load_bitmap(".\\assets\\spritesheet.png");
    must_init(sprites._sheet, "spritesheet");

    sprites.ship_img = sprite_grab(185, 112, SHIP_W, SHIP_H);
    sprites.ball_img[0] = sprite_grab(32, 80, BALL_D, BALL_D);
    sprites.ball_img[1] = sprite_grab(65, 80, BALL_D, BALL_D);

    sprites.bricks_img[0] = sprite_grab(0, 0, BRICK_W, BRICK_H);
    sprites.bricks_img[1] = sprite_grab(74, 0, BRICK_W, BRICK_H);
    sprites.bricks_img[2] = sprite_grab(144, 0, BRICK_W, BRICK_H);
    sprites.bricks_img[3] = sprite_grab(216, 0, BRICK_W, BRICK_H);
}

void sprites_deinit()
{
    al_destroy_bitmap(sprites.ship_img);
    al_destroy_bitmap(sprites.ball_img[0]);
    al_destroy_bitmap(sprites.ball_img[1]);

    al_destroy_bitmap(sprites.bricks_img[0]);
    al_destroy_bitmap(sprites.bricks_img[1]);
    al_destroy_bitmap(sprites.bricks_img[2]);
    al_destroy_bitmap(sprites.bricks_img[3]);

    al_destroy_bitmap(sprites._sheet);
}
